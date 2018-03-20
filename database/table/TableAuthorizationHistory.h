#ifndef TABLEAUTHORIZATIONHISTORY_H
#define TABLEAUTHORIZATIONHISTORY_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>

class TableAuthorizationHistory {

    OurDataBase m_Db;

public:
    TableAuthorizationHistory( const OurDataBase &db );

    void insert( const int &idClient, const QDateTime &dateAuthorization, const bool &result,
                 const QString &login, const QString &password, OurQueryInfo &queryInfo );
};

#endif
