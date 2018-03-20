#include "TableUser.h"

TableUser::TableUser( const OurDataBase &db ) {

    m_Db = db;
}

int TableUser::getId( const QString &login, const QString &password, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT id_user FROM user WHERE login = :login"
                   " and password = :password" );
    query.bindValue( ":login", login );
    query.bindValue( ":password", password );
    query.exec();

    int id = QUERY_NO_DATA;

    if ( query.size() > 0) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            id = query.value( rec.indexOf( "id_user" ) ).toInt();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return id;
}
