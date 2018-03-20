#ifndef TABLELABGROOP_H
#define TABLELABGROOP_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
class TableLabGroop {

    OurDataBase m_Db;

public:
    TableLabGroop( const OurDataBase &db );

   // QList < IdLabGroopIdGroop > getIdLabGroopIdGroopList( quint32 idLab,
     //                                                     OurQueryInfo &queryInfo );
};

#endif // TABLELABGROOP_H
