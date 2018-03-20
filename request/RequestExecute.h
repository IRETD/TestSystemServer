//************************************************************************
// "Поток" отвечающий за исполнение запроса
//************************************************************************

#ifndef REQUESTEXECUTE_H
#define REQUESTEXECUTE_H

#include <QThread>
#include <request/client/RequestClient.h>
#include <request/server/RequestServer.h>
#include <response/client/ResponseClient.h>
#include <database/OurDataBase.h>


class RequestExecute : public QObject {

    Q_OBJECT

    int m_Index;
    OurDataBase m_Db;
    bool m_Priority;
    bool m_Status;

    void customEvent( QEvent* );
    void processRequest( RequestClient *pRequest );
    void processRequest(RequestServer *pRequest );

public slots:
    void connectToDatabase();

public:
    RequestExecute( const int &index, QObject *pObjct = 0 );

    void setPriority( const bool &priority );
    bool getPriority();
    void setStatus( const bool &status );
    bool getStatus();

signals:
    void threadFree( int );
    void sendResponseClientToServer( ResponseClient* );
    void sendResponseServerToServer( ResponseServer* );
    void databaseNotAvailable();
    void sendRequestToQueue( Request* );
    void getLastRequestFromQueue();

};

#endif
