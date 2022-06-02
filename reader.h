#ifndef READER_H
#define READER_H
#include <QObject>
#include <QSqlQuery>
#include"smtp/smtp.h"
#include"encryptpass.h"//密码加盐哈希处理
#include"toast/toast.h"
#include<QDateTimeEdit>
struct Email{
    QString email,title,content;
    Email(const QString& emailAdress,const QString& title,const QString& content)
        :email(emailAdress),title(title),content(content){}
};

class Reader
{
public:
    Reader();
    Reader(const Reader& r);
    bool newReader(QString readerID="",QString name="",QString readerKind="",QString sex="",QString phone="",QString email="",QString remark="",QString password="",QDate registerDate=QDate::currentDate(),int borrowNumber=0,int period=0,int renewal=0);
    bool deleteReader(QString readerID);
    bool setReaderID(QString readerID);
    bool readerLogin(QString readerID,QString password);
    int getBorrowNumber()const;
    int getPeriod()const;
    int getRenewal()const;
    QString getEmail()const;
    QString getReaderID()const;
    void clear();
    bool changePassword(QString password);
    void sendEmail(QString title,QString content);
    void sendEmail(Email email);
    int renewBook(QString ISBN);//返回结果类型，1续借成功，-1达到最大续借次数，-2未查询到此书的借阅记录
    void operator=(const Reader& r);

protected:
    QString name;
    QString email;
    QSqlDatabase db;
    QString hostName="localhost";
    QString databaseName="lmis";

private:
    QString readerID;
    QString readerKind;
    QString sex;
    QString phone;
    QString remark;
    QString password;
    QString registerDate;
    int borrowNumber;
    int period;
    int renewal;
};

#endif // READER_H
