#include "Server.h"
#include <QDebug>
#include <QtTest/QTest>


Server::Server( QObject *pObjct ) : QTcpServer( pObjct ) {
}


bool Server::createServer( const int &port /*= 1500*/ ) {

    if ( !this -> isListening() ) {
        return this -> listen( QHostAddress::Any, port );
    }
    else {
        return false;
    }
}


bool Server::closeServer() {

    if ( this -> isListening() ) {
        this -> close();
        return true;
    }
    return false;
}


QTcpServer *Server::getServer() {

    return this;
}


void Server::incomingConnection( qintptr handle ) {

    emit clientIsConnected( handle );
}
