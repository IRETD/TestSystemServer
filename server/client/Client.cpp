#include "Client.h"


Client::Client() {

    m_ClientType = ClientType::UNKNOWN;
}


Client::Client( const int &bufferMaximumSize,
                const int &requestCountLimit,
                const int &requestTimeLimit ) {

    m_Settings.setBufferMaximumSize( bufferMaximumSize );
    m_Settings.setRequestCountLimit( requestCountLimit );
    m_Settings.setRequestTimeLimit( requestTimeLimit );
    m_RequestStatistics.setRequestCountLimit( requestCountLimit );
    m_RequestStatistics.setRequestTimeSecondLimit( requestTimeLimit );
    m_ClientType = ClientType::UNKNOWN;

    m_RecievedRequestSize = REQUEST_SIZE_IS_NOT_READ;
}


void Client::setIdClient(const ID_USER &idClient ) {

    m_IdClient = idClient;
}


void Client::setRecievedRequestSize( const int &recievedRequestSize ) {

    m_RecievedRequestSize = recievedRequestSize;
}


void Client::setClientBuffer( const QByteArray &clientBuffer ) {

    this -> m_ClientBuffer = clientBuffer;
}


void Client::addInClientBuffer( const QByteArray &clientBuffer ) {

    this -> m_ClientBuffer.append( clientBuffer );
}


void Client::clearClientBuffer() {

    m_ClientBuffer.clear();
}


ClientSettings &Client::getSettings() {

    return m_Settings;
}


ClientRequestStatistics &Client::getRequestStatistics() {

    return m_RequestStatistics;
}


QByteArray &Client::getClientBuffer() {

    return m_ClientBuffer;
}


int Client::getIdClient() const {

    return m_IdClient;
}


int Client::getRecievedRequestSize() const {

    return m_RecievedRequestSize;
}


bool Client::isAuthorized() const {

    return m_IdClient >= 0;
}


void Client::setClientType( ClientType clientType ) {

    m_ClientType = clientType;
}


ClientType Client::getClientType() {

    return m_ClientType;
}

