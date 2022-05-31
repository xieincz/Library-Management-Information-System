#include "adminui.h"
#include "ui_adminui.h"

AdminUI::AdminUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminUI)
{
    ui->setupUi(this);
    this->setWindowTitle("管理员界面");
    ui->bookInfoTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);//垂直滚动条
    ui->bookInfoTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);//水平滚动条
    ui->bookInfoTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//垂直平滑滚动
    ui->bookInfoTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);//水平平滑滚动
    ui->readerInfoTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);//垂直滚动条
    ui->readerInfoTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);//水平滚动条
    ui->readerInfoTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//垂直平滑滚动
    ui->readerInfoTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);//水平平滑滚动
    ui->bookInfoTable->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{""background:#FFFFFF;""padding-top:20px;""padding-bottom:20px;""padding-left:3px;""padding-right:3px;""border-left:1px solid #d7d7d7;}""QScrollBar::handle:vertical{""background:#dbdbdb;""border-radius:6px;""min-height:80px;}");
    ui->bookInfoTable->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{""background:#FFFFFF;""padding-top:3px;""padding-bottom:3px;""padding-left:20px;""padding-right:20px;}""QScrollBar::handle:horizontal{""background:#dbdbdb;""border-radius:6px;""min-width:80px;}");
    ui->readerInfoTable->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{""background:#FFFFFF;""padding-top:20px;""padding-bottom:20px;""padding-left:3px;""padding-right:3px;""border-left:1px solid #d7d7d7;}""QScrollBar::handle:vertical{""background:#dbdbdb;""border-radius:6px;""min-height:80px;}");
    ui->readerInfoTable->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{""background:#FFFFFF;""padding-top:3px;""padding-bottom:3px;""padding-left:20px;""padding-right:20px;}""QScrollBar::handle:horizontal{""background:#dbdbdb;""border-radius:6px;""min-width:80px;}");
    //首先隐藏部分按钮，等待用户操作来激活
    ui->searchButton->hide();
    ui->giveUpChange->hide();
    ui->submitChange->hide();
    ui->batchImportButton->hide();
    //设置初始页面
    ui->stackedWidget->setCurrentWidget(ui->inputReaderIDpage);
    //设置一些输入提示
    ui->bookAuthorInput->setLabelText("请输入作者");
    ui->bookClassInput->setLabelText("请输入分类号");
    ui->bookISBNInput->setLabelText("请输入ISBN");
    ui->bookKeywordInput->setLabelText("请输入关键词");
    ui->bookKindInput->setLabelText("请输入图书类型");
    ui->bookNameInput->setLabelText("请输入书名");
    ui->bookPublishingInput->setLabelText("请输入出版社");
    ui->readerEmailInput->setLabelText("请输入读者电子邮件");
    ui->readerIdInput->setLabelText("请输入读者ID");
    ui->readerNameInput->setLabelText("请输入读者姓名");
    ui->readerPhoneInput->setLabelText("请输入读者电话");
    ui->ridInput->setLabelText("请输入读者账号");
}

AdminUI::~AdminUI()
{
    delete ui;
}

void AdminUI::showAllReader()
{
    model.setTable("reader");
    //设置查询条件
    model.setFilter("reader_id like '%" + ui->readerIdInput->text().trimmed()
                    + "%' and name like '%" + ui->readerNameInput->text().trimmed()
                    + "%' and email like '%" + ui->readerEmailInput->text().trimmed()
                    + "%' and phone like '%" + ui->readerPhoneInput->text().trimmed() + "%'");
    model.setHeaderData(0, Qt::Horizontal, tr("读者ID"));
    model.setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model.setHeaderData(2, Qt::Horizontal, tr("读者类型"));
    model.setHeaderData(3, Qt::Horizontal, tr("性别"));
    model.setHeaderData(4, Qt::Horizontal, tr("电话"));
    model.setHeaderData(5, Qt::Horizontal, tr("电子邮件"));
    model.setHeaderData(6, Qt::Horizontal, tr("借阅数目上限/本"));
    model.setHeaderData(7, Qt::Horizontal, tr("借阅期限/天"));
    model.setHeaderData(8, Qt::Horizontal, tr("续借上限/次"));
    model.setHeaderData(9, Qt::Horizontal, tr("注册日期"));
    model.setHeaderData(10, Qt::Horizontal, tr("备注"));
    model.setHeaderData(11, Qt::Horizontal, tr("密码"));
    model.setEditStrategy(QSqlTableModel::OnManualSubmit); //手动提交事务
    model.select();
    ui->readerInfoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置要根据内容使用宽度的列
    ui->readerInfoTable->setModel(&model);
    ui->readerInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
}

void AdminUI::showAllBook()
{
    model.setTable("book");
    //设置查询条件
    model.setFilter("book_name like '%" + ui->bookNameInput->text().trimmed() + "%' and author like '%" + ui->bookAuthorInput->text().trimmed() + "%' and publishing_house like '%" + ui->bookPublishingInput->text().trimmed() + "%' and isbn like '%" + ui->bookISBNInput->text().trimmed() + "%' and book_kind like '%" + ui->bookKindInput->text().trimmed() + "%' and keyword like '%" + ui->bookKeywordInput->text().trimmed() + "%' and classification_number like '%" + ui->bookClassInput->text().trimmed() + "%'");
    model.setHeaderData(0, Qt::Horizontal, tr("图书ISBN"));
    model.setHeaderData(1, Qt::Horizontal, tr("书名"));
    model.setHeaderData(2, Qt::Horizontal, tr("图书类型"));
    model.setHeaderData(3, Qt::Horizontal, tr("分类号"));
    model.setHeaderData(4, Qt::Horizontal, tr("关键词"));
    model.setHeaderData(5, Qt::Horizontal, tr("出版时间"));
    model.setHeaderData(6, Qt::Horizontal, tr("出版社"));
    model.setHeaderData(7, Qt::Horizontal, tr("作者"));
    model.setHeaderData(8, Qt::Horizontal, tr("价格"));
    model.setHeaderData(9, Qt::Horizontal, tr("馆藏"));
    model.setHeaderData(10, Qt::Horizontal, tr("在借"));
    model.setHeaderData(11, Qt::Horizontal, tr("备注"));
    model.setEditStrategy(QSqlTableModel::OnManualSubmit); //手动提交事务
    model.select();
    ui->bookInfoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置要根据内容使用宽度的列
    ui->bookInfoTable->setModel(&model);
    ui->bookInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
}

void AdminUI::on_adminLogout_clicked()
{
    this->close();
}


void AdminUI::on_readerInfo_clicked()
{
    QFuture<void> future = QtConcurrent::run([=]() {
            showAllReader();
        });
    ui->stackedWidget->setCurrentWidget(ui->ripage);
    ui->searchButton->show();
    ui->giveUpChange->show();
    ui->submitChange->show();
    ui->batchImportButton->show();
}


void AdminUI::on_bookInfo_clicked()
{
    QFuture<void> future = QtConcurrent::run([=]() {
            showAllBook();
        });
    ui->stackedWidget->setCurrentWidget(ui->bipage);
    ui->searchButton->show();
    ui->giveUpChange->show();
    ui->submitChange->show();
    ui->batchImportButton->show();
}


void AdminUI::on_readerService_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->inputReaderIDpage);

    ui->searchButton->hide();
    ui->giveUpChange->hide();
    ui->submitChange->hide();
    ui->batchImportButton->hide();
}


void AdminUI::on_addBook_clicked()//插入图书
{
    insertInfo* info=new insertInfo(true,this);
    info->exec();
}


void AdminUI::on_editBook_clicked()//修改图书
{
    showAllBook();
    ui->bookInfoTable->setEditTriggers(QAbstractItemView::AllEditTriggers);//设置可编辑
}

void AdminUI::on_deleteBook_clicked()
{
    deleteInfo* d=new deleteInfo(true,this);
    d->exec();
    showAllBook();
}

void AdminUI::on_searchButton_clicked()
{
    if(ui->stackedWidget->currentWidget()==ui->bipage)
        QFuture<void> future = QtConcurrent::run([=]() {
                    showAllBook();
                });
    else
        QFuture<void> future = QtConcurrent::run([=]() {
                    showAllReader();
                });
}


void AdminUI::on_submitChange_clicked()//提交事务
{
    if(model.submitAll())
    {
        Toast::showMsg("修改成功",ToastTime::ToastTime_short);
        ui->readerInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
        ui->bookInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    }
    else
    {
        Toast::showMsg("修改失败，请检查网络连接");
    }
}


void AdminUI::on_giveUpChange_clicked()
{
    //撤销事务
    model.revertAll();
    //撤销事务需要提交
    if(model.submitAll())
    {
        Toast::showMsg("撤销成功",ToastTime::ToastTime_short);
    }
    else
    {
        Toast::showMsg("网络连接中断，请重启本程序");
    }
}


void AdminUI::on_editReader_clicked()//修改读者
{
    showAllReader();
    ui->readerInfoTable->setEditTriggers(QAbstractItemView::AllEditTriggers);//设置可编辑
    //设置11列(读者密码)只读
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
    ui->readerInfoTable->setItemDelegateForColumn(11, readOnlyDelegate);
    Toast::showMsg("读者密码请到读者服务模块修改",ToastTime::ToastTime_short);
}


void AdminUI::on_deleteReader_clicked()
{
    deleteInfo* d=new deleteInfo(false,this);
    d->exec();
    showAllReader();
}


void AdminUI::on_readerBorrow_clicked()
{
    br_Re_Cp* br=new br_Re_Cp(reader,borrowBook,this);
    br->exec();
}


void AdminUI::on_readerReturn_clicked()
{
    br_Re_Cp* br=new br_Re_Cp(reader,returnBook,this);
    br->exec();
}


void AdminUI::on_changePass_clicked()
{
    br_Re_Cp* br=new br_Re_Cp(reader,changePassWord,this);
    br->exec();
}


void AdminUI::on_lossOrbroke_clicked()
{
    compensateDialog* co=new compensateDialog(reader.getReaderID(),this);
    co->exec();
}


void AdminUI::on_readerIdConfirmButton_clicked()
{
    if(!ui->ridInput->editor()->text().trimmed().isEmpty()){
        if(reader.setReaderID(ui->ridInput->editor()->text().trimmed()))
        {
            ui->stackedWidget->setCurrentWidget(ui->rspage);
            ui->ridInput->setText("");//清空输入框
        }
        else
        {
            Toast::showMsg("未找到此读者",ToastTime::ToastTime_long);
            ui->ridInput->showWrong("请检查输入读者ID",true);
        }

    }
    else
    {
        Toast::showMsg("请输入读者ID",ToastTime::ToastTime_long);
        ui->ridInput->showWrong("请输入读者ID",true);
    }
}


void AdminUI::on_addReader_clicked()
{
    insertInfo* reg=new insertInfo(false,this);
    reg->exec();
    showAllReader();
}


void AdminUI::on_batchImportButton_clicked()
{
    try
    {
        if(ui->stackedWidget->currentIndex()==0)
        {
            batchImport(true,this);
        }
        else if(ui->stackedWidget->currentIndex()==1)
        {
            batchImport(false,this);
        }
    }
    catch (...)
    {
        QMessageBox::warning(this,QObject::tr("读取文件出错"),QObject::tr("无法打开文件，请检查文件内容是否正确"));
    }
}
