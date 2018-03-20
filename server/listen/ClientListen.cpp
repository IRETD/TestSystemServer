#include "ClientListen.h"
#include <QTest>


ClientListen::ClientListen(QObject *parent) : QObject(parent) {
}


void ClientListen::startServer() {

    this -> thread() -> setObjectName( "first" );
    Server *pServer = new Server();
    if ( pServer -> createServer() ) {
        qDebug() << "Server was started!" << this -> thread();
        connect( pServer, &Server::clientIsConnected,
                 this, &ClientListen::clientConnected );
    }
    else {
        qDebug() << "Error!";
    }
}
