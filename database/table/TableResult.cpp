#include "TableResult.h"

TableResult::TableResult( const OurDataBase &db ) {

    m_Db = db;
}

QString TableResult::getResult( const TestResult &idResult, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT name FROM result WHERE id_result = :result" );
    query.bindValue( ":result", static_cast < int > ( idResult ) );
    query.exec();

    QString stageResult;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            stageResult = query.value( rec.indexOf( "name" ) ).toString();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return stageResult;
}
