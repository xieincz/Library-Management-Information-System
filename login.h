#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include"adminui.h"
#include"ui_adminui.h"

#include"readerui.h"
#include"ui_readerui.h"

#include"insertinfo.h"//读者注册

#include"changepassdialog.h"

#include"encryptpass.h"//密码加盐哈希处理
#include"reader.h"
#include"admin.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_readerLogin_clicked();

    void on_adminLogin_clicked();

    void on_readerRegister_clicked();

    void on_readerForgotPass_clicked();

    void on_adminForgotPass_clicked();

private:
    Ui::Login *ui;
    Reader reader;
    Admin admin;
};

#endif // LOGIN_H
