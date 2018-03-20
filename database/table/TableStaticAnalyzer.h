#ifndef TABLESTATICANALYZER_H
#define TABLESTATICANALYZER_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
#include <MacroDefinitions/Data/Test/TestResult.h>

class TableStaticAnalyzer {

    OurDataBase m_Db;

public:
    TableStaticAnalyzer( const OurDataBase &db );

    quint32 insert( quint32 idAboutHistory,
                    TestResult idResult,
                    OurQueryInfo &queryInfo );
    quint32 getIdStaticAnalyzer( quint32 idAboutHistory,
                                 OurQueryInfo &queryInfo );

};

#endif
