#ifndef TABLETESTINPUT_H
#define TABLETESTINPUT_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>

class TableTestInput {

    OurDataBase m_Db;

public:
    TableTestInput( const OurDataBase &db );

    QStringList getInputDataList( const int &idTest, OurQueryInfo &queryInfo );
};

#endif
