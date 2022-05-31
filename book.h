#ifndef BOOK_H
#define BOOK_H
#include <QObject>
#include <QSqlQuery>
#include <QDate>
#include"toast/toast.h"

class Book
{
public:
    Book();
    Book(QString theISBN);
    bool newBook(QString theISBN,QString theBookName,QString theAuthor,QString thePublishingHouse,QString theKeyword,QString theBookKind,QString theClassificationNumber,QDate thePublicationDate,QString theRemark,double thePrice,int theTotalNumber);//新增书
    bool deleteBook(QString theISBN);//删除书
    bool lossCopy();//丢失了此书一个副本
    bool addCopy();//补充了此书一个副本
    bool lend(QString readerID,int borrow_number);//借给参数一个副本
    bool returned(QString readerID);//参数归还一本
    bool find(QString theISBN="",QString theBookName="",QString theAuthor="",QString thePublishingHouse="",QString theKeyword="",QString theBookKind="",QString theClassificationNumber="");
    bool setISBN(QString theISBN);
    bool compensate(QString readerID,QString kind,double money=0);
    int overdue(QString readerID,int period);
    double getPrice() const;
private:
    void lendNumberAdd(const int& num);
    void totalNumberAdd(const int& num);
    QString isbn;
    QString bookName;
    QString bookKind;
    QString classificationNumber;
    QString keyword;
    QString publicationDate;
    QString publishingHouse;
    QString author;
    QString remark;
    double price;
    int totalNumber;
    int lendNumber;
    QSqlDatabase db;
    QString hostName="localhost";
    QString databaseName="lmis";
};

#endif // BOOK_H
