#include "TableClientBufferSettings.h"


TableClientBufferSettings::TableClientBufferSettings( const OurDataBase &db ) {

    m_Db = db;
}


int TableClientBufferSettings::getClientBufferMaxSize( const int &idClientBufferSetting, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT client_buffer_max_size_kilobyte FROM client_buffer_settings WHERE id_client_buffer_setting = :id_client_buffer_setting" );
    query.bindValue( ":id_client_buffer_setting", idClientBufferSetting );

    query.exec();

    int clientBufferSize = QUERY_NO_DATA;

    if ( query.size() > 0 ) {
        QSqlRecord record = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            clientBufferSize = query.value( record.indexOf( "client_buffer_max_size_kilobyte" ) ).toInt();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return clientBufferSize;
}



