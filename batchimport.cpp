#include "batchimport.h"

bool batchImport(bool isForReader,QWidget *parent)
{
    QString path = QFileDialog::getOpenFileName(parent,QObject::tr("请选择CSV文件进行导入"),".",QObject::tr("CSV文件(*.csv)"));
    if(path.isEmpty())
    {
        Toast::showMsg("你没有选择任何文件");
        return false;
    }
    Toast::showMsg("开始导入",ToastTime::ToastTime_short);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))//读取csv数据到数据表
    {
        QMessageBox::warning(parent,QObject::tr("读取文件出错"),QObject::tr("无法打开文件:\n%1").arg(path));
        return false;
    }
    QTextStream in(&file);//QTextStream读取数据
    QSqlQuery q;
    QStringList list;
    list.clear();
    QString fileLine = in.readLine();//跳过第一行
    if(isForReader)
    {
        while(!in.atEnd())
        {
           fileLine = in.readLine();  //从第一行读取至下一行
           list = fileLine.split(",");//这里针对的是采用逗号作为分隔符的CSV文件
           q.prepare("insert into reader(reader_id,password,name,reader_kind,"
                     "sex,phone,email,borrow_number,period,renewal,register_date,"
                     "remark) values(:reader_id,:password,:name,:reader_kind,:sex,"
                     ":phone,:email,:borrow_number,:period,:renewal,:register_date,:remark)");

           q.bindValue(":reader_id",list.at(0).toUtf8().trimmed());
           q.bindValue(":name",list.at(1).toUtf8().trimmed());
           q.bindValue(":reader_kind",list.at(2).toUtf8().trimmed());
           q.bindValue(":sex",list.at(3).toUtf8().trimmed());
           q.bindValue(":phone",list.at(4).toUtf8().trimmed());
           q.bindValue(":email",list.at(5).toUtf8().trimmed());
           q.bindValue(":borrow_number",list.at(6).toInt());
           q.bindValue(":period",list.at(7).toInt());
           q.bindValue(":renewal",list.at(8).toInt());
           q.bindValue(":register_date",QDate::currentDate());
           q.bindValue(":remark",list.at(9).toUtf8().trimmed());
           q.bindValue(":password",encryptPass(list.at(10).toUtf8().trimmed()));//对密码加盐哈希处理
           q.exec();
        }
    }
    else
    {
        while(!in.atEnd())
        {
           fileLine = in.readLine();  //从第一行读取至下一行
           list = fileLine.split(",");
           q.prepare("insert into book(isbn,book_name,book_kind,classification_number"
                     ",keyword,publication_date,publishing_house,author,price,total_number,"
                     "lend_number,remark) values(:isbn,:book_name,:book_kind,:classification_number,"
                     ":keyword,:publication_date,:publishing_house,:author,:price,:total_number,0,:remark)");
           q.bindValue(":isbn",list.at(0).toUtf8().trimmed());
           q.bindValue(":book_name",list.at(1).toUtf8().trimmed());
           q.bindValue(":book_kind",list.at(2).toUtf8().trimmed());
           q.bindValue(":classification_number",list.at(3).toUtf8().trimmed());
           q.bindValue(":keyword",list.at(4).toUtf8().trimmed());
           q.bindValue(":publication_date",list.at(5));
           q.bindValue(":publishing_house",list.at(6).toUtf8().trimmed());
           q.bindValue(":author",list.at(7).toUtf8().trimmed());
           q.bindValue(":price",list.at(8).toDouble());
           q.bindValue(":total_number",list.at(9).toInt());
           q.bindValue(":remark",list.at(10).toUtf8().trimmed());
           q.exec();
        }
    }
    q.clear();
    Toast::showMsg("导入完成",ToastTime::ToastTime_short);
    return true;
}
