#ifndef TABLEIDLESETTINGS_H
#define TABLEIDLESETTINGS_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>

class TableIdleSettings {

    OurDataBase m_Db;

public:
    TableIdleSettings( const OurDataBase &db );

    int getTimeSecond( const int &idIdleSetting , OurQueryInfo &queryInfo );
};

#endif // TABLEIDLESETTINGS_H
