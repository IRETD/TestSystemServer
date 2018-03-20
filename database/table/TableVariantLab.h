#ifndef TABLEVARIANTLAB_H
#define TABLEVARIANTLAB_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>

class TableVariantLab {

     OurDataBase m_Db;

public:
    TableVariantLab( const OurDataBase &db );

    int getIdLab( const int &idVariant , OurQueryInfo &queryInfo);
    int getTimeLimit( const int &idVariant, OurQueryInfo &queryInfo );
};

#endif
