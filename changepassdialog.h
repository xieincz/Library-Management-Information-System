#ifndef CHANGEPASSDIALOG_H
#define CHANGEPASSDIALOG_H
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include"encryptpass.h"//密码加盐哈希处理
#include<QtConcurrent>
#include"captchabox/captchabox.h"
#include"toast/toast.h"
#include<QRandomGenerator>
#include"reader.h"
#include"admin.h"
namespace Ui {
class changePassDialog;
}

class changePassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changePassDialog(bool isForReader,QWidget *parent = nullptr);
    ~changePassDialog();

private slots:
    void on_sendButton_clicked();

    void on_cancelButton_clicked();

    void on_confirmButton_clicked();

    void on_cancelButton_2_clicked();

    void on_confirmPassButton_clicked();

private:
    Ui::changePassDialog *ui;
    bool forReader;
    QString id;
    int verificationCode;
    Reader reader;
    Admin admin;
};

#endif // CHANGEPASSDIALOG_H
