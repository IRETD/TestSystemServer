#include "TableTestOutput.h"


TableTestOutput::TableTestOutput( const OurDataBase &db ) {

    m_Db = db;
}


QStringList TableTestOutput::getOutputDataList( const int &idTest, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT output_data FROM test_output WHERE id_test = :id_test" );
    query.bindValue( ":id_test", idTest );
    query.exec();

    QStringList outputDataList;

    if ( query.size() > 0 ) {
        QSqlRecord recordTestOutput = query.record();

        while ( query.next() ) {

            if ( query.isValid() ) {
                queryInfo.setResult( true );
                outputDataList.append( query.value(
                                           recordTestOutput.indexOf( "output_data" ) ).toString() );
            }

        }
    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return outputDataList;
}
