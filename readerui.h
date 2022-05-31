#ifndef READERUI_H
#define READERUI_H
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QScrollBar>
#include"br_re_cp.h"
#include"toast/toast.h"
#include"book.h"
#include"reader.h"
#include<QtConcurrent>//用于多线程
namespace Ui {
class ReaderUI;
}

class ReaderUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReaderUI(Reader reader,QWidget *parent = nullptr);
    ~ReaderUI();

private:
    Ui::ReaderUI *ui;
private slots:
    void on_searchAndBorrow_clicked();

    void on_myBorrow_clicked();

    void on_readerLogout_clicked();

    void on_searchButton_clicked();

    void on_borrowButton_clicked();

    void on_renewBorrowButton_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    void showAllBook();
    void showBookRorUr(bool isRetuned);
    Book book;
    Reader reader;
    QSqlTableModel model;
};

#endif // READERUI_H
