#include "readerui.h"
#include "ui_readerui.h"

ReaderUI::ReaderUI(Reader reader,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReaderUI)
{
    ui->setupUi(this);
    this->reader=reader;
    ui->bookInfoTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);//垂直滚动条
    ui->bookInfoTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);//水平滚动条
    ui->bookInfoTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//垂直平滑滚动
    ui->bookInfoTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);//水平平滑滚动
    ui->unreturnTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);//垂直滚动条
    ui->unreturnTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);//水平滚动条
    ui->unreturnTableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//垂直平滑滚动
    ui->unreturnTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);//水平平滑滚动
    ui->returnedTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);//垂直滚动条
    ui->returnedTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);//水平滚动条
    ui->returnedTableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//垂直平滑滚动
    ui->returnedTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);//水平平滑滚动。
    ui->bookInfoTable->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{"        //垂直滑块整体
                                                                 "background:#FFFFFF;"  //背景色
                                                                 "padding-top:20px;"    //上预留位置（放置向上箭头）
                                                                 "padding-bottom:20px;" //下预留位置（放置向下箭头）
                                                                 "padding-left:3px;"    //左预留位置（美观）
                                                                 "padding-right:3px;"   //右预留位置（美观）
                                                                 "border-left:1px solid #d7d7d7;}"//左分割线
                                                                 "QScrollBar::handle:vertical{"//滑块样式
                                                                 "background:#dbdbdb;"  //滑块颜色
                                                                 "border-radius:6px;"   //边角圆润
                                                                 "min-height:80px;}"    //滑块最小高度
                                                                 "QScrollBar::handle:vertical:hover{"//鼠标触及滑块样式
                                                                 "background:#d0d0d0;}");//滑块颜色
    ui->bookInfoTable->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{""background:#FFFFFF;""padding-top:3px;""padding-bottom:3px;""padding-left:20px;""padding-right:20px;}""QScrollBar::handle:horizontal{""background:#dbdbdb;""border-radius:6px;""min-width:80px;}""QScrollBar::handle:horizontal:hover{""background:#d0d0d0;}");
    ui->unreturnTableView->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{""background:#FFFFFF;""padding-top:20px;""padding-bottom:20px;""padding-left:3px;""padding-right:3px;""border-left:1px solid #d7d7d7;}""QScrollBar::handle:vertical{""background:#dbdbdb;""border-radius:6px;""min-height:80px;}");
    ui->unreturnTableView->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{""background:#FFFFFF;""padding-top:3px;""padding-bottom:3px;""padding-left:20px;""padding-right:20px;}""QScrollBar::handle:horizontal{""background:#dbdbdb;""border-radius:6px;""min-width:80px;}");
    ui->returnedTableView->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{""background:#FFFFFF;""padding-top:20px;""padding-bottom:20px;""padding-left:3px;""padding-right:3px;""border-left:1px solid #d7d7d7;}""QScrollBar::handle:vertical{""background:#dbdbdb;""border-radius:6px;""min-height:80px;}");
    ui->returnedTableView->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{""background:#FFFFFF;""padding-top:3px;""padding-bottom:3px;""padding-left:20px;""padding-right:20px;}""QScrollBar::handle:horizontal{""background:#dbdbdb;""border-radius:6px;""min-width:80px;}");
    //设置一些输入提示
    ui->bookAuthorInput->setLabelText("请输入作者");
    ui->bookClassInput->setLabelText("请输入分类号");
    ui->bookISBNInput->setLabelText("请输入ISBN");
    ui->bookKeywordInput->setLabelText("请输入关键词");
    ui->bookKindInput->setLabelText("请输入图书类型");
    ui->bookNameInput->setLabelText("请输入书名");
    ui->bookPublishingInput->setLabelText("请输入出版社");
    ui->isbnInput_renewBorrow->setLabelText("请输入要续借的图书的ISBN");
    //设置初始页面
    ui->stackedWidget->setCurrentWidget(ui->searchpage);
}

ReaderUI::~ReaderUI()
{
    delete ui;
}

void ReaderUI::showAllBook()
{
    model.setTable("book");
    //设置查询条件
    model.setFilter("book_name like '%" + ui->bookNameInput->text().trimmed()
                    + "%' and author like '%" + ui->bookAuthorInput->text().trimmed()
                    + "%' and publishing_house like '%" + ui->bookPublishingInput->text().trimmed()
                    + "%' and isbn like '%" + ui->bookISBNInput->text().trimmed()
                    + "%' and book_kind like '%" + ui->bookKindInput->text().trimmed()
                    + "%' and keyword like '%" + ui->bookKeywordInput->text().trimmed()
                    + "%' and classification_number like '%" + ui->bookClassInput->text().trimmed() + "%'");
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
    model.select();
    ui->bookInfoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置要根据内容使用宽度的列
    ui->bookInfoTable->setModel(&model);
    ui->bookInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
}

void ReaderUI::showBookRorUr(bool isRetuned)
{
    QSqlQueryModel* model = new QSqlQueryModel(this);
    if(isRetuned)
    {
        model->setQuery("select book.isbn,book_name,author,"
                        "publishing_house,borrow_date,renew_times,"
                        "return_date from book,borrow_return where book.isbn"
                        "=borrow_return.isbn and reader_id="
                        +reader.getReaderID()+" and return_date is not null");
    }
    else
    {
        model->setQuery("select book.isbn,book_name,author,"
                        "publishing_house,borrow_date,renew_times from book"
                        ",borrow_return where book.isbn=borrow_return.isbn"
                        " and reader_id="+reader.getReaderID()+" and return_date is null");
    }
    model->setHeaderData(0, Qt::Horizontal, tr("图书ISBN"));
    model->setHeaderData(1, Qt::Horizontal, tr("书名"));
    model->setHeaderData(2, Qt::Horizontal, tr("作者"));
    model->setHeaderData(3, Qt::Horizontal, tr("出版社"));
    model->setHeaderData(4, Qt::Horizontal, tr("借书日期"));
    model->setHeaderData(5, Qt::Horizontal, tr("续借次数"));
    if(isRetuned)
    {
        model->setHeaderData(6, Qt::Horizontal, tr("归还日期"));
        ui->returnedTableView->setModel(model);//数据放置进去
        ui->returnedTableView->verticalHeader()->hide();//不显示序号
        ui->returnedTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置要根据内容使用宽度的列
    }
    else
    {
        ui->unreturnTableView->setModel(model);//数据放置进去
        ui->unreturnTableView->verticalHeader()->hide();//不显示序号
        ui->unreturnTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置要根据内容使用宽度的列
    }
}

void ReaderUI::on_searchAndBorrow_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->searchpage);
    ui->searchButton->show();
    ui->borrowButton->show();
}


void ReaderUI::on_myBorrow_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mbpage);
    ui->tabWidget->setCurrentWidget(ui->unreturn);
    showBookRorUr(false);
    //隐藏部分按钮，等待用户操作来激活
    ui->searchButton->hide();
    ui->borrowButton->hide();
}


void ReaderUI::on_readerLogout_clicked()
{
    //清空账号的变量
    reader.clear();
    Toast::showMsg("成功退出登录",ToastTime::ToastTime_short);
    this->close();
}


void ReaderUI::on_searchButton_clicked()
{
    QFuture<void> future = QtConcurrent::run([=]() {
            showAllBook();
        });
}


void ReaderUI::on_borrowButton_clicked()//打开借书界面
{
    br_Re_Cp* br=new br_Re_Cp(reader,borrowBook,this);
    br->exec();
}


void ReaderUI::on_renewBorrowButton_clicked()//续借
{
    if(ui->isbnInput_renewBorrow->text().trimmed().isEmpty())
    {
        Toast::showMsg("请输入ISBN");
        ui->isbnInput_renewBorrow->showWrong("请输入要续借的图书的ISBN",true);
        return;
    }
    int type=reader.renewBook(ui->isbnInput_renewBorrow->text().trimmed());
    if(type==1)
    {
        Toast::showMsg("续借成功");
        showBookRorUr(false);
        ui->isbnInput_renewBorrow->setText("");
    }
    if(type==-1)
        Toast::showMsg("已达到最大续借次数");
    if(type==-2)
    {
        ui->isbnInput_renewBorrow->showWrong("请检查输入的ISBN是否是已归还的图书");
        Toast::showMsg("未查询到此书的借阅记录，请检查输入的ISBN");
    }
}


void ReaderUI::on_tabWidget_currentChanged(int index)
{
    if(index==0)
        showBookRorUr(false);
    else if(index==1)
        showBookRorUr(true);
}

