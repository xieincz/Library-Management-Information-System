#include "deleteinfo.h"
#include "ui_deleteinfo.h"

deleteInfo::deleteInfo(bool isForBook,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteInfo)
{
    ui->setupUi(this);
    forBook=isForBook;
    if(forBook)
    {
        this->setWindowTitle("删除书本");
    }
    else
    {
        this->setWindowTitle("删除读者账号");
        ui->label->setText("请输入要删除的读者的账号id");
    }
}

deleteInfo::~deleteInfo()
{
    delete ui;
}

void deleteInfo::on_deleteButton_clicked()
{
    if(ui->input->editor()->text().trimmed().isEmpty())
    {
        Toast::showMsg("请输入信息");
        return;
    }
    bool success=false;
    if(forBook)
        success=book.deleteBook(ui->input->text().trimmed());
    else
        success=reader.deleteReader(ui->input->text().trimmed());
    if(success)
    {
        Toast::showMsg("删除成功",ToastTime::ToastTime_short);
        ui->input->setText("");
        this->close();
    }
    else
        Toast::showMsg("删除失败，请检查输入的数据");
}


void deleteInfo::on_cancelButton_clicked()
{
    this->close();
}

