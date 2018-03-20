#include "database/OurDataBase.h"
#include <QDebug>


//----------------------------------------------------------------
// Подключение к БД
//----------------------------------------------------------------
OurDataBase::OurDataBase() {

}


bool OurDataBase::connectToDataBase( const QString &login, const QString &password,
                                     const QString &nameConnection, const int &port, const QString &hostName,
                                     const QString &databaseName ) {


    m_ConnectionName = nameConnection;

    if ( m_Db.isOpen() ) {
        m_Db.close();
    }

    if ( QSqlDatabase::contains( m_ConnectionName ) ) {
        m_Db = QSqlDatabase::database( m_ConnectionName, false );
    }
    else {
        m_Db = QSqlDatabase::addDatabase( "QMYSQL", m_ConnectionName );
    }

    m_Db.setDatabaseName( databaseName );
    m_Db.setUserName( login );
    m_Db.setPassword( password );
    m_Db.setHostName( hostName );
    m_Db.setPort( port );

    return m_Db.open();
}


bool OurDataBase::startTransaction() {

    return m_Db.transaction();
}


bool OurDataBase::commit() {

    return m_Db.commit();
}


bool OurDataBase::rollback() {

    return m_Db.rollback();
}

bool OurDataBase::getStatus() {


    return m_Db.isOpen();
}


bool OurDataBase::isConnectionActive() {

    return m_Db.isOpen();
}


QSqlError OurDataBase::getLastError() {

    return m_Db.lastError();
}


QString OurDataBase::getConnectionName() {

    return m_ConnectionName;
}
