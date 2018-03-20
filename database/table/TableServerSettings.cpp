#include "TableServerSettings.h"


TableServerSettings::TableServerSettings( const OurDataBase &db ) {

    m_Db = db;
}


int TableServerSettings::getTimePeerAddressBlackList( const int &idSetting, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT time_minute_in_peer_address_black_list FROM server_settings WHERE id_setting = :id_setting" );
    query.bindValue( ":id_setting", idSetting );
    query.exec();

    int timePeerAddressBlackList = QUERY_NO_DATA;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            timePeerAddressBlackList = query.value( rec.indexOf( "time_minute_in_peer_address_black_list" ) ).toInt();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return timePeerAddressBlackList;
}


//int TableServerSettings::getTimeClientBlackList( const int &idSetting, int &errorCode ) {

//    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
//    query.prepare( "SELECT time_minute_in_client_black_list FROM server_settings WHERE id_setting = :id_setting" );
//    query.bindValue( ":id_setting", idSetting );
//    query.exec();

//    int timeClientBlackList = QUERY_NO_DATA;

//    if ( query.size() > 0 ) {
//        QSqlRecord rec = query.record();

//        if ( query.first() && query.isValid() ) {
//            timeClientBlackList = query.value( rec.indexOf( "time_minute_in_client_black_list" ) ).toInt();
//        }

//    }

//    errorCode = query.lastError().type();

//    return timeClientBlackList;
//}


QString TableServerSettings::getDirectoryTest( const int &idSetting, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT output_directory_for_test_program FROM server_settings WHERE id_setting = :id_setting" );
    query.bindValue( ":id_setting", idSetting );
    query.exec();

    QString directoryTest;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            directoryTest = query.value( rec.indexOf( "output_directory_for_test_program" ) ).toString();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return directoryTest;
}
