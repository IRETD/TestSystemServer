#ifndef TABLEABOUTSTATICANALYZER_H
#define TABLEABOUTSTATICANALYZER_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
#include <code/Anazyler/StaticAnalyzer.h>

class TableAboutStaticAnalyzer
{

    OurDataBase m_Db;

public:
    TableAboutStaticAnalyzer( const OurDataBase &db );
    void insert( quint32 idStaticAnalyzer,
                 StaticAnalyzer staticAnalyzerData,
                 OurQueryInfo &queryInfo );
    QList < StaticAnalyzer > getStaticAnalyzerList( quint32 idStaticAnalyzer,
                                                    OurQueryInfo &queryInfo );
};

#endif // TABLEABOUTSTATICANALYZER_H
