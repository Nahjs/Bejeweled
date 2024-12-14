#ifndef SMTP_H
#define SMTP_H

#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

class Smtp : public QObject
{
    Q_OBJECT

public:
    Smtp(const QString &serverName, const QString &username, const QString &password,
         const QString &from, const QStringList &to, const QString &subject, const QString &body);
    ~Smtp();

signals:
    void status(const QString &);

private slots:
    void stateChanged(QAbstractSocket::SocketState socketState);
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void connected();
    void readyRead();

private:
    QString message;
    QTextStream *t;
    QTcpSocket *socket;
    QString from;
    QString rcpt;
    QString response;
    QString user;
    QString pass;
    QString server;
    int x;
    QStringList recips;
    enum States {Init, Auth, User, Pass, Mail, Rcpt, Data, Body, Quit, Close};
    int state;
};

#endif
