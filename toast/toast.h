#ifndef TOAST_H
#define TOAST_H

#include <QWidget>
#include <QPushButton>
#include <QApplication>
#include <QScreen>
#include <QVector>
#include <QPropertyAnimation>

namespace ToastTime {
enum Time{
    ToastTime_short=1,
    ToastTime_long=3,
};
}
class Screen{
private:
    QString m_name;
    int m_width;
    int m_height;
public:
    Screen(QString name="main_screen",int width=1920,int height=1080);
    inline int width(){return m_width;}
    inline int height(){return m_height;}
};
class ToastMsg{
private:
    QString m_text;
    ToastTime::Time m_time;
public:
    inline ToastMsg(QString text,ToastTime::Time time):m_text(text),m_time(time){}
    inline QString text(){return m_text;}
    inline ToastTime::Time time(){return m_time;}
    inline int time_toInt(){return m_time*1000;}
    bool operator ==(const ToastMsg& msg) const;
};
class Toast : public QWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE void makeText(QString text,ToastTime::Time time=ToastTime::Time::ToastTime_long);
    static void showMsg(QString text,ToastTime::Time time=ToastTime::Time::ToastTime_long);
    static Toast& instance();
    Q_INVOKABLE void exit();
private:
    Toast(QWidget *parent = nullptr);
    ~Toast();
    QPushButton *toast_info=nullptr;
    Screen *screen_info=nullptr;
    QString m_text;
    QVector<ToastMsg> toast_msg_list;
    int master_timer_id;
    int msg_timer_id;
    void fadeToastAnimation(int time);
    void raiseToastAnimation(int time);
    void adaptPage(int width,int height=40);
public slots:
    void addMsg(QString msg);
    void removeMsg(QString msg);
    void appExit();
    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};
#endif // TOAST_H
