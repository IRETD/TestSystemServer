/****************************************************************************
**
** Стадии проверки лабораторной работы.
**
****************************************************************************/

#ifndef ABOUTHISTORY_H
#define ABOUTHISTORY_H

#include <QString>

class Stage {

    QString m_Name; //стадия проверки
    QString m_Result; // результат

public:
    Stage();

    void setName(QString name);
    void setResult(QString result);
    QString getName();
    QString getResult();
};

#endif
