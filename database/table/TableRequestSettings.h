#ifndef TABLEREQUESTSETTINGS_H
#define TABLEREQUESTSETTINGS_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>

class TableRequestSettings {

    OurDataBase m_Db;

public:
    TableRequestSettings( const OurDataBase & db );

    int getRequestCountLimit( const int &idRequestSetting, OurQueryInfo &queryInfo );
    int getRequestTimeLimit( const int &idRequestSetting , OurQueryInfo &queryInfo );
};

#endif // TABLEREQUESTSETTINGS_H
