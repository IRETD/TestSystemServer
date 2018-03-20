#ifndef TABLERESULT_H
#define TABLERESULT_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
#include <MacroDefinitions/Data/Test/TestResult.h>

class TableResult {

    OurDataBase m_Db;

public:
    TableResult( const OurDataBase & db );

    QString getResult( const TestResult &idResult, OurQueryInfo &queryInfo );
};

#endif
