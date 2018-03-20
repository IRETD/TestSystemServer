#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class Server : public QTcpServer {
    Q_OBJECT


private:
    QTcpServer *m_pServer;

protected:
    void incomingConnection( qintptr handle );

signals:
    void clientIsConnected( int );

public:
    Server( QObject *pObjct = 0 );

    bool createServer( const int &port = 1500 );
    bool closeServer();

    QTcpServer* getServer();
};

#endif
