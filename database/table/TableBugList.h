#ifndef TABLEBUGLIST_H
#define TABLEBUGLIST_H

#include <database/OurDataBase.h>
#include <QDateTime>
#include <database/OurQueryInfo.h>

class TableBugList {

    OurDataBase m_Db;

public:
    TableBugList( const OurDataBase &db );

    void insert( const QString &description, const QDateTime &bugDateTime, const QString &className,
                 const QString &functionName, const QString &functionInputData, const int &bugLineNumber,
                 const QString &bugLineDescritpion, OurQueryInfo &queryInfo );
};

#endif
