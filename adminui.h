#ifndef ADMINUI_H
#define ADMINUI_H
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QScrollBar>
#include"toast/toast.h"
#include"batchimport.h"
#include"insertinfo.h"
#include"readonlydelegate.h"
#include"deleteinfo.h"
#include"br_re_cp.h"
#include"compensatedialog.h"
#include"reader.h"
#include"book.h"
#include<QtConcurrent>//用于多线程
namespace Ui {
class AdminUI;
}

class AdminUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminUI(QWidget *parent = nullptr);
    ~AdminUI();

private:
    Ui::AdminUI *ui;
private slots:
    void on_adminLogout_clicked();
    void on_readerInfo_clicked();
    void on_bookInfo_clicked();
    void on_readerService_clicked();
    void on_addBook_clicked();

    void on_editBook_clicked();

    void on_deleteBook_clicked();

    void on_searchButton_clicked();

    void on_submitChange_clicked();

    void on_giveUpChange_clicked();

    void on_editReader_clicked();

    void on_deleteReader_clicked();

    void on_readerBorrow_clicked();

    void on_readerReturn_clicked();

    void on_changePass_clicked();

    void on_lossOrbroke_clicked();

    void on_readerIdConfirmButton_clicked();

    void on_addReader_clicked();

    void on_batchImportButton_clicked();

private:
    void showAllBook();
    void showAllReader();
    Reader reader;
    Book book;
    QSqlTableModel model;
};

#endif // ADMINUI_H
