#ifndef CLIENTLISTEN_H
#define CLIENTLISTEN_H

#include <QThread>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <server/Server.h>
#include "server/service/ClientService.h"
#include <request/client/RequestClient.h>


class ClientListen : public QObject {

    Q_OBJECT

private:
    Server *m_pServer;

public:
    ClientListen( QObject *parent = 0 );

signals:
    void clientConnected( int );
    
public slots:
    void startServer();
};

#endif
