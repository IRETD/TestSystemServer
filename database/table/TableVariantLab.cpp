#include "TableVariantLab.h"

TableVariantLab::TableVariantLab( const OurDataBase &db ) {

    m_Db = db;
}


int TableVariantLab::getIdLab( const int &idVariant, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT id_lab FROM variant_lab WHERE id_variant = :id_variant" );
    query.bindValue( ":id_variant", idVariant );
    query.exec();

    int id = QUERY_ERROR;

    if ( query.size() > 0) {
        id = QUERY_NO_DATA;
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            id = query.value( rec.indexOf( "id_lab" ) ).toInt();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return id;
}


int TableVariantLab::getTimeLimit( const int &idVariant, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT time_limit FROM variant_lab WHERE id_variant = :id_variant" );
    query.bindValue( ":id_variant", idVariant );
    query.exec();

    int id = QUERY_ERROR;

    if ( query.size() > 0) {
        id = QUERY_NO_DATA;
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            id = query.value( rec.indexOf( "time_limit" ) ).toInt();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return id;
}
