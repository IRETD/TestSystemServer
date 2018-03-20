#include "TableDiscipline.h"

TableDiscipline::TableDiscipline( const OurDataBase &db ) {

    m_Db = db;
}

Discipline TableDiscipline::getDiscipline( const int &idDiscipline,
                                           OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT * FROM discipline WHERE id_discipline = :id_discipline" );
    query.bindValue( ":id_discipline", idDiscipline );
    query.exec();

    Discipline discipline;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            discipline.setIdDiscipline( idDiscipline );
            discipline.setName( query.value( rec.indexOf( "name" ) ).toString() );
            discipline.setDescription( query.value( rec.indexOf( "description" ) ).toString() );
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return discipline;

}

QString TableDiscipline::getName( const int &idDiscipline, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT name FROM discipline WHERE id_discipline = :id_discipline" );
    query.bindValue( ":id_discipline", idDiscipline );
    query.exec();

    QString name;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            name = query.value( rec.indexOf( "name" ) ).toString();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return name;
}


QString TableDiscipline::getDescription( const int &idDiscipline, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT description FROM discipline WHERE id_discipline = :id_discipline" );
    query.bindValue( ":id_discipline", idDiscipline );
    query.exec();

    QString description;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            description = query.value( rec.indexOf( "description" ) ).toString();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return description;
}
