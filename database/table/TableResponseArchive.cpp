#include "TableResponseArchive.h"
#include <log/MyLog.h>


TableResponseArchive::TableResponseArchive( const OurDataBase &db ) {

    m_Db = db;
}


void TableResponseArchive::insert( const int &idUser, const QString &valueResponse, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "INSERT INTO response_archive( id_user, value_response ) "
            " VALUES(:id_user, :value_response)" );
    query.bindValue( ":id_user", idUser );
    query.bindValue( ":value_response", valueResponse );
    query.exec();

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );
}


void TableResponseArchive::deleteValues( const int &idUser, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "DELETE FROM response_archive WHERE id_user = :id_user" );
    query.bindValue( ":id_user", idUser );
    query.exec();

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );
}


QList < QString > TableResponseArchive::getValue( const int &idUser, OurQueryInfo &queryInfo ) {

    QList < QString > list;

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT value_response FROM response_archive WHERE id_user = :id_user" );
    query.bindValue( ":id_user", idUser );
    query.exec();

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {

            do {

                if ( query.isValid() ) {
                    queryInfo.setResult( true );
                    list.append( query.value( rec.indexOf( "value_response" ) ).toString() );
                }

            } while ( query.next() );
        }
    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return list;
}

