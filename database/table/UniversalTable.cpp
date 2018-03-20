#include "UniversalTable.h"

//НАЧАЛО КАЖДОЙ ФУНКЦИИ С ЗАПРОСОМ К БАЗЕ
//-----------------------------------
#define PROLOG_OF_QUERY_FUNCTION(str) \
    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );\
    query.prepare( str );
//-----------------------------------


//КОНЦОВКА КАЖДОЙ ФУНКЦИИ С ЗАПРОСОМ К БАЗЕ
//-----------------------------------
#define EPILOG_OF_QUERY_FUNCTION \
queryInfo.setTypeError( query.lastError().type() );\
queryInfo.setNumberError( query.lastError().number() );\
queryInfo.setDescription( query.lastError().text() );
//-----------------------------------

UniversalTable::UniversalTable( OurDataBase db ) {

    m_Db = db;
}


QString UniversalTable::getName( OurQueryInfo &queryInfo,
                                 ID_TYPE whereIdValue,
                                 QString tableName,
                                 QString whereFieldIdTitle,
                                 QString selectFieldNameTitle ) {

    PROLOG_OF_QUERY_FUNCTION( "SELECT " +
                              selectFieldNameTitle +
                              " FROM " +
                              tableName +
                              " WHERE " +
                              whereFieldIdTitle +
                              " = :id_value" )
    /*
    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT " +
                   fieldNameTitle +
                   " FROM " +
                   tableName +
                   " WHERE " +
                   fieldIdTitle +
                   " = :id_value" );
    */
    query.bindValue( ":id_value", whereIdValue );
    query.exec();

    QString name;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            name = query.value( rec.indexOf( selectFieldNameTitle ) ).toString();
        }

    }

    EPILOG_OF_QUERY_FUNCTION

    return name;
}


ID_TYPE UniversalTable::getId(OurQueryInfo &queryInfo,
                               QString tableName,
                               QString selectFieldIdTitle,
                               QString whereFieldTitle,
                               ID_TYPE whereFieldValue ) {

    PROLOG_OF_QUERY_FUNCTION( "SELECT " + selectFieldIdTitle +
                              " FROM " +
                              tableName +
                              " WHERE " +
                              whereFieldTitle +
                              " = :firstFieldValue" );
     query.bindValue( ":firstFieldValue",
                      whereFieldValue );
     query.exec();

     ID_TYPE id = QUERY_NO_DATA;

     if ( query.size() > 0) {
         QSqlRecord rec = query.record();

         if ( query.first() && query.isValid() ) {
             queryInfo.setResult( true );
             id = query.value( rec.indexOf( selectFieldIdTitle ) ).toInt();
         }

     }

     EPILOG_OF_QUERY_FUNCTION

     return id;
}



ID_TYPE UniversalTable::getId( OurQueryInfo &queryInfo,
                           QString tableName,
                           QString selectFieldIdTitle,
                           QString whereFirstFieldTitle,
                           QString whereSecondFieldTitle,
                           QString whereFirstFieldValue,
                           QString whereSecondFieldValue ) {

   PROLOG_OF_QUERY_FUNCTION( "SELECT " + selectFieldIdTitle +
                             " FROM " +
                             tableName +
                             " WHERE " +
                             whereFirstFieldTitle +
                             " = :firstFieldValue" +
                             " and " +
                             whereSecondFieldTitle +
                             " = :secondFiledValue" );
    query.bindValue( ":firstFieldValue",
                     whereFirstFieldValue);
    query.bindValue( ":secondFiledValue",
                     whereSecondFieldValue );
    query.exec();

    ID_TYPE id = QUERY_NO_DATA;

    if ( query.size() > 0) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            id = query.value( rec.indexOf( selectFieldIdTitle ) ).toInt();
        }

    }

    EPILOG_OF_QUERY_FUNCTION

    return id;
}


QList < ID_TYPE > UniversalTable::getListId(OurQueryInfo &queryInfo,
                                         QString tableName,
                                         QString selectFieldIdTitle,
                                         QString whereFirstFieldTitle,
                                         ID_TYPE whereFirstFieldValue ) {

    PROLOG_OF_QUERY_FUNCTION( "SELECT " + selectFieldIdTitle +
                              " FROM " +
                              tableName +
                              " WHERE " +
                              whereFirstFieldTitle +
                              " = :firstFieldValue" );
    query.bindValue( ":firstFieldValue",
                     whereFirstFieldValue  );
    query.exec();

    QList < ID_TYPE > idList;
    if ( query.size() > 0 ) {
        QSqlRecord recordTestInput = query.record();

        while ( query.next() ) {

            if ( query.isValid() ) {
                queryInfo.setResult( true );
                idList.append( query.value(
                                          recordTestInput.indexOf( selectFieldIdTitle ) ).toInt() );
            }
        }

    }

    EPILOG_OF_QUERY_FUNCTION

    return idList;
}


///первоначальное назначение этого метода:
///стянуть список из 2 айдишников с базы
QList<QPair<ID_TYPE, ID_TYPE> > UniversalTable::getPairIdList(OurQueryInfo &queryInfo,
                                                            QString tableName,
                                                            QString selectFieldFirstIdTitle,
                                                            QString selectFieldSecondIdTitle,
                                                            QString whereFirstFieldTitle,
                                                            ID_TYPE whereFirstFieldValue ) {
    PROLOG_OF_QUERY_FUNCTION( "SELECT " + selectFieldFirstIdTitle +
                              ", " +
                              selectFieldSecondIdTitle +
                              " FROM " +
                              tableName +
                              " WHERE " +
                              whereFirstFieldTitle +
                              " = :firstFieldValue" );
    query.bindValue( ":firstFieldValue",
                     whereFirstFieldValue  );
    query.exec();

    QList < QPair < ID_TYPE, ID_TYPE > > pairIdList;
    if ( query.size() > 0 ) {
        QSqlRecord recordTestInput = query.record();

        while ( query.next() ) {

            if ( query.isValid() ) {
                queryInfo.setResult( true );
                QPair < int, int > pair;
                pair.first = query.value( recordTestInput.indexOf( selectFieldFirstIdTitle ) ).toInt();
                pair.second = query.value( recordTestInput.indexOf( selectFieldSecondIdTitle ) ).toInt();

                pairIdList.append( pair );
            }
        }

    }

    EPILOG_OF_QUERY_FUNCTION

    return pairIdList;
}

QList<QPair<ID_TYPE, QPair<ID_TYPE, ID_TYPE> > > UniversalTable::getPairIdList(OurQueryInfo &queryInfo,
                                                                               QString tableName,
                                                                               QString selectFieldFirstIdTitle,
                                                                               QString selectFieldSecondIdTitle,
                                                                               QString selectFieldThirdIdTitle,
                                                                               QString whereFirstFieldTitle,
                                                                               ID_TYPE whereFirstFieldValue ) {

    PROLOG_OF_QUERY_FUNCTION( "SELECT " + selectFieldFirstIdTitle +
                              ", " +
                              selectFieldSecondIdTitle +
                              ", " +
                              selectFieldThirdIdTitle +
                              " FROM " +
                              tableName +
                              " WHERE " +
                              whereFirstFieldTitle +
                              " = :firstFieldValue" );
    query.bindValue( ":firstFieldValue",
                     whereFirstFieldValue  );
    query.exec();

    QList < QPair < ID_TYPE,
                    QPair < ID_TYPE,
                            ID_TYPE >
                  >
          > pairIdList;
    if ( query.size() > 0 ) {
        QSqlRecord recordTestInput = query.record();

        while ( query.next() ) {

            if ( query.isValid() ) {
                queryInfo.setResult( true );
                QPair < ID_TYPE,
                        QPair < ID_TYPE,
                                ID_TYPE >
                      > pair;
                pair.first = query.value( recordTestInput.indexOf( selectFieldFirstIdTitle ) ).toInt();
                pair.second.first = query.value( recordTestInput.indexOf( selectFieldSecondIdTitle ) ).toInt();
                pair.second.second = query.value( recordTestInput.indexOf( selectFieldThirdIdTitle ) ).toInt();

                pairIdList.append( pair );
            }
        }

    }

    EPILOG_OF_QUERY_FUNCTION

    return pairIdList;

}

QPair<QList<ID_TYPE>, QList<ID_TYPE> > UniversalTable::getPairOfList(OurQueryInfo &queryInfo,
                                       QString tableName,
                                       QString selectFieldFirstIdTitle,
                                       QString selectFieldSecondIdTitle,
                                       QString whereFieldTitle,
                                       ID_TYPE whereFieldValue) {


    PROLOG_OF_QUERY_FUNCTION( "SELECT " + selectFieldFirstIdTitle +
                              ", " +
                              selectFieldSecondIdTitle +
                              " FROM " +
                              tableName +
                              " WHERE " +
                              whereFieldTitle +
                              " = :firstFieldValue" );
    query.bindValue( ":firstFieldValue",
                     whereFieldValue  );
    query.exec();

    QPair < QList < ID_TYPE >,
            QList < ID_TYPE >
          > pairOfList;

    if ( query.size() > 0 ) {
        QSqlRecord recordTestInput = query.record();

        QList < ID_TYPE > firstList;
        QList < ID_TYPE > secondList;
        while ( query.next() ) {

            if ( query.isValid() ) {
                queryInfo.setResult( true );
                firstList.push_back( query.value( recordTestInput.indexOf( selectFieldFirstIdTitle ) ).toInt() );
                secondList.push_back( query.value( recordTestInput.indexOf( selectFieldSecondIdTitle ) ).toInt() );
            }
        }

        pairOfList.first = firstList;
        pairOfList.second = secondList;

    }

    EPILOG_OF_QUERY_FUNCTION

    return pairOfList;
}
