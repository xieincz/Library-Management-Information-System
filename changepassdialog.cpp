#include "changepassdialog.h"
#include "ui_changepassdialog.h"

changePassDialog::changePassDialog(bool isForReader,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changePassDialog)
{
    ui->setupUi(this);
    forReader=isForReader;
    QFont font;
    font.setPointSize(15);
    this->setWindowTitle("修改密码");
    ui->userIDInput->setLabelText("请输入账号ID");
    ui->captchaLabelInput->setLabelText("请输入上图的文字");
    ui->emailCodeInput->setLabelText("请输入收到的邮件验证码");
    ui->inputPassWidget->hide();
    ui->passInput_1->setLabelText("请输入新的密码");
    ui->passInput_2->setLabelText("请再次输入新的密码");
}

changePassDialog::~changePassDialog()
{
    verificationCode=0;
    delete ui;
}

void changePassDialog::on_sendButton_clicked()
{
    if(ui->userIDInput->text().trimmed().isEmpty())
    {
        ui->userIDInput->showWrong("请输入用户账号ID");
        return;
    }
    bool success=false;
    if(forReader)
        success=reader.setReaderID(ui->userIDInput->text().trimmed());
    else
        success=admin.setAdminID(ui->userIDInput->text().trimmed());
    if(!success)
    {
        Toast::showMsg("无法找到相关账号的信息");
        ui->userIDInput->showWrong("无法找到该ID的信息");
        return;
    }
    id=ui->userIDInput->text().trimmed();
    if(ui->captchaLabelInput->text().trimmed().isEmpty())
    {
        ui->captchaLabelInput->showWrong("验证码不匹配，请重新输入");
        return;
    }
    if(ui->captchaLabel->checkCaptcha(ui->captchaLabelInput->text().trimmed()))
    {
        verificationCode =  QRandomGenerator::global()->bounded(10000, 99999);
        QString msg = QString("验证码为 %1 ，若非本人操作，请勿告诉他人。").arg(verificationCode);
        //异步发送验证码，防止卡界面
        if(forReader){
            QFuture<void> future = QtConcurrent::run([=]() {
                reader.sendEmail("图书馆验证码",msg);
            });
            Toast::showMsg(QString("   验证码已经发送到注册邮箱 %1   ").arg(reader.getEmail()));
        }else{
            QFuture<void> future = QtConcurrent::run([=]() {
                admin.sendEmail("图书馆验证码",msg);
            });
            Toast::showMsg(QString("   验证码已经发送到注册邮箱 %1   ").arg(admin.getEmail()));
        }
        ui->captchaLabel->generateCaptcha();//更新验证码
        ui->captchaLabelInput->setText("");//清空输入框
    }
    else
        ui->captchaLabelInput->showWrong("验证码不匹配，请重新输入");
}


void changePassDialog::on_cancelButton_clicked()
{
    verificationCode=0;
    this->close();
}


void changePassDialog::on_confirmButton_clicked()
{
    if(ui->emailCodeInput->text().trimmed().isEmpty())
    {
        ui->emailCodeInput->showWrong("请输入验证码");
        return;
    }
    if(ui->emailCodeInput->text().trimmed().toInt()==verificationCode)
    {
        Toast::showMsg("验证码正确，请输入新的密码",ToastTime::ToastTime_short);
        ui->sendEmailWidget->hide();
        ui->inputPassWidget->show();
    }
    else
    {
        Toast::showMsg("验证码错误",ToastTime::ToastTime_short);
        ui->emailCodeInput->showWrong("请检查输入的验证码");
    }

}


void changePassDialog::on_cancelButton_2_clicked()
{
    verificationCode=0;
    this->close();
}


void changePassDialog::on_confirmPassButton_clicked()
{
    if(ui->passInput_1->text().trimmed().isEmpty()&&ui->passInput_2->text().trimmed().isEmpty())
    {
        ui->passInput_1->showWrong("请输入密码");
        ui->passInput_2->showWrong("请输入密码");
        return;
    }
    bool success=false;
    QString p1=ui->passInput_1->text().trimmed(),p2=ui->passInput_2->text().trimmed();
    if(p1==p2)
    {
        //把密码更新到数据库
        if(forReader)
        {
            reader.setReaderID(id);
            success=reader.changePassword(p1);
        }
        else
        {
            admin.setAdminID(id);
            success=admin.changePassword(p1);
        }
        if(success)
        {
            Toast::showMsg("密码修改成功",ToastTime::ToastTime_short);
            this->close();
        }
        else
            Toast::showMsg("密码修改失败，请检查网络连接",ToastTime::ToastTime_short);

    }
    else
    {
        ui->passInput_1->showWrong("两次输入的密码不一致");
        ui->passInput_2->showWrong("两次输入的密码不一致");
    }
}
