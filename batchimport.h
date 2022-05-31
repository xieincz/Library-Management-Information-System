#ifndef BATCHIMPORT_H
#define BATCHIMPORT_H
#include <QMessageBox>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QObject>
#include"encryptpass.h"
#include"toast/toast.h"
bool batchImport(bool isForReader,QWidget *parent);

#endif // BATCHIMPORT_H
