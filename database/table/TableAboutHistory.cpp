#include "TableAboutHistory.h"
#include <database/table/TableResult.h>
#include <database/table/TableStep.h>




TableAboutHistory::TableAboutHistory( const OurDataBase &db ) {

    m_Db = db;
}

int TableAboutHistory::insert( const int &idHistory,
                               const StepType &idStep,
                               TestResultsInfo &testResultsInfo,
                               OurQueryInfo &queryInfo ) {

    m_Db.startTransaction();

    TestResult testResult = testResultsInfo.getTestResult();
    QString peakMemory = testResultsInfo.getPeakMemory();
    QString timePassed = testResultsInfo.getTimePassed();
    AdditionalColumnType additionColumn = testResultsInfo.getAdditionalColumn();

    QSqlQuery query(QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "INSERT INTO about_history(id_history, id_step, id_result, memory, time, additional_column) "
            "VALUES(:id_history, :id_step, :result, :memory, :time, :additional_column)" );
    query.bindValue( ":id_history", idHistory );
    query.bindValue( ":id_step",
                     static_cast < int > ( idStep ) );
    query.bindValue( ":result",
                     static_cast < int > ( testResult ) );
    query.bindValue( ":memory",
                     peakMemory);
    query.bindValue( ":time",
                     timePassed );
    query.bindValue( ":additional_column",
                     static_cast < int > ( additionColumn ) );

    if ( query.exec() ) {
        query.prepare( "SELECT LAST_INSERT_ID();" );

        if ( query.exec() ) {
            QSqlRecord rec = query.record();

            if ( query.first() && query.isValid() ) {
                int idAboutHistory = query.value( rec.indexOf( "LAST_INSERT_ID()" ) ).toInt();
                queryInfo.setResult( true );
                query.finish();
                m_Db.commit();
                queryInfo.setTypeError( query.lastError().type() );
                queryInfo.setNumberError( query.lastError().number() );
                queryInfo.setDescription( query.lastError().text() );
                return idAboutHistory;
            }

        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    m_Db.rollback();

    return QUERY_ERROR;
}

int TableAboutHistory::insert( const int &idHistory,
                               const StepType &idStep,
                               TestResult &testResult,
                               OurQueryInfo &queryInfo ) {

    TestResultsInfo testResultsInfo;
    testResultsInfo.setTestResult( testResult );
    return insert( idHistory,
                   idStep,
                   testResultsInfo,
                   queryInfo );
}


void TableAboutHistory::updateResult( const int &idAboutHistory,
                                      TestResultsInfo &testResultsInfo,
                                      OurQueryInfo &queryInfo ) {

    TestResult testResult = testResultsInfo.getTestResult();
    QString peakMemory = testResultsInfo.getPeakMemory();
    QString timePassed = testResultsInfo.getTimePassed();
    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "UPDATE about_history SET id_result=:id_result, memory=:memory, time=:time "
                   " WHERE id_about_history=:id_about_history" );
    query.bindValue( ":id_about_history", idAboutHistory);
    query.bindValue( ":id_result",
                     static_cast < int > ( testResult ) );
    query.bindValue( ":memory",
                     peakMemory);
    query.bindValue( ":time",
                     timePassed );
    query.exec();

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );
}


QList < AboutHistory > TableAboutHistory::getAboutHistoryList( const int &idHistory,
                                                               OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT * from about_history "
                   " WHERE id_history =:id_history" );
    query.bindValue( ":id_history", idHistory );
    query.exec();

    QList < AboutHistory > aboutHistoryList;

    if ( query.size() > 0 ) {
        QSqlRecord record = query.record();

        while ( query.next() ) {

            if ( query.isValid() ) {
                AboutHistory aboutHistory;
                aboutHistory.setIdHistory( idHistory );
                aboutHistory.setIdAboutHistory( query.value( record.indexOf( "id_about_history" ) ).toInt() );

                TestResult idResult = static_cast < TestResult > ( query.value( record.indexOf( "id_result" ) ).toInt() );
                //!!!!!!!
                ///ПОКА НЕ ИСПОЛЬЗУЕМ!
                /*
                aboutHistory.setResult( static_cast < TestResult > ( idResult ) );
                */
                TableResult resultTable( m_Db );
                aboutHistory.setTextResult( resultTable.getResult( idResult,
                                                                    queryInfo ) );
                aboutHistory.setResult( idResult );


                StepType idStep = static_cast < StepType > ( query.value( record.indexOf( "id_step" ) ).toInt() );
                TableStep stepTable( m_Db );
                aboutHistory.setDescription( stepTable.getName( idStep,
                                                                queryInfo ) );
                aboutHistory.setStepType( idStep );

                /*
                ///Для каждой записи наименование столбца :((((
                ColumnNameAboutHistory idAboutHistoryTable = static_cast < ColumnNameAboutHistory > ( query.value( record.indexOf( "id_about_history_table" ) ).toInt() );
                TableAboutHistoryTable columnNameTable( m_Db );
                QString columnName = columnNameTable.getAboutHistoryTableName( idAboutHistoryTable,
                                                                               queryInfo );
                aboutHistory.setColumnName( columnName );
                */

                QString memory = query.value( record.indexOf( "memory" ) ).toString();
                aboutHistory.setMemory( memory );
                QString time = query.value( record.indexOf( "time" ) ).toString();
                aboutHistory.setTime( time );

                //пока что пусто :)
                QString additionalColumnName;
                AdditionalColumnType idAdditionalColumn = static_cast < AdditionalColumnType > (
                                                            query.value( record.indexOf( "additional_column" )).toInt() );
                if ( idAdditionalColumn != AdditionalColumnType::NONE_ADDITIONAL_COLUMN) {

                    //TableAdditionalColumnAboutHistory tableAdditionalColumn( m_Db );
                    //additionalColumnName = tableAdditionalColumn.getName( idAdditionalColumn,
                                                                          //queryInfo );
                }
                aboutHistory.setAdditionalColumn( additionalColumnName );

                queryInfo.setResult( true );


                aboutHistoryList.push_back( aboutHistory );
            }
        }
    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return aboutHistoryList;

}

/*
QList < AboutHistory > TableAboutHistory::getDescriptionStepList( const int &idHistory,
                                                                  OurQueryInfo &queryInfo ) {


    return getAboutHistoryList( idHistory,
                                Field::STEP,
                                queryInfo );
}

QList < AboutHistory > TableAboutHistory::getDescriptionResultList( const int &idHistory,
                                                                    OurQueryInfo &queryInfo ) {

    return getAboutHistoryList( idHistory,
                                Field::RESULT,
                                queryInfo );

}
*/
