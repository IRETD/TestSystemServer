#include "TableLab.h"


TableLab::TableLab( const OurDataBase &db ) {

    m_Db = db;
}


Lab TableLab::getLab( const int &idLab,
                      OurQueryInfo &queryInfo )  {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT * FROM lab WHERE id_lab = :id_lab" );
    query.bindValue( ":id_lab", idLab );
    query.exec();

    Lab lab;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            lab.setIdDiscipline( query.value( rec.indexOf( "id_discipline" ) ).toInt() );
            lab.setIdLab( idLab );
            lab.setName( query.value( rec.indexOf( "name" ) ).toString() );
            lab.setPurpose( query.value( rec.indexOf( "purpose" ) ).toString() );
            lab.setDesiredDate( query.value( rec.indexOf( "desiried_date" ) ).toDateTime() );
            lab.setCriticalDate( query.value( rec.indexOf( "critical_date" ) ).toDateTime() );
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return lab;
}

QList < Lab > TableLab::getLabListByIdDiscipline( const int &idDiscipline,
                                                  OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT * FROM lab WHERE id_discipline = :id_discipline" );
    query.bindValue( ":id_discipline", idDiscipline );
    query.exec();

    QList < Lab > labList;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();
        while ( query.next() ) {
            if ( query.isValid() ) {
                Lab lab;
                queryInfo.setResult( true );
                lab.setIdDiscipline( query.value( rec.indexOf( "id_discipline" ) ).toInt() );
                lab.setIdLab( query.value( rec.indexOf( "id_lab" ) ).toInt() );
                lab.setName( query.value( rec.indexOf( "name" ) ).toString() );
                lab.setPurpose( query.value( rec.indexOf( "purpose" ) ).toString() );
                lab.setDesiredDate( query.value( rec.indexOf( "desiried_date" ) ).toDateTime() );
                lab.setCriticalDate( query.value( rec.indexOf( "critical_date" ) ).toDateTime() );
                labList.append( lab );
            }
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return labList;

}

int TableLab::getIdDiscipline( const int &idLab , OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT id_discipline FROM lab WHERE id_lab = :id_lab" );
    query.bindValue( ":id_lab", idLab );
    query.exec();

    int idDiscipline;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            idDiscipline = query.value( rec.indexOf( "id_discipline" ) ).toInt();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return idDiscipline;
}


QString TableLab::getName( const int &idLab, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT name FROM lab WHERE id_lab = :id_lab" );
    query.bindValue( ":id_lab", idLab );
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


QString TableLab::getPurpose( const int &idLab, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT purpose FROM lab WHERE id_lab = :id_lab" );
    query.bindValue( ":id_lab", idLab );
    query.exec();

    QString purpose;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            purpose = query.value( rec.indexOf( "purpose" ) ).toString();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return purpose;
}


QDateTime TableLab::getDesiredDate( const int &idLab, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT desiried_date FROM lab WHERE id_lab = :id_lab" );
    query.bindValue( ":id_lab", idLab );
    query.exec();

    QDateTime desiredDate;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            desiredDate = query.value( rec.indexOf( "desiried_date" ) ).toDateTime();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return desiredDate;
}


QDateTime TableLab::getCriticalDate( const int &idLab, OurQueryInfo &queryInfo ) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT critical_date FROM lab WHERE id_lab = :id_lab" );
    query.bindValue( ":id_lab", idLab );
    query.exec();

    QDateTime criticalDate;

    if ( query.size() > 0 ) {
        QSqlRecord rec = query.record();

        if ( query.first() && query.isValid() ) {
            queryInfo.setResult( true );
            criticalDate = query.value( rec.indexOf( "critical_date" ) ).toDateTime();
        }

    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return criticalDate;

}
