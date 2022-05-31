#ifndef BR_RE_CP_H
#define BR_RE_CP_H
#include <QDialog>
#include"toast/toast.h"
#include"compensatedialog.h"
#include"book.h"
#include"reader.h"
namespace Ui {
class br_Re_Cp;
}

enum opType{
    borrowBook,returnBook,changePassWord
};

class br_Re_Cp : public QDialog
{
    Q_OBJECT

public:
    explicit br_Re_Cp(Reader reader,opType theType,QWidget *parent = nullptr);
    ~br_Re_Cp();

private slots:
    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::br_Re_Cp *ui;
    opType type;
    Book book;
    Reader reader;
};

#endif // BR_RE_CP_H
