#include "request/Request.h"


Request::Request() {
}


void Request::setPriority( const bool &priority ) {

    m_Priority = priority;
}


bool Request::getPriority() {

    return m_Priority;
}


void Request::setRequestType( const RequestType &requestType ) {

    m_RequestType = requestType;
}


RequestType Request::getRequestType() {

    return m_RequestType;
}


void Request::setRequestSender( RequestSender requestSender ) {

    m_RequestSender = requestSender;
}



void Request::readStream( QDataStream &stream ) {

    //ничего не делаем
}


void Request::setIdClient( const int &idClient ) {

    m_IdClient = idClient;
}


int Request::getIdClient() const {

    return m_IdClient;
}


RequestSender Request::getRequestSender() {

    return m_RequestSender;
}





