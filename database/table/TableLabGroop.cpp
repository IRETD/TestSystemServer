#include "TableLabGroop.h"

TableLabGroop::TableLabGroop( const OurDataBase &db ) {

    m_Db = db;
}

/*
//именно Groop, а не Group :)
QList < IdLabGroopIdGroop > TableLabGroop::getIdLabGroopIdGroopList( quint32 idLab,
                                                                     OurQueryInfo &queryInfo) {

    QSqlQuery query( QSqlDatabase::database( m_Db.getConnectionName() ) );
    query.prepare( "SELECT * FROM lab_groop WHERE id_lab = :id_lab" );
    query.bindValue( ":id_lab", idLab );
    query.exec();

    QList < IdLabGroopIdGroop > idLabGroopIdGroopList;

    if ( query.size() > 0 ) {
        QSqlRecord record = query.record();

        while ( query.next() ) {

            if ( query.isValid() ) {
                IdLabGroopIdGroop idLabGroopIdGroop;
                idLabGroopIdGroop.m_IdGroop = query.value( record.indexOf( "id_groop" ) ).toInt();
                idLabGroopIdGroop.m_IdLabGroop = query.value( record.indexOf( "id_lab_groop" ) ).toInt();

                queryInfo.setResult( true );

                idLabGroopIdGroopList.push_back( idLabGroopIdGroop );
            }
        }
    }

    queryInfo.setTypeError( query.lastError().type() );
    queryInfo.setNumberError( query.lastError().number() );
    queryInfo.setDescription( query.lastError().text() );

    return idLabGroopIdGroopList;
}
*/
