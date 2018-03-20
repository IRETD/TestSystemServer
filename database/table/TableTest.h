#ifndef TABLETEST_H
#define TABLETEST_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>

class TableTest {

    OurDataBase m_Db;

public:
    TableTest( const OurDataBase &db );

    QList < quint32 > getIdTestList( const int &idVariant, OurQueryInfo &queryInfo );
};

#endif
