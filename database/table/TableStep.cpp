#include "TableStep.h"

TableStep::TableStep( const OurDataBase &db ) {

    m_Db = db;
}

QString TableStep::getName( const StepType &idStep, OurQueryInfo &queryInfo ) {

    QSqlQuery query(QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT name FROM step WHERE id_step = :id_step" );
    query.bindValue( ":id_step", static_cast < int > ( idStep ) );
    query.exec();

    QString stepName = "";

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid( )) {
            queryInfo.setResult( true );
            stepName = query.value( rec.indexOf( "name" ) ).toString();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return stepName;
}
