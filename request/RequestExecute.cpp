#include <request/RequestExecute.h>
#include <QtTest/QTest>
#include <QDebug>
#include <event/OurEvent.h>
#include <request/client/ReqAuth.h>
#include <request/RequestFactory.h>
#include <request/client/ReqCode.h>

RequestExecute::RequestExecute( const int &index, QObject *pObjct ) : QObject( pObjct ) {

    m_Index = index;
    m_Priority = true;
    m_Status = true;
}

void RequestExecute::setPriority ( const bool &priority ) {

    m_Priority = priority;
}

bool RequestExecute::getPriority() {

    return m_Priority;
}

void RequestExecute::setStatus( const bool &status ) {

    m_Status = status;
}

bool RequestExecute::getStatus() {

    return m_Status;
}

//----------------------------------------------------------------
// у каждого потока свое подключение к БД
//----------------------------------------------------------------
void RequestExecute::connectToDatabase() {

    QString login = QString::number( m_Index );
    QString password = QString::number( m_Index );

    bool resultConnection = m_Db.connectToDataBase( login, password, QString::number( m_Index ) );

    if ( resultConnection ) {
        //забираем имеющиеся запросы
        emit getLastRequestFromQueue();
    }
    else {
        emit databaseNotAvailable();
    }
}

//----------------------------------------------------------------
// Принимаем событие (запрос).
//----------------------------------------------------------------
void RequestExecute::customEvent( QEvent *pEvent ) {

    if ( static_cast < int > ( pEvent  -> type() ) == OurEvent::eventType ) {
        OurEvent *pOurEvent = static_cast < OurEvent* > (pEvent);
        if ( pOurEvent != NULL ) {
            Request *pRequest = pOurEvent -> getRequest();

            if ( pRequest -> getRequestType() == RequestType::CLIENT ) {
                RequestClient* pRequestClient = static_cast<RequestClient*>( pRequest );
                processRequest( pRequestClient );
            }

            if ( pRequest -> getRequestType() == RequestType::SERVER ) {
                RequestServer *pRequestServer = static_cast < RequestServer* > ( pRequest );
                processRequest( pRequestServer );
            }

        }

      //  processRequestqobject_cast<OurEvent*> (pEvent) -> getRequest() );
    }
}

//----------------------------------------------------------------
// Исполнение запроса и отсылка сигнала о результатах исполнения
// запроса.
//----------------------------------------------------------------
void RequestExecute::processRequest(RequestClient *pRequest ) {

    OurQueryInfo queryInfo;

    if ( pRequest -> getRequestClientType() == RequestClientType::CODE ) {
        connect( static_cast < ReqCode* > ( pRequest ),
                 &ReqCode::sendResponseClient,
                 this,
                 &RequestExecute::sendResponseClientToServer );
    }

    ResponseClient *pResponseClient ( pRequest -> doRequest( m_Db,
                                                             queryInfo ) );

    emit threadFree( m_Index );

    if ( queryInfo.isConnectionError() ) {
        emit sendResponseClientToServer( pResponseClient );
        emit sendRequestToQueue( pRequest );
        emit databaseNotAvailable();
    }
    else {

        if ( pResponseClient != NULL ) {
            //А КАК ТУТ ТО РАБОТАЛО??!!! ЕСЛИ Я ДАЖЕ НЕ ВОЗВРАЩАЛ УКАЗАТЕЛЬ!?
            pResponseClient -> setIdClient( pRequest -> getIdClient() );
            pResponseClient -> writeInStreamBuffer();
            emit sendResponseClientToServer( pResponseClient );
        }

        emit getLastRequestFromQueue();
    }
}


void RequestExecute::processRequest( RequestServer *pRequest ) {

    OurQueryInfo queryInfo;

    ResponseServer *pResponseServer( pRequest -> doRequest( m_Db, queryInfo ) );

    emit threadFree( m_Index );

    if ( queryInfo.isConnectionError() ) {
        emit sendRequestToQueue( pRequest );
        emit databaseNotAvailable();
    }
    else {

        if ( pResponseServer != NULL ) {
            emit sendResponseServerToServer( pResponseServer );
        }

        emit getLastRequestFromQueue();
    }
}

