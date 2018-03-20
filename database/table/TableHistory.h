#ifndef TABLEHISTORY_H
#define TABLEHISTORY_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
#include <data/history/History.h>

class TableHistory {

    OurDataBase m_Db;

public:
    TableHistory( const OurDataBase &db );

    int insert( const int &idUserLab, const TestResult &idResult, const QDateTime &date,
                    const QString &pathCodeFolder, OurQueryInfo &queryInfo );
    void updateResult( const int &idHistory, const TestResult &idResult, OurQueryInfo &queryInfo );
    QList < History > getHistoryList( const int &idUserLab, OurQueryInfo &queryInfo );

};

#endif
