#include "admin.h"

Admin::Admin(){}

bool Admin::setAdminID(QString adminID)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM admin WHERE admin_id=:admin_id");
    q.bindValue(":admin_id", adminID); //把占位符替换为传入的参数，可以有效防止SQL注入
    if(!q.exec())//没执行成功
        return false;
    if(!q.next())//没找到
        return false;
    this->adminID=adminID;
    name=q.value("name").toString();
    email=q.value("email").toString();
    remark=q.value("remark").toString();
    entryDate=q.value("entry_date").toString();
    password=q.value("password").toString();
    return true;
}

void Admin::sendEmail(QString title, QString content)
{
    Reader::name=name;
    Reader::email=email;
    Reader::sendEmail(title,content);
}

void Admin::clear()
{
    Reader::clear();
    name.clear(),password.clear(),adminID.clear(),email.clear(),entryDate.clear(),remark.clear();
}

bool Admin::changePassword(QString password)
{
    QSqlQuery q;
    q.prepare("update admin set password=:pass where admin_id=:id");
    q.bindValue(":id",adminID);
    q.bindValue(":pass",password);
    if(!q.exec())
        return false;
    this->password=encryptPass(password);
    return true;
}

bool Admin::adminLogin(QString adminID, QString password)
{
    setAdminID(adminID);
    return this->password==encryptPass(password);
}

QString Admin::getEmail()
{
    return email;
}
