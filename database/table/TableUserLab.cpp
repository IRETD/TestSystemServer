#include "TableUserLab.h"


TableUserLab::TableUserLab( const OurDataBase &db ) {

    m_Db = db;
}


int TableUserLab::getIdVariant( const int &idUserLab, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT id_variant FROM user_lab WHERE id_user_lab = :id_user_lab" );
    query.bindValue( ":id_user_lab", idUserLab );
    query.exec();

    int id = QUERY_NO_DATA;

    if ( query.size() > 0) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            id = query.value( rec.indexOf( "id_variant" ) ).toInt();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return id;
}


bool TableUserLab::idUserLabExist( const int &idUserLab, const int &idUser, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT id_user_lab FROM user_lab WHERE id_user_lab = :id_user_lab and id_user = :id_user" );
    query.bindValue( ":id_user_lab", idUserLab );
    query.bindValue( ":id_user", idUser );

    query.exec();

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return query.size() > 0;
}


QList < ID_USER_LAB > TableUserLab::getIdUserLab( const ID_USER &idUser,
                                                  OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT id_user_lab FROM user_lab WHERE id_user = :id_user" );
    query.bindValue( ":id_user", idUser );
    query.exec();


    QList < ID_USER_LAB > idUserLabList;

    if ( query.size() > 0 ) {
        QSqlRecord recordTestInput = query.record();

        while ( query.next() ) {

            if ( query.isValid() ) {
                queryInfo.setResult( true );
                idUserLabList.append( query.value(
                                          recordTestInput.indexOf( "id_user_lab" ) ).toInt() );
            }
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return idUserLabList;
}


