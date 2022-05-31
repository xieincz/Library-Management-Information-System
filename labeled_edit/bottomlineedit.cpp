#include "bottomlineedit.h"

BottomLineEdit::BottomLineEdit(QWidget *parent) : QLineEdit(parent)
{
    setObjectName("BottomLineEdit");
    setStyleSheet("#BottomLineEdit { background: transparent; border: none; margin: 0px; padding: 1px;}");
}

void BottomLineEdit::setViewShowed(bool show)
{
    //使用paintEvent
    this->show_view = show;
    update();
}

void BottomLineEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    emit signalFocusIn();
}

void BottomLineEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    emit signalFocusOut();
}

void BottomLineEdit::paintEvent(QPaintEvent *e)
{
    if (!show_view)
        return ;
    QLineEdit::paintEvent(e);
}
