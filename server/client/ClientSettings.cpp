#include "ClientSettings.h"


ClientSettings::ClientSettings() {
}


void ClientSettings::setRequestCountLimit( const int &requestCountLimit ) {

    m_RequestCountLimit = requestCountLimit;
}


void ClientSettings::setRequestTimeLimit( const int &requestTimeLimit ) {

    m_RequestTimeLimit = requestTimeLimit;
}


void ClientSettings::setBufferMaximumSize( const int &bufferMaximumSize ) {

    m_BufferMaximumSize = bufferMaximumSize;
}


int ClientSettings::getBufferMaximumSize() {

    return m_BufferMaximumSize;
}


int ClientSettings::getRequestCountLimit() {

    return m_RequestCountLimit;
}


int ClientSettings::getRequestTimeLimit() {

    return m_RequestTimeLimit;
}


