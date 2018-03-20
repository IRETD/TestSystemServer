#include "TableIdleSettings.h"


TableIdleSettings::TableIdleSettings( const OurDataBase &db ) {

    m_Db = db;
}


int TableIdleSettings::getTimeSecond( const int &idIdleSetting, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT time_second FROM idle_settings WHERE id_idle_setting = :id_idle_setting" );
    query.bindValue( ":id_idle_setting", idIdleSetting );
    query.exec();

    int timeSecond = QUERY_NO_DATA;

    if ( query.size() > 0 ) {
        QSqlRecord record = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            timeSecond = query.value( record.indexOf( "time_second" ) ).toInt();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return timeSecond;
}
