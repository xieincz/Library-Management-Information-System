#include "br_re_cp.h"
#include "ui_br_re_cp.h"

br_Re_Cp::br_Re_Cp(Reader reader,opType theType,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::br_Re_Cp)
{
    ui->setupUi(this);
    type=theType;
    this->reader=reader;
    QFont font;
    font.setPointSize(15);

    switch (type)
    {
    case returnBook://还书
    {
        this->setWindowTitle("还书");
        ui->input->setLabelText("请输入ISBN");
        break;
    }
    case borrowBook://借书
    {
        this->setWindowTitle("借书");
        ui->label->setText("请输入要借阅的图书的ISBN");
        ui->input->setLabelText("请输入ISBN");
        break;
    }
    case changePassWord://修改密码
    {
        this->setWindowTitle("修改密码");
        ui->label->setText("请输入要修改的密码");
        ui->input->setLabelText("请输入密码");
        break;
    }
    }
}

br_Re_Cp::~br_Re_Cp()
{
    delete ui;
}

void br_Re_Cp::on_confirmButton_clicked()
{
    if(ui->input->text().trimmed().isEmpty())
    {
        Toast::showMsg("请输入内容");
        ui->input->showWrong("输入不能为空",true);
        return;
    }
    switch (type)
    {
    case returnBook://还书
    {
        if(!book.setISBN(ui->input->text().trimmed()))
        {
            ui->input->showWrong("请检查输入的ISBN是否正确");
            return;
        }
        int t=book.overdue(reader.getReaderID(),reader.getPeriod());
        if(t==0)
            book.returned(reader.getReaderID());
        else if(t>0)
        {
            compensateDialog* co=new compensateDialog(reader.getReaderID());
            co->setOutOftime(t,ui->input->text().trimmed());
            Toast::showMsg("这本书已经超期归还，正在进入赔偿界面",ToastTime::ToastTime_short);
            if(co->exec()!=co->Accepted)
                Toast::showMsg("检测到未赔偿或赔偿失败，请重试");
        }
        break;
    }
    case borrowBook://借书
    {
        if(!book.setISBN(ui->input->text().trimmed()))
        {
            ui->input->showWrong("请检查输入的ISBN是否正确");
            return;
        }
        book.lend(reader.getReaderID(),reader.getBorrowNumber());
        break;
    }
    case changePassWord://修改密码
    {
        reader.setReaderID(reader.getReaderID());
        reader.changePassword(ui->input->text().trimmed());
        break;
    }
    }
    this->close();
}


void br_Re_Cp::on_cancelButton_clicked()
{
    this->close();
}
