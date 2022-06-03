#include "reader.h"

Reader::Reader()
{
    borrowNumber=0,period=0,renewal=0;
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
          Toast::showMsg("无法连接到数据库，请检查网络");
    }
}

Reader::Reader(const Reader &r)
{
    readerID=r.readerID,name=r.name,readerKind=r.readerKind,sex=r.sex,phone=r.phone;
    email=r.email,remark=r.remark,password=r.password,registerDate=r.registerDate;
    borrowNumber=r.borrowNumber,period=r.period,renewal=r.renewal;
}

bool Reader::newReader(QString readerID, QString name, QString readerKind, QString sex, QString phone, QString email, QString remark, QString password,QDate registerDate,int borrowNumber, int period, int renewal)
{
    QSqlQuery q;//一定要在QSqlDatabase建立了数据库连接后声明才能正常连接到数据库执行SQL
    q.prepare("insert into reader(reader_id,password,name,reader_kind,"
              "sex,phone,email,borrow_number,period,renewal,register_date,"
              "remark) values(:reader_id,:password,:name,:reader_kind,:sex,"
              ":phone,:email,:borrow_number,:period,:renewal,:register_date,:remark)");
    q.bindValue(":reader_id",readerID);
    q.bindValue(":password",encryptPass(password));//对密码加盐哈希处理
    q.bindValue(":name",name);
    q.bindValue(":reader_kind",readerKind);
    q.bindValue(":sex",sex);
    q.bindValue(":phone",phone);
    q.bindValue(":email",email);
    q.bindValue(":borrow_number",borrowNumber);
    q.bindValue(":period",period);
    q.bindValue(":renewal",renewal);
    q.bindValue(":register_date",registerDate);
    q.bindValue(":remark",remark);
    return q.exec();
}

bool Reader::deleteReader(QString readerID)
{
    QSqlQuery q;
    q.prepare("delete from reader where reader_id=:reader_id");
    q.bindValue(":reader_id",readerID);
    return q.exec();
}

bool Reader::setReaderID(QString readerID)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM reader WHERE reader_id=:readerID");
    q.bindValue(":readerID", readerID);//把占位符替换为传入的参数，可以有效防止SQL注入
    if(!q.exec())//没执行成功
        return false;
    if(!q.next())//没找到
        return false;
    this->readerID=readerID;
    period=q.value("period").toInt();//借阅期限
    renewal=q.value("renewal").toInt();//续借次数
    borrowNumber=q.value("borrow_number").toInt();//可借阅数目
    name=q.value("name").toString();
    readerKind=q.value("reader_kind").toString();
    sex=q.value("sex").toString();
    phone=q.value("phone").toString();
    email=q.value("email").toString();
    remark=q.value("remark").toString();
    registerDate=q.value("register_date").toString();
    password=q.value("password").toString();
    return true;
}

bool Reader::readerLogin(QString readerID, QString password)
{
    setReaderID(readerID);
    return this->password==encryptPass(password);
}


int Reader::getBorrowNumber()const
{
    return borrowNumber;
}

int Reader::getPeriod()const
{
    return period;
}

int Reader::getRenewal()const
{
    return renewal;
}

QString Reader::getEmail()const
{
    return email;
}

QString Reader::getReaderID()const
{
    return readerID;
}

void Reader::clear()
{
    readerID.clear(),name.clear(),readerKind.clear(),sex.clear(),phone.clear();
    email.clear(),remark.clear(),password.clear(),registerDate.clear();
    borrowNumber=0,period=0,renewal=0;
}

bool Reader::changePassword(QString password)
{
    QSqlQuery q;
    q.prepare("update reader set password=:password where reader_id=:reader_id");
    q.bindValue(":reader_id",readerID);
    q.bindValue(":password",encryptPass(password));
    if(!q.exec())
        return false;
    this->password=encryptPass(password);
    return true;
}

void Reader::sendEmail(QString title,QString content)
{
    sendEmail({email,title,content});
}

void Reader::sendEmail(Email email)
{
    Smtp send("rolbo@qq.com","colbhvhayglsdjdg");
    send.send(email.email.toUtf8(),email.title,email.content);
}

int Reader::renewBook(QString ISBN)
{
    QSqlQuery q;
    q.prepare("select renew_times from borrow_return where reader_id"
              "=:reader_id and isbn=:isbn and return_date is null");
    q.bindValue(":reader_id",readerID);
    q.bindValue(":isbn",ISBN);
    q.exec();
    if(q.next())
    {
        int rt=q.value(0).toInt();
        if(rt<renewal)
        {
            q.prepare("update borrow_return set renew_times=renew_times+1 "
                      "where reader_id=:reader_id and isbn=:isbn and return_date is null");
            q.bindValue(":reader_id",readerID);
            q.bindValue(":isbn",ISBN);
            if(q.exec())
                return 1;
        }
        else
            //已达到最大续借次数
            return -1;
    }
    else
        //未查询到此书的借阅记录
        return -2;
    return 0;
}

void Reader::operator=(const Reader &r)
{
    readerID=r.readerID,name=r.name,readerKind=r.readerKind,sex=r.sex,phone=r.phone;
    email=r.email,remark=r.remark,password=r.password,registerDate=r.registerDate;
    borrowNumber=r.borrowNumber,period=r.period,renewal=r.renewal;
}
