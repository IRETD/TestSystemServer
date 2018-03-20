#ifndef TABLELAB_H
#define TABLELAB_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
#include <data/lab/StudentTask.h>

typedef StudentTask Lab;

class TableLab {

    OurDataBase m_Db;

public:
    TableLab( const OurDataBase &db );

    Lab getLab( const int &idLab, OurQueryInfo &queryInfo );
    QList < Lab > getLabListByIdDiscipline( const int &idDiscipline,
                                            OurQueryInfo &queryInfo );
    int getIdDiscipline( const int &idLab, OurQueryInfo &queryInfo );
    QString getName( const int &idLab, OurQueryInfo &queryInfo );
    QString getPurpose( const int &idLab, OurQueryInfo &queryInfo );
    QDateTime getDesiredDate( const int &idLab, OurQueryInfo &queryInfo );
    QDateTime getCriticalDate( const int &idLab, OurQueryInfo &queryInfo );
};

#endif // TABLELAB_H
