#ifndef COMPENSATEDIALOG_H
#define COMPENSATEDIALOG_H
#include <QDialog>
#include <QDate>
#include"toast/toast.h"
#include"book.h"
namespace Ui {
class compensateDialog;
}

class compensateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit compensateDialog(QString thereaderID,QWidget *parent = nullptr);
    ~compensateDialog();
    void setOutOftime(int thetime,QString theisbn);

private slots:
    void on_searchButton_clicked();
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::compensateDialog *ui;

    QString readerID;
    int time=0;
    QString isbn;
    Book book;
};

#endif // COMPENSATEDIALOG_H
