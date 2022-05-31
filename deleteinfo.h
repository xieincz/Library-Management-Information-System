#ifndef DELETEINFO_H
#define DELETEINFO_H
#include <QDialog>
#include"toast/toast.h"
#include"book.h"
#include"reader.h"
namespace Ui {
class deleteInfo;
}

class deleteInfo : public QDialog
{
    Q_OBJECT

public:
    explicit deleteInfo(bool isForBook,QWidget *parent = nullptr);
    ~deleteInfo();

private slots:
    void on_deleteButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::deleteInfo *ui;
    bool forBook;
    Book book;
    Reader reader;
};

#endif // DELETEINFO_H
