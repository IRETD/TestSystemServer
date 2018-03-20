#include "ServerSettings.h"
#include <QCoreApplication>


ServerSettings::ServerSettings() {

    m_IdleTimeSecond = 5;
    m_ClientBufferKilobyteMaxSize = 100;
    m_RequestCountLimit = 100;
    m_RequestTimeSecondLimit = 60;
    m_DirectoryTest = QCoreApplication::applicationDirPath();
    m_TimeMinuteInPeerAddressBlackList = 120;
}


void ServerSettings::setIdleTimeSecond( const int &idleTimeSecond ) {

    m_IdleTimeSecond = idleTimeSecond;
}


void ServerSettings::setClientBufferKilobyteMaxSize( const int &clientBufferKilobyteMaxSize ) {

    m_ClientBufferKilobyteMaxSize = clientBufferKilobyteMaxSize;
}


void ServerSettings::setRequestCountLimit( const int &requestCountLimit ) {

    m_RequestCountLimit = requestCountLimit;
}


void ServerSettings::setRequestTimeSecondLimit( const int &requestTimeSecondLimit ) {

    m_RequestCountLimit = requestTimeSecondLimit;
}


void ServerSettings::setTimeMinuteInPeerAddressBalckList( const int &timeMinuteInPeerAddressBlackList ) {

    m_TimeMinuteInPeerAddressBlackList = timeMinuteInPeerAddressBlackList;
}


void ServerSettings::setDirectoryTest( const QString &directoryTest ) {

    m_DirectoryTest = directoryTest;
}


int ServerSettings::getIdleTimeSecond() const {

    return m_IdleTimeSecond;
}


int ServerSettings::getClientBufferKilobyteMaxSize() const {

    return m_ClientBufferKilobyteMaxSize;
}


int ServerSettings::getRequestCountLimit() const {

    return m_RequestCountLimit;
}


int ServerSettings::getRequestTimeLimit() const {

    return m_RequestTimeSecondLimit;
}


int ServerSettings::getTimeMinuteInPeerAddressBalckList() const {

    return m_TimeMinuteInPeerAddressBlackList;
}


QString ServerSettings::getDirectoryTest() const {

    return m_DirectoryTest;
}
