#ifndef TABLEUSERLAB_H
#define TABLEUSERLAB_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
#include <TypeDefinitions/BaseTypeDefinitions.h>

class TableUserLab {

     OurDataBase m_Db;

public:
    TableUserLab( const OurDataBase &db );

    int getIdVariant( const int &idUserLab, OurQueryInfo &queryInfo );
    bool idUserLabExist( const int &idUserLab, const int &idUser, OurQueryInfo &queryInfo );
    QList < ID_USER_LAB > getIdUserLab( const ID_USER &idUser, OurQueryInfo &queryInfo );
};

#endif
