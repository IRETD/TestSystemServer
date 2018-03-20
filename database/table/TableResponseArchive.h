#ifndef TABLERESPONSEARCHIVE_H
#define TABLERESPONSEARCHIVE_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>

class TableResponseArchive {

    OurDataBase m_Db;

public:
    TableResponseArchive( const OurDataBase & db );

    void insert( const int &idUser, const QString &valueResponse, OurQueryInfo &queryInfo );
    void deleteValues( const int &idUser, OurQueryInfo &queryInfo );

    QList < QString > getValue( const int &idUser, OurQueryInfo &queryInfo );
};

#endif
