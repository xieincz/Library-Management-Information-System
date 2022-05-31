#include "toast.h"
Toast::Toast(QWidget *parent)
    : QWidget(parent)
{
    QScreen *scr=QApplication::primaryScreen();
    this->screen_info=new Screen(scr->name(),scr->availableSize().width(),scr->availableSize().height());
    this->toast_info=new QPushButton(this);
    this->toast_info->setFont(QFont("Microsoft YaHei",12,QFont::Bold));
    adaptPage(0,0);
    this->toast_info->setStyleSheet("border-radius:20px;background-color: #24936E;color: rgb(255,255,255)");//toast外观
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->master_timer_id=startTimer(200);
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
}

void Toast::makeText(QString text, ToastTime::Time time)
{
    this->toast_msg_list.append(ToastMsg(text,time));
}

void Toast::showMsg(QString text, ToastTime::Time time)
{
    instance().makeText(text,time);
}

Toast &Toast::instance()
{
    static Toast instance;
    instance.show();
    return instance;
}

void Toast::exit()
{
    this->close();
}

Toast::~Toast()
{
    delete toast_info;
    delete screen_info;
    toast_msg_list.clear();
}

void Toast::fadeToastAnimation(int time)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(time);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
}

void Toast::raiseToastAnimation(int time)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(time);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

void Toast::adaptPage(int width, int height)
{
    if(width<50){
        this->toast_info->setGeometry(0,0,50,height);
    }else {
        this->toast_info->setGeometry(0,0,width,height);
    }
    this->toast_info->setStyleSheet("border-radius:"+QString::number(height/2)+"px;background-color: #24936E;color: rgb(255,255,255)");
    this->setGeometry((screen_info->width()-toast_info->width())*0.5,screen_info->height()*0.85,toast_info->width(),toast_info->height());
}

void Toast::addMsg(QString msg)
{
    Toast::showMsg(msg);
}

void Toast::removeMsg(QString msg)
{
    this->toast_msg_list.removeOne(ToastMsg(msg,ToastTime::ToastTime_short));
}

void Toast::appExit()
{
    this->exit();
}

void Toast::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==this->master_timer_id){
        if(this->toast_msg_list.length()>0){
            this->msg_timer_id=startTimer(this->toast_msg_list.first().time_toInt());
            killTimer(this->master_timer_id);//暂停监控
            adaptPage(this->toast_msg_list.first().text().toLocal8Bit().length()*7.5+30);
            this->toast_info->setText(this->toast_msg_list.first().text());
            raiseToastAnimation(100);
            this->setVisible(true);
        }else {
            this->setVisible(false);
        }
    }else if (event->timerId()==msg_timer_id) {
        this->toast_msg_list.removeFirst();
        killTimer(this->msg_timer_id);
        this->master_timer_id=startTimer(200);//开启监控
        fadeToastAnimation(100);
    }else {
        makeText("i don't know the toast timer id:"+QString::number(event->timerId()));
    }
}
Screen::Screen(QString name, int width, int height):m_name(name),m_width(width),m_height(height)
{

}

bool ToastMsg::operator ==(const ToastMsg &msg) const
{
    if(this->m_text==msg.m_text){
        return true;
    }else {
        return false;
    }
}
