#ifndef TABLEADDITIONALCOLUMNABOUTHISTORY_H
#define TABLEADDITIONALCOLUMNABOUTHISTORY_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
#include <MacroDefinitions/database/table/TableAboutHistory/AdditionalColumnType.h>

class TableAdditionalColumnAboutHistory {

    OurDataBase m_Db;

public:
    TableAdditionalColumnAboutHistory( const OurDataBase &db );

    QString getName( const AdditionalColumnType &idAdditionalColumn,
                     OurQueryInfo &queryInfo );
};

#endif // TABLEADDITIONALCOLUMNABOUTHISTORY_H
