#include "insertinfo.h"
#include "ui_insertinfo.h"

insertInfo::insertInfo(bool isForBook,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insertInfo)
{
    ui->setupUi(this);
    forBook=isForBook;
    ui->sendEmailWidget->hide();
    ui->captchaLabelInput->setLabelText("请输入上图的文字");
    ui->emailCodeInput->setLabelText("请输入收到的邮件验证码");
    if(forBook)
    {
        this->setWindowTitle("新增书本");
        ui->w11->setLabelText("ISBN");
        ui->w12->setLabelText("书名");
        ui->w21->setLabelText("中图分类号");
        ui->w22->setLabelText("关键词");
        ui->w31->setLabelText("作者");
        ui->dateEdit->setMaximumDate(QDate::currentDate());//出版日期不能是未来的时间
        ui->w32->setLabelText("出版社");
        ui->w41->setLabelText("备注");
        ui->w42->setLabelText("图书类型");
        ui->doubleSpinBox->setRange(0,99999999999);
        ui->spinBox->setRange(1,999999999);
    }
    else
    {
        this->setWindowTitle("新增读者账号");
        ui->w11->setLabelText("学工号");
        ui->w12->setLabelText("密码");
        ui->w21->setLabelText("名字");
        ui->w22->setLabelText("电话");
        ui->w31->setLabelText("电子邮箱");
        ui->w32->setLabelText("备注");
        ui->dateEdit->hide();
        ui->doubleSpinBox->hide();
        ui->spinBox->hide();
        ui->pdate->hide();
        ui->price->hide();
        ui->w41->hide();
        ui->w42->hide();
        rk=new QComboBox(this);
        se=new QComboBox(this);
        this->resize(580,450);//重新调整窗口大小
        rk->setGeometry(60,300,200,60);
        se->setGeometry(320,300,200,60);
        ui->summitButton->move(60,390);
        ui->cancelButton->move(320,390);
        rk->addItem("本科生");
        rk->addItem("研究生");
        rk->addItem("教职工");
        rk->addItem("其他");
        se->addItem("男");
        se->addItem("女");
        ui->number->hide();
    }

}

void insertInfo::reg()
{
    forReg=true;
}

insertInfo::~insertInfo()
{
    delete ui;
}

void insertInfo::on_cancelButton_clicked()
{
    this->close();
}


void insertInfo::on_summitButton_clicked()
{
    int count=0;
    bool success=false;
    if(forBook)
    {
        //正则表达式检查是否为isbn
        QRegularExpression id("^(\\d{10}|\\d{13})\\s*$");
        QRegularExpressionMatch matchid = id.match(ui->w11->text().trimmed());
        if (!matchid.hasMatch())
        {
            ui->w11->showWrong("请正确填写10位或13位ISBN");
            count++;
        }
        //检查isbn是否已经存在
        if(book.setISBN(ui->w11->text().trimmed()))
        {
            Toast::showMsg("这本书已经存在，请使用书籍修改功能");
            ui->w11->showWrong("数据库中已存在此书，请检查ISBN");
            return;
        }
        if(ui->w12->editor()->text().trimmed().isEmpty())
        {
            ui->w12->showWrong("请填写书名",true);
            count++;
        }
        if(ui->w21->editor()->text().trimmed().isEmpty())
        {
            ui->w21->showWrong("请填写中图分类号",true);
            count++;
        }
        if(ui->w22->editor()->text().trimmed().isEmpty())
        {
            ui->w22->showWrong("请填写关键词",true);
            count++;
        }
        if(ui->w31->editor()->text().trimmed().isEmpty())
        {
            ui->w31->showWrong("请填写作者",true);
            count++;
        }
        if(ui->w32->editor()->text().trimmed().isEmpty())
        {
            ui->w32->showWrong("请填写出版社",true);
            count++;
        }
        if(ui->w42->editor()->text().trimmed().isEmpty())
        {
            ui->w42->showWrong("请填写图书类型",true);
            count++;
        }
        if(count>0)
        {
            Toast::showMsg("缺少必要的信息，请完整填写信息");
            return;
        }
        success=book.newBook(ui->w11->text().trimmed(),ui->w12->text().trimmed(),ui->w31->text().trimmed(),ui->w32->text().trimmed(),ui->w22->text().trimmed(),ui->w42->text().trimmed(),ui->w21->text().trimmed(),ui->dateEdit->date(),ui->w41->text().trimmed(),ui->doubleSpinBox->value(),ui->spinBox->value());

    }
    else
    {
        //正则表达式检查是否为Email
        QRegularExpression regExpEmail("[a-zA-Z0-9-_]+@[a-zA-Z0-9-_]+\\.[a-zA-Z]+");
        QRegularExpressionMatch match = regExpEmail.match(ui->w31->text().trimmed());
        if (!match.hasMatch())
        {
            ui->w31->showWrong("电子邮件格式错误，正确示例：abc123@qq.com");
            count++;
        }

        //正则表达式检查是否为学工号
        QRegularExpression id("^\\d{12}$");
        QRegularExpressionMatch matchid = id.match(ui->w11->text().trimmed());
        if (!matchid.hasMatch())
        {
            ui->w11->showWrong("学工号格式错误，请输入12位数字");
            count++;
        }

        //正则表达式检查是否为手机号
        QRegularExpression ph("^(13[0-9]|14[5|7]|15[0|1|2|3|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|9])\\d{8}$");
        QRegularExpressionMatch matchph = ph.match(ui->w22->text().trimmed());
        if (!matchph.hasMatch())
        {
            ui->w22->showWrong("手机号格式错误，请输入正确的手机号");
            count++;
        }

        //检查学工号是否已经存在
        if(reader.setReaderID(ui->w11->text().trimmed()))
        {
            Toast::showMsg("这名读者已经注册，请使用读者信息修改功能");
            ui->w11->showWrong("数据库中已存在此读者，请检查学工号");
            return;
        }
        if(ui->w12->editor()->text().trimmed().isEmpty())
        {
            ui->w12->showWrong("请填写密码",true);
            count++;
        }
        if(ui->w21->editor()->text().trimmed().isEmpty())
        {
            ui->w21->showWrong("请填写姓名",true);
            count++;
        }


        if(count>0)
        {
            Toast::showMsg("缺少必要的信息，请完整填写信息");
            return;
        }
        int bn=0,pe=0,re=0;
        switch (rk->currentIndex())//根据读者类型进行一些数据的自动填充
        {
            case 0:
            {
                bn=25;
                pe=30;
                re=3;
                break;
            }
            case 1:
            {
                bn=30;
                pe=60;
                re=4;
                break;
            }
            case 2:
            {
               bn=35;
               pe=30;
               re=3;
               break;
            }
            case 3:
            {
                bn=10;
                pe=30;
                re=1;
                break;
            }
            default:
                break;
        }

        //此处要进行邮箱的验证
        if(forReg)
        {
            email=ui->w31->text().trimmed();
            ui->sendEmailWidget->show();
            ui->iw->hide();
            rk->hide();
            se->hide();
            return;//后面的操作交给验证页面完成
        }
        success=reader.newReader(ui->w11->text().trimmed(),ui->w21->text().trimmed(),rk->currentText().trimmed(),se->currentText().trimmed(),ui->w22->text().trimmed(),ui->w31->text().trimmed(),ui->w32->text().trimmed(),ui->w12->text().trimmed(),QDate::currentDate().toString(),bn,pe,re);
    }
    if(success)
    {
        Toast::showMsg("信息添加成功",ToastTime::ToastTime_short);
        this->close();
        return;
    }
    Toast::showMsg("信息添加失败，请检查网络连接");
}


void insertInfo::on_cancelButton_2_clicked()
{
    ui->iw->show();
    rk->show();
    se->show();
    ui->sendEmailWidget->hide();
}

void insertInfo::on_sendButton_clicked()
{
    if(ui->captchaLabelInput->text().trimmed().isEmpty())
    {
        ui->captchaLabelInput->showWrong("验证码不匹配，请重新输入");
        return;
    }
    if(ui->captchaLabel->checkCaptcha(ui->captchaLabelInput->text().trimmed()))
    {
        //异步发送验证码，防止卡界面
        QFuture<void> future = QtConcurrent::run([=]() {
            //发送验证码
            //产生一个5位数的随机数
            //将验证码加入字符串
            verificationCode =  QRandomGenerator::global()->bounded(10000, 99999);
            reader.sendEmail({email,"图书馆验证码",QString("验证码为 %1 ，若非本人操作，请勿告诉他人。").arg(verificationCode)});
        });
        Toast::showMsg(QString("  验证码已经发送到注册邮箱 %1  ").arg(email));
        ui->captchaLabel->generateCaptcha();//更新验证码
        ui->captchaLabelInput->setText("");//清空输入框
    }
    else
    {
        ui->captchaLabelInput->showWrong("验证码不匹配，请重新输入");
    }
}


void insertInfo::on_confirmButton_clicked()
{
    if(ui->emailCodeInput->text().trimmed().isEmpty())
    {
        ui->emailCodeInput->showWrong("请输入验证码");
        return;
    }
    if(ui->emailCodeInput->text().trimmed().toInt()==verificationCode)
    {
        Toast::showMsg("验证码正确，正在为您添加账号信息",ToastTime::ToastTime_short);
        forReg=false;
        on_summitButton_clicked();//调用前面的方法插入账号信息
    }
    else
    {
        Toast::showMsg("验证码错误",ToastTime::ToastTime_short);
        ui->emailCodeInput->showWrong("请检查输入的验证码");
    }
}

