#ifndef TABLESERVERSETTINGS_H
#define TABLESERVERSETTINGS_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>

class TableServerSettings {

    OurDataBase m_Db;

public:
    TableServerSettings( const OurDataBase &db );

    int getTimePeerAddressBlackList( const int &idSetting, OurQueryInfo &queryInfo );
    // int getTimeClientBlackList( const int &idSetting, int &errorCode );
    QString getDirectoryTest( const int &idSetting, OurQueryInfo &queryInfo );
};

#endif
