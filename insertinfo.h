#ifndef INSERTINFO_H
#define INSERTINFO_H
#include <QDialog>
#include<QComboBox>
#include<QDateTimeEdit>
#include"toast/toast.h"
#include"smtp/smtp.h"
#include<QRandomGenerator>
#include<QRegExp>
#include<QtConcurrent>
#include"book.h"
#include"reader.h"
namespace Ui {
class insertInfo;
}

class insertInfo : public QDialog
{
    Q_OBJECT

public:
    explicit insertInfo(bool isForBook,QWidget *parent = nullptr);//最后一个参数只能够是指定父亲的指针，否则会报错
    ~insertInfo();
    void reg();

private slots:
    void on_cancelButton_clicked();

    void on_summitButton_clicked();

    void on_cancelButton_2_clicked();

    void on_sendButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::insertInfo *ui;
    bool forBook;
    bool forReg=false;
    int verificationCode;
    QString email;
    QComboBox* rk;
    QComboBox* se;
    Book book;
    Reader reader;
};

#endif // INSERTINFO_H
