#include "TableStaticAnalyzer.h"


quint32 TableStaticAnalyzer::insert( quint32 idAboutHistory,
                                     TestResult idResult,
                                     OurQueryInfo &queryInfo ) {

    m_Db.startTransaction();

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "INSERT INTO static_analyzer(id_about_history, id_result) "
                    "VALUES(:id_about_history, :id_result)" );
    query.bindValue( ":id_about_history", idAboutHistory );
    query.bindValue( ":id_result",
                     static_cast < int > ( idResult ) );

    if ( query.exec() ) {
        query.prepare( "SELECT LAST_INSERT_ID();" );

        if ( query.exec() ) {
            QSqlRecord rec = query.record();

            if ( query.first() && query.isValid() ) {
                quint32 idStaticAnalyzer = query.value( rec.indexOf( "LAST_INSERT_ID()" ) ).toInt();
                queryInfo.setResult( true );
                query.finish();
                m_Db.commit();
                queryInfo.setTypeError( query.lastError().type() );
                queryInfo.setNumberError( query.lastError().number() );
                queryInfo.setDescription( query.lastError().text() );
                return idStaticAnalyzer;
            }

        }

    }
    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    m_Db.rollback();

    return QUERY_ERROR;
}


quint32 TableStaticAnalyzer::getIdStaticAnalyzer( quint32 idAboutHistory,
                                                  OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT id_static_analyzer FROM static_analyzer WHERE id_about_history = :id_about_history" );
    query.bindValue( ":id_about_history", idAboutHistory );
    query.exec();

    int idStaticAnalyzer;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            idStaticAnalyzer = query.value( rec.indexOf( "id_static_analyzer" ) ).toInt();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return idStaticAnalyzer;
}

TableStaticAnalyzer::TableStaticAnalyzer( const OurDataBase &db ) {

    m_Db = db;
}
