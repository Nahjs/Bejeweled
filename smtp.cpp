#include "smtp.h"

/**
 * @brief 构造函数：初始化SMTP客户端
 * 设置服务器信息，创建socket连接，准备邮件内容
 */
Smtp::Smtp(const QString &serverName, const QString &username, const QString &password, const QString &from, const QStringList &to, const QString &subject, const QString &body)
{
    // 初始化服务器信息
    server = serverName;
    user = username;
    pass = password;

    // Base64编码用户名和密码
    user = user.toLocal8Bit().toBase64();
    pass = pass.toLocal8Bit().toBase64();

    x = 1; // 收件人计数器
    int recipCount = 0;
    
    // 创建socket并连接信号槽
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected() ) );
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
             SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged( QAbstractSocket::SocketState)), this,
             SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this,
            SLOT(disconnected()));

    qDebug() << "Signals created";

    // 构建邮件头
    for(recipCount = 0; recipCount < to.count(); recipCount++)
    {
        message.append("To: " + to.at(recipCount) + "\n");
    }
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");
    message.append("Mime-Version: 1.0;\n");
    message.append("Content-Type: text/html; charset=\"utf8\";\n");
    message.append("Content-Transfer-Encoding: 8bit;\n");
    message.append("\n");
    qDebug() << "body is: " << body;
    message.append(body);
    message.replace(QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n"));
    message.replace(QString::fromLatin1( "\r\n.\r\n" ), QString::fromLatin1( "\r\n..\r\n" ) );

    // 初始化连接
    this->from = from;
    rcpt = to.at(0);
    recips = to;
    state = Init;
    socket->connectToHost(server, 25); // 连接SMTP服务器，标准端口25
    if(socket->waitForConnected(30000))
    {
        qDebug("connected");
    }

    t = new QTextStream( socket );
}

/**
 * @brief 析构函数：清理资源
 */
Smtp::~Smtp()
{
    qDebug() << "Destroying";
    finished();
    delete t;
    delete socket;
}

/**
 * @brief 处理Socket状态变化
 */
void Smtp::stateChanged(QAbstractSocket::SocketState socketState)
{

    qDebug() <<"stateChanged: " << socketState;

}

/**
 * @brief 处理Socket错误
 */
void Smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << " error:" <<socketError;

}

/**
 * @brief 处理断开连接事件
 */
void Smtp::disconnected()
{
    qDebug() << "Disconnected: "  << socket->errorString();
}

/**
 * @brief 处理连接建立事件
 */
void Smtp::connected()
{
    // 连接建立后的处理
}

/**
 * @brief 处理服务器响应
 * 实现SMTP协议的状态机，处理每个阶段的命令发送和响应
 */
void Smtp::readyRead()
{
    // 读取服务器响应
    QString rLine;
    do
    {
        rLine = socket->readLine();
        response += rLine;
        qDebug() << "Response is: " << response;
    }
    while (socket->canReadLine() && rLine[3] != ' ');

    rLine.truncate(3);

    // 根据当前状态处理SMTP协议流程
    if (state == Init && rLine[0] == '2')
    {
        // 发送HELO命令
        qDebug() << "HELO there";
        *t << "HELO there\r\n";
        t->flush();

        state = Auth;
    }
    else if (state == Auth && rLine[0] == '2')
    {
        // 开始认证过程
        qDebug() << "Auth";
        *t << "AUTH LOGIN" << "\r\n";
        t->flush();
        state = User;
    }
    else if (state == User && rLine[0] == '3')
    {
        //Trying User
        qDebug() << "Username";
        *t << user << "\r\n";
        t->flush();

        state = Pass;
    }
    else if (state == Pass && rLine[0] == '3')
    {
        //Trying pass
        qDebug() << "Pass";
        *t << pass << "\r\n";
        t->flush();

        state = Mail;
    }
    else if (state == Mail && rLine[0] == '2')
    {
        qDebug() << "Mail from";
        *t << "MAIL FROM: " << from << "\r\n";
        t->flush();
        state = Rcpt;
    }
    else if (state == Rcpt && rLine[0] == '2')
    {

        qDebug() << "RCPT TO ";
        *t << "RCPT TO: " << rcpt << "\r\n";
        t->flush();
        if(recips.isEmpty() || x == recips.count() )
        {
            state = Data;
        }
        else
        {
            if(x < recips.count())
            {
                rcpt = recips.at(x);
                x++;
                state = Rcpt;
            }
        }
    }
    else if (state == Data && rLine[0] == '2')
    {
        qDebug() << "Data";
        *t << "DATA\r\n";
        t->flush();
        state = Body;
    }
    else if (state == Body && rLine[0] == '3')
    {
        qDebug() << "Body state";
        *t << message << "\r\n.\r\n";
        t->flush();
        state = Quit;
    }
    else if (state == Quit && rLine[0] == '2')
    {
        qDebug() << "Quit";
        *t << "QUIT\r\n";
        t->flush();
        // here, we just close.
        state = Close;
        emit status( tr( "Message sent" ) );
    }
    else if (state == Close)
    {
        // 关闭连接
        qDebug() << "State == close";
        deleteLater();
        return;
    }
    else
    {
        // 发生错误，关闭连接
        state = Close;
    }
    response = "";
}