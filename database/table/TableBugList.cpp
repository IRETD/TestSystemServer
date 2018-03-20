#include "TableBugList.h"


TableBugList::TableBugList( const OurDataBase &db ) {

    m_Db = db;
}

void TableBugList::insert( const QString &description, const QDateTime &bugDateTime, const QString &className,
                           const QString &functionName, const QString &functionInputData, const int &bugLineNumber,
                           const QString &bugLineDescritpion, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "INSERT INTO bug_list(description, bug_date_time, class_name, function_name, function_input_data, bug_line_number, bug_line_description) "
            "VALUES(:description, :bug_date_time, :class_name, :function_name, :function_input_data, :bug_line_number, :bug_line_description)" );
    query.bindValue( ":description", description );
    query.bindValue( ":bug_date_time", bugDateTime );
    query.bindValue( ":class_name", className );
    query.bindValue( ":function_name", functionName );
    query.bindValue( ":function_input_data", functionInputData );
    query.bindValue( ":bug_line_number", bugLineNumber );
    query.bindValue( ":bug_line_description", bugLineDescritpion );

    query.exec();

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );
}
