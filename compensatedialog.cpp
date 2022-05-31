#include "compensatedialog.h"
#include "ui_compensatedialog.h"

compensateDialog::compensateDialog(QString thereaderID,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::compensateDialog)
{
    ui->setupUi(this);
    readerID=thereaderID;
    QFont font;
    this->setWindowTitle("赔偿处理");
    font.setPointSize(15);
    ui->comboBox->addItem("损坏");
    ui->comboBox->addItem("丢失");
    ui->doubleSpinBox->setMaximum(99999999999);
    ui->isbnInput->setLabelText("请输入ISBN");
}

compensateDialog::~compensateDialog()
{
    delete ui;
}

void compensateDialog::on_searchButton_clicked()
{
    if(ui->isbnInput->text().trimmed().isEmpty())
        Toast::showMsg("请输入ISBN");
    else
    {
        isbn=ui->isbnInput->text().trimmed();
        if(!book.setISBN(isbn))
        {
            Toast::showMsg("未找到此书");
            ui->isbnInput->showWrong("请检查输入的ISBN");
            return;
        }
        double p=book.getPrice();
        ui->adviceLabel->setText(QString("本书原价 %1 元").arg(p));
        ui->doubleSpinBox->setValue(p);
    }
}

void compensateDialog::setOutOftime(int thetime,QString theisbn)
{
    isbn=theisbn;
    time=thetime;
    ui->adviceLabel->setText(QString("共超期 %1 天").arg(time));
    ui->doubleSpinBox->setValue(time*0.1);
    ui->isbnInput->hide();
    ui->comboBox->removeItem(0);
    ui->comboBox->addItem("超期归还");
    ui->comboBox->removeItem(0);
    ui->comboBox->setCurrentText("超期归还");
    ui->searchButton->hide();
}

void compensateDialog::on_confirmButton_clicked()
{
    if(ui->doubleSpinBox->value()==0)
    {
        Toast::showMsg("请输入赔偿金额");
        return;
    }
    QString kind=ui->comboBox->currentText();
    book.setISBN(isbn);
    if(book.compensate(readerID,kind))
    {
        this->accept();
        return;
    }
    this->close();
}


void compensateDialog::on_cancelButton_clicked()
{
    reject();
    this->close();
}

