#include "book.h"

Book::Book()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else{
      db = QSqlDatabase::addDatabase("QMYSQL");
      db.setHostName(hostName);
      db.setDatabaseName("lmis");
      db.setPort(3306);
      db.setUserName("root");//数据库账号
      db.setPassword("G6Sd@ZndSU&G");
      if(!db.open())//创建数据库连接
      {
          Toast::showMsg("无法连接到数据库，请检查网络");
      }
    }
}

bool Book::newBook(QString theISBN, QString theBookName, QString theAuthor, QString thePublishingHouse, QString theKeyword, QString theBookKind, QString theClassificationNumber, QDate thePublicationDate,QString theRemark,double thePrice,int theTotalNumber)
{
    QSqlQuery q;
    q.prepare("insert into book(isbn,book_name,book_kind,"
              "classification_number,keyword,publication_date,"
              "publishing_house,author,price,total_number,lend_number,remark"
              ") values(:isbn,:book_name,:book_kind,:classification_number,"
              ":keyword,:publication_date,:publishing_house,:author,:price,"
              ":total_number,0,:remark)");
    q.bindValue(":isbn",theISBN);
    q.bindValue(":book_name",theBookName);
    q.bindValue(":book_kind",theBookKind);
    q.bindValue(":classification_number",theClassificationNumber);
    q.bindValue(":keyword",theKeyword);
    q.bindValue(":publication_date",thePublicationDate);
    q.bindValue(":publishing_house",thePublishingHouse);
    q.bindValue(":author",theAuthor);
    q.bindValue(":price",thePrice);
    q.bindValue(":total_number",theTotalNumber);
    q.bindValue(":remark",theRemark);
    if(q.exec())
        return true;
    return false;
}

bool Book::deleteBook(QString theISBN)
{
    QSqlQuery q;
    q.prepare("delete from book where isbn=:isbn");
    q.bindValue(":isbn",theISBN);
    if(!q.exec())
    {
        Toast::showMsg("数据修改失败");
        return false;
    }
    return true;
}

bool Book::lossCopy()
{
    QSqlQuery q;
    q.prepare("update book set total_number=total_number-1 where isbn=:isbn");
    q.bindValue(":isbn",isbn);
    q.exec();
    return true;
}

bool Book::lend(QString readerID,int borrow_number)
{
    QSqlQuery q;
    //还需要检查是否未归还，并且提示
    q.prepare("select renew_times from borrow_return where reader_id=:reader_id and isbn=:isbn and return_date is null");
    q.bindValue(":reader_id",readerID);
    q.bindValue(":isbn",isbn);
    q.exec();
    if(q.next())
    {
        Toast::showMsg("检测到这本书已被当前读者借阅，且未归还");
        Toast::showMsg("请归还后再借或选择续借");
        return false;
    }

    //检查目前未归还的书本数目
    q.prepare("select reader_id,count(*) as count from borrow_return where reader_id"
      "=:reader_id and return_date is null group by reader_id");
    q.bindValue(":reader_id",readerID);
    q.exec();
    if(q.next())
    {
        int count=q.value("count").toInt();//未归还的书本数目
        if(count>=borrow_number)
        {
            Toast::showMsg("当前借阅数目达到上限，请归还部分书籍后再借阅");
            return false;
        }
    }
    //检查借出数目和馆藏数目
    q.prepare("select total_number,lend_number from book where isbn=:isbn");
    q.bindValue(":isbn",isbn);
    q.exec();
    if(q.next())
    {
        int total_number=q.value("total_number").toInt();
        int lend_number=q.value("lend_number").toInt();
        if(total_number<=lend_number)
        {
            Toast::showMsg("这本书已经全部借出，请确认此书是否是其他读者已借阅但未归还的");
            return false;
        }
    }
    else
    {
        Toast::showMsg("未查询到相关图书");
        return false;
    }
    q.prepare("insert into borrow_return(isbn,reader_id,borrow_date,renew_times) values(:isbn,:reader_id,:borrow_date,0)");
    q.bindValue(":borrow_date",QDate::currentDate());
    q.bindValue(":reader_id",readerID);
    q.bindValue(":isbn",isbn);
    q.exec();
    //借出加一
    q.prepare("update book set lend_number=lend_number+1 where isbn=:isbn");
    q.bindValue(":isbn",isbn);
    q.exec();
    return true;
}

bool Book::returned(QString readerID)
{
    QSqlQuery q;
    q.prepare("update borrow_return set return_date=:today where reader_id=:reader_id and isbn=:isbn");
    q.bindValue(":today",QDate::currentDate());
    q.bindValue(":reader_id",readerID);
    q.bindValue(":isbn",isbn);
    q.exec();
    //借出减一
    q.prepare("update book set lend_number=lend_number-1 where isbn=:isbn");
    q.bindValue(":isbn",isbn);
    return true;
}


bool Book::setISBN(QString theISBN)
{
    QSqlQuery q;
    isbn=theISBN;
    //下面还要把本书的其他信息填充到这个类
    q.prepare("select * from book where isbn=:isbn");
    q.bindValue(":isbn",isbn);
    if(!q.exec())
        return false;
    if(!q.next())
        return false;
    isbn=theISBN;
    bookName=q.value("book_name").toString();
    bookKind=q.value("book_kind").toString();
    classificationNumber=q.value("classification_number").toString();
    keyword=q.value("keyword").toString();
    publicationDate=q.value("publication_date").toString();
    publishingHouse=q.value("publishing_house").toString();
    author=q.value("author").toString();
    remark=q.value("remark").toString();
    price=q.value("price").toDouble();
    totalNumber=q.value("total_number").toInt();
    lendNumber=q.value("lend_number").toInt();
    return true;

}

bool Book::compensate(QString readerID,QString kind,double money)
{
    QSqlQuery q;
    //还需要检查是否借阅过这本书，并且提示
    q.prepare("select renew_times from borrow_return where reader_id"
              "=:reader_id and isbn=:isbn and return_date is null");
    q.bindValue(":reader_id",readerID);
    q.bindValue(":isbn",isbn);
    q.exec();
    if(!q.next())
    {
        Toast::showMsg("检测到这本书未被当前读者借阅");
        Toast::showMsg("若要赔偿未借阅图书请添加借阅记录后再进行赔偿");
        return false;
    }

    q.prepare("insert into compensate(isbn,reader_id,compensation_date,money"
              ",compensation_kind) values(:isbn,:reader_id,:compensation_date"
              ",:money,:compensation_kind)");
    q.bindValue(":isbn",isbn);
    q.bindValue(":reader_id",readerID);
    q.bindValue(":compensation_date",QDate::currentDate());
    q.bindValue(":money",money);

    if(kind=="超期归还")
    {
        q.bindValue(":compensation_kind","超期归还");
        if(q.exec())
        {
            Toast::showMsg("赔偿成功",ToastTime::ToastTime_short);
            //return true;
        }else
            return false;

    }
    else if(kind=="丢失")
    {
        q.bindValue(":compensation_kind","丢失");
        q.exec();
        lossCopy();
    }
    else if(kind=="损坏")
    {
        q.bindValue(":compensation_kind","损坏");
        q.exec();
        lossCopy();
    }

    q.prepare("update book set lend_number=lend_number-1 where isbn=:isbn");
    q.bindValue(":isbn",isbn);
    q.exec();
    q.prepare("update borrow_return set return_date=:return_date where isbn=:isbn and reader_id=:reader_id");
    q.bindValue(":isbn",isbn);
    q.bindValue(":reader_id",readerID);
    q.bindValue(":return_date",QDate::currentDate());
    q.exec();
    Toast::showMsg("赔偿成功",ToastTime::ToastTime_short);
    return true;
}

int Book::overdue(QString readerID, int period)
{
    QSqlQuery q;
    //检查是否超期，并且要求赔偿
    q.prepare("select renew_times,borrow_date from borrow_return where reader_id"
              "=:reader_id and isbn=:isbn and return_date is null");
    q.bindValue(":reader_id",readerID);
    q.bindValue(":isbn",isbn);
    q.exec();
    if(q.next())
    {
        int rt=q.value(0).toInt();
        QDate borrow_date=q.value(1).toDate();
        int t=borrow_date.daysTo(QDate::currentDate())-(rt+1)*period;

        if(0<t)
            return t;
    }
    else
    {
        Toast::showMsg("未查询到相关未归还记录");
        return -1;
    }
    return 0;
}

double Book::getPrice() const
{
    return price;
}

void Book::lendNumberAdd(const int& num)
{
    QSqlQuery q;
    q.prepare("update book set lend_number=:lend_number where isbn=:isbn");
    q.bindValue(":isbn",isbn);
    q.bindValue(":lend_number",lendNumber+num);
    if(!q.exec())
        Toast::showMsg("数据修改失败");
}

void Book::totalNumberAdd(const int &num)
{
    QSqlQuery q;
    q.prepare("update book set total_number=:total_number where isbn=:isbn");
    q.bindValue(":isbn",isbn);
    q.bindValue(":total_number",totalNumber+num);
    if(!q.exec())
        Toast::showMsg("数据修改失败");
}
