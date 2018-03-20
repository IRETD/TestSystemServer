#include "TableAdditionalColumnAboutHistory.h"


TableAdditionalColumnAboutHistory::TableAdditionalColumnAboutHistory( const OurDataBase &db ) {

    m_Db = db;
}


QString TableAdditionalColumnAboutHistory::getName( const AdditionalColumnType &idAdditionalColumn,
                                                    OurQueryInfo &queryInfo ) {

    QSqlQuery query(QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT name FROM additional_column_about_history WHERE id_additional_column = :id_additional_column" );
    query.bindValue( ":id_additional_column", static_cast < int > ( idAdditionalColumn ) );
    query.exec();

    QString columnName = "";

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid( )) {
            queryInfo.setResult( true );
            columnName = query.value( rec.indexOf( "name" ) ).toString();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return columnName;
}
