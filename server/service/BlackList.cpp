#include "BlackList.h"
#include <QDebug>

BlackList::BlackList( QObject *pObjct /*= 0*/ ) : QObject( pObjct ), m_TimerPeerAddress( this ) {

    m_LimitMinuteForPeerAddress = 120;
    m_TimerPeerAddressMinuteStart = 1000 * 60;
    connect( &m_TimerPeerAddress, &QTimer::timeout, this, &BlackList::checkPeerAddress );
}


BlackList::BlackList( const BlackList &copySource ) {

    m_TimerPeerAddressMinuteStart = copySource.m_TimerPeerAddressMinuteStart;
    m_LimitMinuteForPeerAddress = copySource.m_LimitMinuteForPeerAddress;
    m_PeerAddressTable = copySource.m_PeerAddressTable;
}


void BlackList::addPeerAddress( const QString &peerAddress, QDateTime &endTime ) {

    if ( !m_PeerAddressTable.contains( peerAddress ) ) {

        if ( !m_TimerPeerAddress.isActive() ) {
            m_TimerPeerAddress.start( m_TimerPeerAddressMinuteStart );
        }

        if ( endTime.isNull() ) {
            endTime = QDateTime::currentDateTime().addSecs( m_LimitMinuteForPeerAddress * 60 );
        }

        m_PeerAddressTable[ peerAddress ] = endTime;
    }
}


void BlackList::addPeerAddress( const QString &peerAddress ) {

    qDebug() << "BLACKLIST!";

    if ( !m_PeerAddressTable.contains( peerAddress ) ) {

        if ( !m_TimerPeerAddress.isActive() ) {
            m_TimerPeerAddress.start( m_TimerPeerAddressMinuteStart );
        }

        QDateTime endTime = QDateTime::currentDateTime().addSecs( m_LimitMinuteForPeerAddress * 60 );
        m_PeerAddressTable[ peerAddress ] = endTime;
    }
}


bool BlackList::removePeerAddress( const QString &peerAddress ) {

    return m_PeerAddressTable.remove( peerAddress );
}


bool BlackList::contain( const QString &peerAddress ) {

    return m_PeerAddressTable.contains( peerAddress );
}


void BlackList::setLimitMinutePeerAddress( const int &limitMinute ) {

    m_LimitMinuteForPeerAddress = limitMinute;
}


QHash < QString, QDateTime > BlackList::getPeerAddressTable() {

    return m_PeerAddressTable;
}


BlackList &BlackList::operator=( const BlackList &copySource ) {

    if ( this != &copySource ) {
        m_TimerPeerAddressMinuteStart = copySource.m_TimerPeerAddressMinuteStart;
        m_LimitMinuteForPeerAddress = copySource.m_LimitMinuteForPeerAddress;
        m_PeerAddressTable = copySource.m_PeerAddressTable;
    }

    return *this;
}


void BlackList::checkPeerAddress() {

    auto it = m_PeerAddressTable.begin();
    auto itEnd = m_PeerAddressTable.end();

    for ( ; it != itEnd; it++ ) {
        if ( it.value() > QDateTime::currentDateTime() ) {
            it = m_PeerAddressTable.erase( it );

            if ( it == itEnd ) {
                break;
            }

        }
    }

    if ( m_PeerAddressTable.isEmpty() ) {
        m_TimerPeerAddress.stop();
    }
}


