/****************************************************************************
**
** Вся информация по лабораторной работе.
** Именно о самой лабораторной работе (цель, название, сроки сдачи и т.п.).
** Не путать с вариантами работ, где уже только условия :)
**
****************************************************************************/


#ifndef LABLIST_H
#define LABLIST_H

#include <QString>
#include <QDate>
#include <QVector>
#include <response/client/subclasses/restriction.h>

class LabList {

    int m_Id; //номер работы в системе
    int m_NumLab; //номер самой работы
    QString m_Name; // название работы
    QString m_Purpose; //цель работы
    int m_Attempt; //количество попыток
    QDate m_DesiredDate; //желательная дата сдачи
    QDate m_CriticalDate; //крайний срок сдачи
    QVector <Restriction> m_Restriction; //ограничения

public:
    LabList();
};

#endif
