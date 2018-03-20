#include "ClientService.h"
#include <QTest>
#include <QHostAddress>
#include <request/client/RequestClientName.h>
#include <request/client/ReqGetResponseArchive.h>
#include <request/server/ReqPutResponseArchive.h>
#include <response/server/RespServerSettings.h>
#include <response/client/RespAuth.h>
#include <request/client/ReqCode.h>
#include <response/client/RespLeave.h>
#include <server/service/RequestReadInfo.h>
#include <windows.h>
#include <memory>
#include <QMetaType>
#include <QSharedPointer>


ClientService::ClientService( QObject *pObjct /*= 0*/ ) : QObject( pObjct ), m_IdleList( this ),
    m_BlackList( this ), m_IdCreator( this ) {

//    RequestServer *pRequestServer = prepareServerRequest( RequestServerType::SERVER_SETTINGS );
//    if ( pRequestServer != NULL ) {
//        sendRequestToQueue( pRequestServer );
//    }

    connect( &m_IdleList,
             &IdleList::clientIsIdle,
             this,
             &ClientService::clientIsIdle );
}


ClientService::ClientService( const RequestFactory &factory ) {

    m_RequestFactory = factory;
}


void ClientService::loadService() {

    sendRequestToQueue( prepareServerRequest( RequestServerType::SERVER_SETTINGS ) );
}


void ClientService::clientConnected( int socketDescriptor ) {

    QTcpSocket *pClientSocket = new QTcpSocket( this );
    if ( pClientSocket -> setSocketDescriptor( socketDescriptor ) ) {
        QString peerAddress =  pClientSocket -> peerAddress().toString();
        if ( !m_BlackList.contain( peerAddress ) ) {

            qDebug() << "Client was connected!";

            int requestCountLimit = m_ServerSettings.getRequestCountLimit();
            int requestTimeLimit = m_ServerSettings.getRequestTimeLimit();
            int clientBufferKilobyteMaxSize = m_ServerSettings.getClientBufferKilobyteMaxSize();

            Client connectedClient( clientBufferKilobyteMaxSize, requestCountLimit, requestTimeLimit );

            int idClient = m_IdCreator.getIdForNotAuthorizedClient();

            connectedClient.setIdClient( idClient );
            m_ClientTable[ pClientSocket ] = connectedClient;
            m_IdleList.addClient( idClient );

            connect( pClientSocket, SIGNAL( readyRead() ), SLOT( readClient() ) );
            connect( pClientSocket, SIGNAL( disconnected() ), SLOT( deleteClient() ) );
        }
    }
}


void ClientService::readClient() {

    QTcpSocket *pClientSocket = ( QTcpSocket* ) sender();

    Client client = m_ClientTable[ pClientSocket ];

    client.addInClientBuffer( pClientSocket -> readAll() );

    bool clientBufferIsNotEmpty = !client.getClientBuffer().isEmpty();

    do {

        StreamReader reader;
        RequestReadInfo readInfo;
        RequestClient *pRequestClient = reader.readStream( client,
                                                         m_RequestFactory,
                                                         readInfo );

        if ( readInfo.getReadStatus() == ReadStatus::INPUT_DATA_ARE_INCOMPLETE ) {
            break;
        }

        if ( readInfo.getReadStatus() == ReadStatus::INPUT_DATA_ARE_UNEXPECTED ) {

            m_BlackList.addPeerAddress( pClientSocket -> peerAddress().toString() );

         //   qDebug() << "ReadStatus::INPUT_DATA_ARE_UNEXPECTED";

            disconnectClient( pClientSocket );
            break;
        }

        if ( readInfo.getReadStatus() == ReadStatus::INPUT_DATA_ARE_COMPLETE ) {

            int result = processInputClientData( pRequestClient,
                                                 client );

            if ( result == INPUT_REQUEST_UNEXPECTED ) {
                ////BLACKLIST
                //m_BlackList.addPeerAddress( pClientSocket -> peerAddress().toString() );
                qDebug() << "INPUT_REQUEST_UNEXPECTED";
                disconnectClient( pClientSocket );
                break;
            }

            client.getRequestStatistics().increaseCurrentRequestCount();
            m_IdleList.removeClient( client.getIdClient() );
        }
        clientBufferIsNotEmpty = !client.getClientBuffer().isEmpty();
    }
    while ( clientBufferIsNotEmpty );
}


//Отправляем клиенту результат
void ClientService::sendResponseToClient( ResponseClient *pResponse ) {

    //в ответе известен id нужного нам клиента
    int clientId = pResponse -> getIdClient();

    QTcpSocket *pClientSocket = getClientSocketByClientId( clientId,
                                                           static_cast < ClientType > ( pResponse -> getResponseReciever() ) );

    if ( pClientSocket != NULL ) {

        //предварительно обрабатываем ответ для клиента
        processResponseClient( pResponse );

        QByteArray responseBuffer = pResponse -> getBuffer();
        int resultScoketWrite = pClientSocket -> write( responseBuffer );

        //Ответ мог быть так и не послан клиенту, необходимо его сохранить.
        //!
        if ( resultScoketWrite == SOCKET_WRITE_ERROR ) {
            sendResponseToArchive( pResponse );
        }

    }
    else {
        sendResponseToArchive( pResponse );
    }
}


//Обрабатываем ответ клиенту
void ClientService::processResponseClient( ResponseClient *pResponse ) {

    if ( pResponse -> getResponseClientType() == ResponseClientType::AUTHORIZATION ) {

        //если клиент удачно авторизовался в системе, нам необходимо сменить его идентификатор
        RespAuth *pRespAuth = static_cast < RespAuth* > ( pResponse );
        if ( pRespAuth -> getResult() == AuthResult::AUTHORIZATION_SUCCESS ) {
            qDebug() << "he is auth!";

            // Не забываем УКАЗЫВАТЬ ТИП клиента.
            // Изначально он должен был быть как ClientType::UNKNOWN
            changeClientId( ClientType::UNKNOWN,
                            static_cast < ClientType > ( pRespAuth -> getResponseReciever() ),
                            pRespAuth -> getIdClient(),
                            pRespAuth -> getNewId()
                            );
        }
    }

    if ( pResponse -> getResponseClientType() == ResponseClientType::LEAVE_AUTHORIZATION ) {
        qDebug() << "he is leave!";
        //меняем идентификатор клиента т.к. он покинул систему
        RespLeave *pRespLeave = static_cast < RespLeave* > ( pResponse );

        // т.к. он ПОКИДАЕТ систему, ставим ему тип клиента Unknown
        changeClientId( static_cast < ClientType > ( pRespLeave -> getResponseReciever() ),
                        ClientType::UNKNOWN,
                        pRespLeave -> getIdClient(),
                        m_IdCreator.getIdForNotAuthorizedClient() );
    }

}


//Обрабатываем входные данные клиента
//ЗАБЫЛ НАЗНАЧЕНИЕ ЭТОГО МЕТОДА
int ClientService::processInputClientData( RequestClient *pRequestClient,
                                           Client &client ) {


    // is not EMPTY
    if ( pRequestClient ) {

            ID_USER idClient = client.getIdClient();
            pRequestClient -> setIdClient( idClient );
            qDebug() << client.isAuthorized();
            if ( client.isAuthorized() ) {
                prepareClientRequest( std::move( pRequestClient ) );
                sendRequestToQueue( pRequestClient );
            }
            else {

                if ( pRequestClient -> getRequestClientType() == RequestClientType::AUTHORIZATION ) {
                    sendRequestToQueue( pRequestClient );
                }
                else {
                    return INPUT_REQUEST_UNEXPECTED;
                }

                //Очищаем буффер клиента, т.к. нас больше ничего не интересует
            //    client.clearClientBuffer();
            }
            client.setRecievedRequestSize( REQUEST_SIZE_IS_NOT_READ );
    }
    else {
        return INPUT_REQUEST_ERROR;
    }

    return INPUT_REQUEST_COMPLETE;
}


//Клиент бездействует
void ClientService::clientIsIdle( int idClient ) {

    // Простой возможен ТОЛЬКО со стороны клиента не прошедшего аутентификацию!
    // Поэтому - clienttype = UNKNOWN
    QTcpSocket *pClientSocket = getClientSocketByClientId( idClient,
                                                           ClientType::UNKNOWN );
    if ( pClientSocket != NULL ) {
        disconnectClient( pClientSocket );
    }

}



//Получаем результат выполнения запроса предназначенный ИМЕННО для сервера
void ClientService::getServerResponse( ResponseServer *pResponse ) {

    if ( pResponse -> getType() == ResponseServerType::RESPONSE_SERVER_SETTINGS ) {
        setServerSettings( static_cast < RespServerSettings* > ( pResponse ) );
    }

}


void ClientService::deleteClient() {

    qDebug() << "Client was disconnected!";

    QTcpSocket *pClientSocket = ( QTcpSocket* ) sender();

    if ( m_ClientTable.contains( pClientSocket ) ) {
        Client client = m_ClientTable[ pClientSocket ];
        if ( !client.isAuthorized() ) {
            m_IdCreator.addId( client.getIdClient() );
        }

        m_ClientTable.remove( pClientSocket );
    }
}

/// ВАЖНОЕ ЗАМЕЧАНИЕ.
/// НЕАУТЕНТИФИЦИРОВАННЫЙ ЮЗЕРЫ ИМЕЮТ ОТРИЦАТЕЛЬНЫЙ ID!!!!!!!!!!!

//Получить сокет клиента по его идентификационному номеру
QTcpSocket *ClientService::getClientSocketByClientId( const int &clientId,
                                                      ClientType clientType ) {

    // если id < 0 то это еще не АУТЕНТИФИЦИРОВАННЫЙ ЮЗЕР.
    // причисляем его к группе неизвестных.
    if ( clientId < 0 ) {

        clientType = ClientType::UNKNOWN;
    }
    auto it =  m_ClientTable.begin();
    auto itEnd =  m_ClientTable.end();

    QTcpSocket *pClientSocket = NULL;

    for ( ; it != itEnd; it++ ) {
        Client client = it.value();
        // Если ТИП клиента совпадает с искомым
        // Айдишники кстати могут и совпадать в разных группах :)
        // Самое главное отличать по clienType
        if ( client.getClientType() == clientType &&
             client.getIdClient() == clientId ) {

            pClientSocket = it.key();
            break;
        }
    }

    return pClientSocket;
}


void ClientService::disconnectClient( QTcpSocket *const pClientSocket ) {

    pClientSocket -> abort();
}


void ClientService::sendRequestToQueue(Request *pRequest ) {

    int static count = 0;
    count++;
    qDebug() << "Send Request To Queue " << GetThreadId( GetCurrentThread() ) << " " << count;

    emit sendRequest( pRequest );
    emit sendLastRequestFromQueueToThread();
}


//отправляем результат клиента в архив, т.к. его сокет недоступен в системе
void ClientService::sendResponseToArchive( ResponseClient *pResponse ) {

    ReqPutResponseArchive *pRequest( new ReqPutResponseArchive() );

    pRequest -> setResponse( pResponse );

    sendRequestToQueue( pRequest );
}


//Посмотреть архив результатов клиента
void ClientService::getResponseFromArchiveForUser( const int &idUser ) {

    ReqGetResponseArchive *pRequest(new ReqGetResponseArchive( m_ResponseFactory ));

    pRequest -> setIdClient( idUser );

    sendRequestToQueue( pRequest );
}



void ClientService::setServerSettings(RespServerSettings *pRespServerSettings ) {

    m_ServerSettings = pRespServerSettings -> getServerSettings();
    m_BlackList = pRespServerSettings -> getBlackList();
    m_IdleList = pRespServerSettings -> getIdleList();

    emit serviceIsLoaded();
}


//Подготовоить запрос от СЕРВЕРА на отправку в очередь запросов
RequestServer *ClientService::prepareServerRequest( const RequestServerType &requestType ) {

    RequestServer *pRequestServer =  m_RequestFactory.createServerRequest( requestType );

    return  pRequestServer;
}


//обрабатываем запрос клиента перед его отправкой в очередь запросов
void ClientService::prepareClientRequest(RequestClient *pRequestClient ) {

    switch( pRequestClient -> getRequestClientType() ) {
        case RequestClientType::CODE :
            static_cast < ReqCode* > ( pRequestClient ) -> setDirectoryTest( m_ServerSettings.getDirectoryTest() );
            break;
    }
}


//Меняем идентификационный номер клиента в системе.
void ClientService::changeClientId( ClientType oldClientType,
                                    ClientType newClientType,
                                    const int &oldId,
                                    const int &newId ) {

    qDebug() << "change id client";
    QTcpSocket *pClientSocket = getClientSocketByClientId( oldId,
                                                           oldClientType );

    if ( pClientSocket != NULL ) {
        m_ClientTable[ pClientSocket ].setIdClient( newId );
        // Не забываем обновлять ТИП клиента!!!
        m_ClientTable[ pClientSocket ].setClientType( newClientType );
    }
}
