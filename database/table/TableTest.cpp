#include "TableTest.h"

TableTest::TableTest( const OurDataBase &db ) {

    m_Db = db;
}

QList < quint32 > TableTest::getIdTestList( const int &idVariant, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT id_test FROM test WHERE id_variant = :id_variant" );
    query.bindValue( ":id_variant", idVariant );
    query.exec();

    QList < quint32 > idTestList;

    if ( query.size() > 0 ) {
        QSqlRecord recordTest = query.record();
        while ( query.next() ) {

            if ( query.isValid() ) {
                queryInfo.setResult( true );
                idTestList.append( query.value( recordTest.indexOf( "id_test" ) ).toInt() );
            }

        }
    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return idTestList;
}
