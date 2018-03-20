#ifndef TABLETESTOUTPUT_H
#define TABLETESTOUTPUT_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>

class TableTestOutput {

    OurDataBase m_Db;

public:
    TableTestOutput( const OurDataBase &db );

    QStringList getOutputDataList( const int &idTest, OurQueryInfo &queryInfo );
};

#endif
