#ifndef SMTP_H
#define SMTP_H
#include<QByteArray>
#include<QString>
#include<QTcpSocket>
class Smtp
{
public:
    Smtp();
    Smtp(QByteArray username,QByteArray password);
    ~Smtp();
    void send(QByteArray recvaddr,QString subject,QString content);
    void setAccount(QByteArray username,QByteArray password);
private:
    QTcpSocket * clientsocket;
    QByteArray username;
    QByteArray password;
    QByteArray recvaddr;
    QByteArray mailfrom = "mail from:<";
    QByteArray rcptto = "rcpt to:<";
    QByteArray prefrom = "from:";
    QByteArray preto = "to:";
    QByteArray presubject ="subject:";
    QString subject;                //主题
    QString content;                //发送内容
    QByteArray recvdata;            //接收到的数据
};
#endif // SMTP_H
