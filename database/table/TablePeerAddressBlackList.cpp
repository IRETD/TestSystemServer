#include "TablePeerAddressBlackList.h"


TablePeerAddressBlackList::TablePeerAddressBlackList( const OurDataBase &db ) {

    m_Db = db;
}


void TablePeerAddressBlackList::getBlackList( BlackList &blackList, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT peer_address,end_time FROM peer_address_black_list" );
    query.exec();

    if ( query.size() > 0 ) {
        QSqlRecord record = query.record();

        while ( query.next() ) {

            if ( query.isValid() ) {
                queryInfo.setResult( true );
                QString peerAddress = query.value( record.indexOf( "peer_address" ) ).toString();
                QDateTime endTime = query.value( record.indexOf( "end_time" ) ).toDateTime();
                blackList.addPeerAddress( peerAddress, endTime );
            }

        }
    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );
}


void TablePeerAddressBlackList::insert( const QString &peerAddress, const QDateTime &beginTime, const QDateTime &endTime,
                                        OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "INSERT INTO peer_address_black_list (peer_address, begin_time, end_time) "
                   "VALUES (:peer_address, :begin_time, :end_time)");
    query.bindValue( ":peer_address", peerAddress );
    query.bindValue( ":begin_time", beginTime );
    query.bindValue( ":end_time", endTime );
    query.exec();

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );
}


void TablePeerAddressBlackList::remove( const QString &peerAddress, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "DELETE FROM peer_address_black_list WHERE peer_address = :peer_address" );
    query.bindValue( ":peer_address", peerAddress );
    query.exec();

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );
}
