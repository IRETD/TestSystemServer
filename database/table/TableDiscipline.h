#ifndef TABLEDISCIPLINE_H
#define TABLEDISCIPLINE_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
#include <data/lab/Discipline.h>

class TableDiscipline {

    OurDataBase m_Db;

public:
    TableDiscipline( const OurDataBase &db );

    Discipline getDiscipline( const int &idDiscipline,
                              OurQueryInfo &queryInfo );
    QString getName( const int &idDiscipline,
                     OurQueryInfo &queryInfo );
    QString getDescription( const int &idDiscipline,
                            OurQueryInfo &queryInfo );
};

#endif // TABLEDISCIPLINE_H
