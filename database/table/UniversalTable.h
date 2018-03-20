#ifndef UNIVERSALTABLE_H
#define UNIVERSALTABLE_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
#include <QPair>
#include <TypeDefinitions/BaseTypeDefinitions.h>

/*
 * Универсальная таблица отбора данных
 * Надоело реализовывать ждя каждой таблицы свой отдельный класс
 * и реализовывать одни и теже дубл методы :)
 */

class UniversalTable {

     OurDataBase m_Db;

public:
    UniversalTable( OurDataBase db );

    //id - поле, по которому будет отбираться нужная запись
    QString getName( OurQueryInfo &queryInfo,
                     ID_TYPE whereIdValue,
                     QString tableName,
                     QString whereFieldIdTitle,
                     QString selectFieldNameTitle = "name" );

    ID_TYPE getId( OurQueryInfo &queryInfo,
               QString tableName,
               QString selectFieldIdTitle,
               QString whereFieldTitle,
               ID_TYPE whereFieldValue );

    ID_TYPE getId( OurQueryInfo &queryInfo,
               QString tableName,
               QString selectFieldIdTitle,
               QString whereFirstFieldTitle,
               QString whereSecondFieldTitle,
               QString whereFirstFieldValue,
               QString whereSecondFieldValue );

    QList < ID_TYPE > getListId( OurQueryInfo &queryInfo,
                                 QString tableName,
                                 QString selectFieldIdTitle,
                                 QString whereFirstFieldTitle,
                                 ID_TYPE whereFirstFieldValue );


    QList < QPair < ID_TYPE, ID_TYPE > > getPairIdList( OurQueryInfo &queryInfo,
                                                QString tableName,
                                                QString selectFieldFirstIdTitle,
                                                QString selectFieldSecondIdTitle,
                                                QString whereFirstFieldTitle,
                                                ID_TYPE whereFirstFieldValue );
    QList < QPair < ID_TYPE, QPair < ID_TYPE, ID_TYPE > > > getPairIdList( OurQueryInfo &queryInfo,
                                                               QString tableName,
                                                               QString selectFieldFirstIdTitle,
                                                               QString selectFieldSecondIdTitle,
                                                               QString selectFieldThirdIdTitle,
                                                               QString whereFirstFieldTitle,
                                                               ID_TYPE whereFirstFieldValue );
    QPair < QList < ID_TYPE >,
            QList < ID_TYPE > > getPairOfList( OurQueryInfo &queryInfo,
                                             QString tableName,
                                             QString selectFieldFirstIdTitle,
                                             QString selectFieldSecondIdTitle,
                                             QString whereFieldTitle,
                                             ID_TYPE whereFieldValue );

};

#endif
