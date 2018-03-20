#include "TableTestInput.h"

TableTestInput::TableTestInput( const OurDataBase &db ) {

    m_Db = db;
}

QStringList TableTestInput::getInputDataList( const int &idTest, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT input_data FROM test_input WHERE id_test = :id_test" );
    query.bindValue( ":id_test", idTest );
    query.exec();

    QStringList inputDataList;

    if ( query.size() > 0 ) {
        QSqlRecord recordTestInput = query.record();

        while ( query.next() ) {

            if ( query.isValid() ) {
                queryInfo.setResult( true );
                inputDataList.append( query.value(
                                          recordTestInput.indexOf( "input_data" ) ).toString() );
            }
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return inputDataList;
}
