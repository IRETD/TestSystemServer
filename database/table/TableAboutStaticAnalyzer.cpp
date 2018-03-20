#include "TableAboutStaticAnalyzer.h"

TableAboutStaticAnalyzer::TableAboutStaticAnalyzer( const OurDataBase &db ) {

    m_Db = db;
}


void TableAboutStaticAnalyzer::insert( quint32 idStaticAnalyzer,
                                       StaticAnalyzer staticAnalyzerData ,
                                       OurQueryInfo &queryInfo ) {

    QSqlQuery query(QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "INSERT INTO about_static_analyzer(id_static_analyzer, id_type_static_analyzer, description, location_file, line) "
            "VALUES(:id_static_analyzer, :id_type_static_analyzer, :description, :location_file, :line)" );
    query.bindValue( ":id_static_analyzer",
                     idStaticAnalyzer );
    query.bindValue( ":id_type_static_analyzer",
                     static_cast < int > ( staticAnalyzerData.getTypeStaticAnalyzer() ) );
    query.bindValue( ":description", staticAnalyzerData.getDescription() );
    query.bindValue( ":location_file", staticAnalyzerData.getLocationFile() );
    query.bindValue( ":line", staticAnalyzerData.getLine() );
    query.exec();

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );
}


QList < StaticAnalyzer > TableAboutStaticAnalyzer::getStaticAnalyzerList( quint32 idStaticAnalyzer,
                                                                          OurQueryInfo &queryInfo) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT * from about_static_analyzer "
                   " WHERE id_static_analyzer =:id_static_analyzer" );
    query.bindValue( ":id_static_analyzer", idStaticAnalyzer );
    query.exec();

    QList < StaticAnalyzer > aboutStaticAnalyzerList;

    if ( query.size() > 0 ) {
        QSqlRecord record = query.record();

        while ( query.next() ) {

            if ( query.isValid() ) {
                StaticAnalyzer staticAnalyzerInfo;
                staticAnalyzerInfo.setIdAboutStaticAnalyzer( query.value( record.indexOf( "id_about_static_analyzer" ) ).toInt() );
                staticAnalyzerInfo.setTypeStaticAnalyzer( static_cast < TypeStaticAnalyzer > (
                                                              ( query.value( record.indexOf( "id_type_static_analyzer" ) ).toInt() ) ) );
                staticAnalyzerInfo.setDescription( query.value( record.indexOf( "description" ) ).toString() );
                staticAnalyzerInfo.setLocationFile( query.value( record.indexOf( "location_file" ) ).toString() );
                staticAnalyzerInfo.setLine( query.value( record.indexOf( "line" ) ).toInt() );

                queryInfo.setResult( true );

                aboutStaticAnalyzerList.push_back( staticAnalyzerInfo );
            }
        }
    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return aboutStaticAnalyzerList;
}
