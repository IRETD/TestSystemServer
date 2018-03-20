#ifndef TABLEMESSAGECATALOGFORCLIENT_H
#define TABLEMESSAGECATALOGFORCLIENT_H

#include <database/OurDataBase.h>
#include <QString>
#include <bug/BugReport.h>
#include <database/OurQueryInfo.h>

class TableMessageCatalogForClient {

    OurDataBase m_Db;

public:
    TableMessageCatalogForClient( const OurDataBase & db );

    QString getMessage( const MessageType &idMessage , OurQueryInfo &queryInfo );
};

#endif // TABLEMESSAGECATALOGFORCLIENT_H
