#include "TableRequestSettings.h"


TableRequestSettings::TableRequestSettings( const OurDataBase &db ) {

    m_Db = db;
}


int TableRequestSettings::getRequestCountLimit( const int &idRequestSetting , OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT request_count_limit FROM request_settings WHERE id_request_setting = :idRequestSetting" );
    query.bindValue( ":idRequestSetting", idRequestSetting );
    query.exec();

    int requestCountLimit = QUERY_NO_DATA;

    if ( query.size() > 0 ) {
        QSqlRecord record = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            requestCountLimit = query.value( record.indexOf( "request_count_limit" ) ).toInt();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return requestCountLimit;
}


int TableRequestSettings::getRequestTimeLimit( const int &idRequestSetting, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT request_time_limit FROM request_settings WHERE id_request_setting = :idRequestSetting" );
    query.bindValue( ":idRequestSetting", idRequestSetting );
    query.exec();

    int requestTimeLimit = QUERY_NO_DATA;

    if ( query.size() > 0 ) {
        QSqlRecord record = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            requestTimeLimit = query.value( record.indexOf( "request_time_limit" ) ).toInt();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return requestTimeLimit;
}
