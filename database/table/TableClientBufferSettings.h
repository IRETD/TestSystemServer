#ifndef TABLECLIENTBUFFERSETTINGS_H
#define TABLECLIENTBUFFERSETTINGS_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>

class TableClientBufferSettings {

    OurDataBase m_Db;

public:
    TableClientBufferSettings( const OurDataBase &db );

    int getClientBufferMaxSize( const int &idClientBufferSetting , OurQueryInfo &queryInfo );
};

#endif // TABLECLIENTBUFFERSETTINGS_H
