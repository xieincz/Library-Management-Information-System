#include"encryptpass.h"

QString encryptPass(QString thePass)
{
    return QString("%1").arg(QString(QCryptographicHash::hash(QString("xie%1").arg(thePass).toUtf8(),QCryptographicHash::Sha3_512).toHex()));
}
