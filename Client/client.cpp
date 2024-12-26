#include "client.h"
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "login.h"

Client::Client(QObject *parent) : QObject(parent), m_socket(new QTcpSocket(this)) {
    connect(m_socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), 
            this, &Client::handleError);
}

Client::~Client() {
    if (m_socket->isOpen()) {
        m_socket->close();
    }
}

void Client::connectToServer(const QString &host, int port) {
    m_host = host;
    m_port = port;
    
    // 确保之前的连接已经清理
    if (m_socket->state() != QAbstractSocket::UnconnectedState) {
        m_socket->abort();
        m_socket->waitForDisconnected();
    }

    qDebug() << "正在连接到服务器:" << host << "端口:" << port;
    
    // 添加连接超时处理
    QTimer* timeoutTimer = new QTimer(this);
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, [this, timeoutTimer]() {
        if (m_socket->state() != QAbstractSocket::ConnectedState) {
            qDebug() << "连接超时";
            emit error("连接服务器超时");
            m_socket->abort();
        }
        timeoutTimer->deleteLater();
    });
    timeoutTimer->start(5000);  // 5秒超时

    // 设置保持连接选项
    m_socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    
    #ifdef Q_OS_LINUX
    // Linux系统下的额外KeepAlive设置
    int enableKeepAlive = 1;
    int keepIdle = 60; // 60秒没有数据传输就开始探测
    int keepInterval = 5; // 每5秒探测一次
    int keepCount = 3; // 最多探测3次
    
    setsockopt(m_socket->socketDescriptor(), SOL_SOCKET, SO_KEEPALIVE, &enableKeepAlive, sizeof(enableKeepAlive));
    setsockopt(m_socket->socketDescriptor(), IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(keepIdle));
    setsockopt(m_socket->socketDescriptor(), IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(keepInterval));
    setsockopt(m_socket->socketDescriptor(), IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(keepCount));
    #endif

    m_socket->connectToHost(host, port);

    // 添加连接成功的信号处理
    connect(m_socket, &QTcpSocket::connected, this, [this]() {
        qDebug() << "已连接到服务器";

        emit connected();  // 确保发送连接成功信号
    });
    
    // 添加连接状态监控
    connect(m_socket, &QTcpSocket::stateChanged, this, [this](QAbstractSocket::SocketState state) {
        qDebug() << "Socket状态变化:" << state;
        if (state == QAbstractSocket::ConnectedState) {
            qDebug() << "已连接到服务器";
        } else if (state == QAbstractSocket::UnconnectedState) {
            qDebug() << "未连接状态";
            emit disconnected();
        }
    });
}

void Client::disconnectFromServer() {
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "正在断开与服务器的连接...";
        m_socket->disconnectFromHost();
        if (m_socket->state() != QAbstractSocket::UnconnectedState) {
            m_socket->waitForDisconnected(1000);
        }
        qDebug() << "断开连接完成";
    }
}

void Client::sendMessage(const QString& type, const QString& message) {
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QJsonObject json;
        json["type"] = type;
        json["message"] = message;
        QJsonDocument doc(json);
        QString jsonString = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
        
        // 添加调试输出
        qDebug() << "发送消息:" << jsonString;
        
        m_socket->write(jsonString.toUtf8() + "\n");
        m_socket->flush();
    }
}

void Client::sendMatchRequest(int desiredPlayers) {
    QJsonObject requestData;
    requestData["desiredPlayers"] = desiredPlayers;
    requestData["username"] = Login::currentUsername;
    QJsonDocument doc(requestData);
    sendMessage("MATCH_REQUEST", doc.toJson(QJsonDocument::Compact));
}

void Client::sendMatchCancel() {
    QJsonObject cancelData;
    cancelData["username"] = Login::currentUsername;
    QJsonDocument doc(cancelData);
    sendMessage("MATCH_CANCEL", doc.toJson(QJsonDocument::Compact));
}

bool Client::isConnected() const {
    return m_socket->state() == QAbstractSocket::ConnectedState 
           && m_socket->isValid();  // 添加额外的有效性检查
}


void Client::onReadyRead() {
    while(m_socket->canReadLine()) {
        QByteArray data = m_socket->readLine().trimmed();
        qDebug() << "收到原始数据:" << data;
        
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isObject()) {
            QJsonObject json = doc.object();
            QString type = json["type"].toString();
            
            // 对于用户列表消息，直接传递完整的message值
            if (type == "USER") {
                QJsonValue messageValue = json["message"];
                QString message;
                if (messageValue.isArray()) {
                    QJsonArray messageArray = messageValue.toArray();
                    QJsonDocument messageDoc(messageArray);
                    message = QString::fromUtf8(messageDoc.toJson(QJsonDocument::Compact));
                } else {
                    message = messageValue.toString();
                }
                emit messageReceived(type, message);
            } else {
                QString message = json["message"].toString();
                qDebug() << "解析消息 - 类型:" << type << "内容:" << message;
                emit messageReceived(type, message);
            }
        } else {
            qDebug() << "无法解析JSON数据:" << data;
        }
    }
}

void Client::onDisconnected() {
    qDebug() << "客户端断开连接";

    emit disconnected();
    
    // 自动重连
    QTimer::singleShot(3000, this, [this]() {
        if (!isConnected()) {
            qDebug() << "尝试重新连接...";
            connectToServer(m_host, m_port);
        }
    });
}

void Client::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    Q_UNUSED(socketError)
    emit error(m_socket->errorString());
}

void Client::handleError(QAbstractSocket::SocketError socketError) {
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            qDebug() << "服务器关闭了连接，尝试重新连接...";
            QTimer::singleShot(3000, this, [this]() {
                connectToServer(m_host, m_port);
            });
            break;
        case QAbstractSocket::HostNotFoundError:
            emit error("找不到服务器");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            emit error("连接被拒绝");
            break;
        default:
            emit error("发生错误: " + m_socket->errorString());
            if (m_socket->state() != QAbstractSocket::ConnectedState) {
                QTimer::singleShot(5000, this, [this]() {
                    connectToServer(m_host, m_port);
                });
            }
    }
}

void Client::handleServerMessage(const QString& type, const QString& data) {
    if (type == "MATCH_STATUS") {
        QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            QString state = obj["state"].toString();
            if (state == "matched") {
                emit matchFound(data);
            } else if (state == "waiting") {
                emit matchWaiting(data);
            } else if (state == "cancelled") {
                emit matchCancelled(data);
            } else if (state == "failed") {
                emit matchFailed(data);
            }
        }
    }
    // ...existing message handling...
}

void Client::handleMessage(const QString& type, const QString& data) {
    qDebug() << "处理消息:" << type << data;

    // 先检查特殊的消息类型
    if (type == "BATTLE_START" || type == "BATTLE_REQ") {
        QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            QString username = obj["username"].toString();
            if (!username.isEmpty()) {
                qDebug() << "发出对战开始信号，对手:" << username;
                emit battleStarted(username);
            }
        }
        return;
    }

    // ...existing code...
}

void Client::sendBattleRequest() {
    QJsonObject request;
    request["username"] = Login::currentUsername;
    request["timestamp"] = QDateTime::currentMSecsSinceEpoch();
    
    QJsonDocument doc(request);
    sendMessage("BATTLE_REQ", doc.toJson(QJsonDocument::Compact));
}

