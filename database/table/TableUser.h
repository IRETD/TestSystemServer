#ifndef TABLEUSER_H
#define TABLEUSER_H

#include <database/OurDataBase.h>
#include <QString>
#include <database/OurQueryInfo.h>

class TableUser {

    OurDataBase m_Db;

public:
    TableUser( const OurDataBase &db );

    int getId( const QString &login, const QString &password, OurQueryInfo &queryInfo );
};

#endif
