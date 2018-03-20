#include "TableHistory.h"
#include <database/table/TableResult.h>


TableHistory::TableHistory( const OurDataBase &db ) {

    m_Db = db;
}


int TableHistory::insert( const int &idUserLab, const TestResult &idResult,
                          const QDateTime &date, const QString &pathCodeFolder, OurQueryInfo &queryInfo ) {

    m_Db.startTransaction();

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "INSERT INTO history(id_user_lab, id_result, date_history, path_code_folder) "
                    "VALUES(:id_user_lab, :id_result, :date, :path_code_folder)" );
    query.bindValue( ":id_user_lab", idUserLab );
    query.bindValue( ":id_result",
                     static_cast < int > ( idResult ) );
    query.bindValue( ":date", date );
    query.bindValue( ":path_code_folder", pathCodeFolder );

    if ( query.exec() ) {
        query.prepare( "SELECT LAST_INSERT_ID();" );

        if ( query.exec() ) {
            QSqlRecord rec = query.record();

            if ( query.first() && query.isValid() ) {
                int idHistory = query.value( rec.indexOf( "LAST_INSERT_ID()" ) ).toInt();
                queryInfo.setResult( true );
                query.finish();
                m_Db.commit();
                queryInfo.setTypeError( query.lastError().type() );
                queryInfo.setNumberError( query.lastError().number() );
                queryInfo.setDescription( query.lastError().text() );
                return idHistory;
            }

        }

    }
    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    m_Db.rollback();

    return QUERY_ERROR;
}


void TableHistory::updateResult( const int &idHistory, const TestResult &idResult, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "UPDATE history SET id_result=:id_result "
                   " WHERE id_history=:id_history1" );
    query.bindValue( ":id_history1", idHistory );
    query.bindValue( ":id_result",
                     static_cast < int > ( idResult ) );
    query.exec();

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

}


QList < History > TableHistory::getHistoryList( const int &idUserLab, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT * from history "
                   " WHERE id_user_lab =:id_user_lab" );
    query.bindValue( ":id_user_lab", idUserLab );
    query.exec();

    QList < History > historyList;

    if ( query.size() > 0 ) {
        QSqlRecord record = query.record();

        while ( query.next() ) {

            if ( query.isValid() ) {
                History history;
                history.setIdHistory( query.value( record.indexOf( "id_history" ) ).toInt() );
                history.setIdUserLab( idUserLab );
                history.setDateHistory( query.value( record.indexOf( "date_history" ) ).toDateTime() );

                TestResult idResult = static_cast < TestResult > ( query.value( record.indexOf( "id_result" ) ).toInt() );
                TableResult resultTable( m_Db );
                //!!!!!!!!!!!!!!!!!!
                history.setResult( static_cast < TestResult > ( idResult ) );
                history.setTextResult( resultTable.getResult( idResult, queryInfo ) );

                queryInfo.setResult( true );

                historyList.push_back( history );
            }
        }
    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return historyList;
}
