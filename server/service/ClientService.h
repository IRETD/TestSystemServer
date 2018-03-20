/************************************************************************
 Класс отвечающий за все действия по обслуживанию клиента.

************************************************************************/

#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H

#include <QObject>
#include <QQueue>
#include <QTcpSocket>
#include <QHash>
#include <response/client/ResponseClient.h>
#include <response/server/ResponseServer.h>
#include <server/service/StreamReader.h>
#include <request/RequestFactory.h>
#include <server/service/BlackList.h>
#include <server/service/IdleList.h>
#include <server/client/Client.h>
#include <server/ServerSettings.h>
#include <server/service/IdCreator.h>
#include <response/ResponseFactory.h>
#include <request/server/RequestServerName.h>
#include <response/server/RespServerSettings.h>
#include <MacroDefinitions/CilentType.h>


class ClientService : public QObject {

    Q_OBJECT

// этот модификатор доступа только для теста ClientServiceSubclass!
// сменить потом на private
protected:

    enum {

        SOCKET_WRITE_ERROR = -1,

        INPUT_REQUEST_COMPLETE = 0,
        INPUT_REQUEST_UNEXPECTED = -1,
        INPUT_REQUEST_ERROR = -2
    };

    //храним всех клиентов
    QHash < QTcpSocket*,
            Client > m_ClientTable;

    //черный список клиентов
    BlackList m_BlackList;

    //следим за клиентами в "простое"
    IdleList m_IdleList;

    RequestFactory m_RequestFactory;
    ResponseFactory m_ResponseFactory;

    //класс чтения запросов от клиента
    StreamReader m_StreamReader;

    //настройки сервера
    ServerSettings m_ServerSettings;

    //генерируем ИНДИВИДУАЛЬНЫЙ номер для каждого из клиентов
    IdCreator m_IdCreator;

    QTcpSocket *getClientSocketByClientId( const int &clientId,
                                           ClientType clientType );
    virtual void disconnectClient( QTcpSocket *const pClientSocket );
    void sendRequestToQueue( Request *pRequest );
    void sendResponseToArchive(ResponseClient *pResponse );
    void getResponseFromArchiveForUser( const int &idUser );
    void setServerSettings( RespServerSettings *pRespServerSettings );
    RequestServer *prepareServerRequest( const RequestServerType &requestType );
    void prepareClientRequest( RequestClient *pRequestClient );

    //меняем номер клиента - если присоединился существующий клиент, необходимо сменить его номер
    void changeClientId( ClientType oldClientType,
                         ClientType newClientType,
                         const int &oldId,
                         const int &newId );
    void processResponseClient(ResponseClient *pResponse );
    int processInputClientData( RequestClient *pRequestClient,
                                Client &client );

private slots:
    void clientIsIdle( int idClient );

public:
    ClientService( QObject *pObjct = 0 );
    ClientService( const RequestFactory &factory );

    void setStreamReader( const StreamReader &streamReader );
    void setRequestFactory( const RequestFactory requestFactory );
    void setResponseFactory( const ResponseFactory ResponseFactory );
    void loadService();

signals:
    void sendRequest( Request* );
    void sendLastRequestFromQueueToThread();
    void serviceIsLoaded();


public slots:
    void clientConnected( int socketDescriptor );
    void readClient();
    void sendResponseToClient( ResponseClient *pResp );
    void getServerResponse( ResponseServer *pResponse );
    void deleteClient();
};

#endif
