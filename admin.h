#ifndef ADMIN_H
#define ADMIN_H

#include "reader.h"

class Admin : private Reader
{
public:
    Admin();
    bool setAdminID(QString adminID);
    void sendEmail(QString title,QString content);
    void clear();
    bool changePassword(QString password);
    bool adminLogin(QString adminID,QString password);
    QString getEmail();

private:
    QString adminID;
    QString name;
    QString password;
    QString email;
    QString entryDate;
    QString remark;
};

#endif // ADMIN_H
