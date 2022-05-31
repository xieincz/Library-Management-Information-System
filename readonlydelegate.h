#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H
#include<QItemDelegate>

// 设置tableview某行/列不可编辑,
class ReadOnlyDelegate: public QItemDelegate
{
public:
    ReadOnlyDelegate(QWidget *parent = NULL):QItemDelegate(parent) {}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override;
};

#endif // READONLYDELEGATE_H
