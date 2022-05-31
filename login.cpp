#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->usernanmeInput->setLabelText("账号");
    ui->usernanmeInput->setTipText("请输入学工号");
    ui->passInput->setLabelText("密码");
    ui->passInput->setTipText("请输入密码");
    this->setWindowTitle("登录界面");
    ui->usernanmeInput_2->setLabelText("账号");
    ui->usernanmeInput_2->setTipText("请输入管理员账号");
    ui->passInput_2->setLabelText("密码");
    ui->passInput_2->setTipText("请输入密码");
    ui->tabWidget->setCurrentWidget(ui->readerTab);//设置默认页面
}

Login::~Login()
{
    delete ui;
}

void Login::on_readerLogin_clicked()
{
    ui->usernanmeInput->showLoading();
    ui->passInput->showLoading();
    bool logined=reader.readerLogin(ui->usernanmeInput->text().trimmed(),ui->passInput->text().trimmed());
    //结束加载动画
    ui->usernanmeInput->hideLoading();
    ui->passInput->hideLoading();
    if(!logined)//登录失败
    {
        ui->usernanmeInput->showWrong("请检查输入的账号", true); // 错误的波浪线
        ui->passInput->showWrong("请检查输入的密码", true); // 错误的波浪线
        Toast::showMsg("用户名或密码错误",ToastTime::ToastTime_long);
        return;
    }
    ui->usernanmeInput->showCorrect(); // 正确的勾
    ui->passInput->showCorrect(); // 正确的勾
    Toast::showMsg("登陆成功",ToastTime::ToastTime_short);
    ReaderUI *readerui=new ReaderUI(reader,this);
    readerui->show();
    ui->usernanmeInput->editor()->setText("");//清空输入框
    ui->passInput->editor()->setText("");
    ui->usernanmeInput->hideCorrect();
    ui->passInput->hideCorrect();
    this->close();
}


void Login::on_adminLogin_clicked()
{
    ui->usernanmeInput_2->showLoading();
    ui->passInput_2->showLoading();
    bool logined=admin.adminLogin(ui->usernanmeInput_2->text().trimmed(),ui->passInput_2->text().trimmed());

    //结束加载动画
    ui->usernanmeInput_2->hideLoading();
    ui->passInput_2->hideLoading();
    if(!logined)//没登录成功
    {
        ui->usernanmeInput_2->showWrong("请检查输入的账号", true); // 错误的波浪线
        ui->passInput_2->showWrong("请检查输入的密码", true); // 错误的波浪线
        Toast::showMsg("用户名或密码错误",ToastTime::ToastTime_long);
        return;
    }
    ui->usernanmeInput_2->showCorrect(); // 正确的勾
    ui->passInput_2->showCorrect(); // 正确的勾
    Toast::showMsg("登陆成功",ToastTime::ToastTime_short);
    AdminUI *adminui=new AdminUI(this);
    adminui->show();
    ui->usernanmeInput_2->editor()->setText("");//清空输入框
    ui->passInput_2->editor()->setText("");
    ui->usernanmeInput_2->hideCorrect();
    ui->passInput_2->hideCorrect();
    this->close();
}


void Login::on_readerRegister_clicked()
{
    insertInfo* reg=new insertInfo(false,this);
    reg->reg();
    reg->exec();
}


void Login::on_readerForgotPass_clicked()
{
    changePassDialog* ch=new changePassDialog(true,this);
    ch->exec();
}


void Login::on_adminForgotPass_clicked()
{
    changePassDialog* ch=new changePassDialog(false,this);
    ch->exec();
}

