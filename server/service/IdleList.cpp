#include "IdleList.h"


IdleList::IdleList( QObject *pObjct ) : QObject( pObjct ), m_Timer( this ) {

    m_TimerStartSecond = 1000;
    m_LimitSecondForIdle = 5;
    connect( &m_Timer, &QTimer::timeout, this, &IdleList::checkIdleList );
}


IdleList::IdleList( const IdleList &copySource ) {

    m_IdleTable = copySource.m_IdleTable;
    m_TimerStartSecond = copySource.m_TimerStartSecond;
    m_LimitSecondForIdle = copySource.m_LimitSecondForIdle;
}


void IdleList::addClient( int idClient ) {

    if ( !m_IdleTable.contains( idClient ) ) {

        if ( !m_Timer.isActive() ) {
            m_Timer.start( m_TimerStartSecond );
        }

        QTime watch;
        watch.start();
        m_IdleTable[ idClient ] = watch;
    }
}


void IdleList::removeClient( int idClient ) {

    m_IdleTable.remove( idClient );
    checkIdleTableForEmpty();
}


void IdleList::checkIdleTableForEmpty() {

    if ( m_IdleTable.isEmpty() ) {
        m_Timer.stop();
    }
}


bool IdleList::contain( int idClient ) {

    return m_IdleTable.contains( idClient );
}


void IdleList::setLimitSecondForIdle( const int &limitSecond ) {

    m_LimitSecondForIdle = limitSecond;
}


IdleList &IdleList::operator=( const IdleList &copySource ) {

    if ( this != &copySource ) {
        m_IdleTable = copySource.m_IdleTable;
        m_TimerStartSecond = copySource.m_TimerStartSecond;
        m_LimitSecondForIdle = copySource.m_LimitSecondForIdle;
    }

    return *this;
}


void IdleList::checkIdleList() {

    auto it = m_IdleTable.begin();
    auto itEnd = m_IdleTable.end();

    for ( ; it != itEnd; it++ ) {
        //переводим в секунды прошедшее время простоя клиента
        int seconds = it.value().elapsed() / MILLISECONDS_PER_SECOND;

        if ( seconds >  m_LimitSecondForIdle ) {
            emit clientIsIdle( it.key() );
            it = m_IdleTable.erase( it );
            if ( it == itEnd ) {
                break;
            }
        }

    }

    checkIdleTableForEmpty();
}
