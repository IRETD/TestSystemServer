#include "TableMessageCatalogForClient.h"

TableMessageCatalogForClient::TableMessageCatalogForClient( const OurDataBase &db ) {

    m_Db = db;
}

QString TableMessageCatalogForClient::getMessage( const MessageType &idMessage, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT message FROM message_catalog_for_client WHERE id_message = :id_message" );
    query.bindValue( ":id_message", static_cast < int > ( idMessage ) );
    query.exec();

    QString message;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            message = query.value( rec.indexOf( "message" ) ).toString();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return message;
}
