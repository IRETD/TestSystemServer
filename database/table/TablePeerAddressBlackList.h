#ifndef TABLEPEERADDRESSBLACKLIST_H
#define TABLEPEERADDRESSBLACKLIST_H

#include <database/OurDataBase.h>
#include <server/service/BlackList.h>
#include <database/OurQueryInfo.h>

class TablePeerAddressBlackList {

    OurDataBase m_Db;

public:
    TablePeerAddressBlackList( const OurDataBase &db );

    void getBlackList( BlackList &blackList, OurQueryInfo &queryInfo );
    void insert( const QString &peerAddress, const QDateTime &beginTime, const QDateTime &endTime,
                 OurQueryInfo &queryInfo );
    void remove( const QString &peerAddress, OurQueryInfo &queryInfo );
};

#endif // TABLECLIENTBLACKLIST_H
