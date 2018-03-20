#include "TableAuthorizationHistory.h"


TableAuthorizationHistory::TableAuthorizationHistory( const OurDataBase &db ) {

    m_Db = db;
}


void TableAuthorizationHistory::insert( const int &idClient, const QDateTime &dateAuthorization, const bool &result,
                                        const QString &login, const QString &password, OurQueryInfo &queryInfo ) {

    QSqlQuery query(QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "INSERT INTO authorization_history(id_client, date_authorization, result, login, password) "
            "VALUES(:id_client, :date_authorization, :result, :login, :password)" );
    query.bindValue( ":id_client", idClient );
    query.bindValue( ":date_authorization", dateAuthorization );
    query.bindValue( ":result", result );
    query.bindValue( ":login", login );
    query.bindValue( ":password", password );
    query.exec();

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );
}



