#include <QCoreApplication>

#include <MacroDefinitions/Data/Test/TestResult.h>

#include <thread/OurThreads.h>

#include <server/listen/ClientListen.h>
#include <server/service/ClientService.h>

#include <QTextStream>

#include <queue/OurQueue.h>

#include <request/RequestExecute.h>

#include <code/CodeCompile.h>

#include <QList>
#include <QByteArray>

#include <database/OurDataBase.h>
#include <database/OurDataBaseKeepConnection.h>

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <QSharedPointer>
#include <QMetaType>

int main( int argc, char *argv[] ) {


    QCoreApplication a( argc, argv );

    const int THREADS_COUNT_HIGH_PRIORITY = 9;
    const int THREADS_COUNT_LOW_PRIORITY = 1;

    int i = 0;
    OurThreads threads;
    ClientService *pClientService = new ClientService;
    ClientListen *pClientListen = new ClientListen() ;
    OurQueue *ourQue = new OurQueue();
    OurDataBaseKeepConnection *dbConnection = new OurDataBaseKeepConnection();

    threads.addObject( ourQue );
    threads.addObject( dbConnection );


    for ( i = 0; i < THREADS_COUNT_LOW_PRIORITY; i++ ) {

        ourQue -> addRequestExecute( new RequestExecute( i ) );
        ourQue -> getRequestExecute( i ) -> setPriority( false );

        threads.addObject( ourQue -> getRequestExecute( i ) );

        QObject::connect( ourQue -> getRequestExecute( i ),
                          &RequestExecute::sendResponseClientToServer,
                          pClientService,
                          &ClientService::sendResponseToClient );

        QObject::connect( ourQue -> getRequestExecute( i ),
                          &RequestExecute::sendResponseServerToServer,
                          pClientService,
                          &ClientService::getServerResponse );

        QObject::connect( ourQue -> getRequestExecute( i ),
                          &RequestExecute::threadFree,
                          ourQue, &OurQueue::setThreadFreeStatus );

        QObject::connect( ourQue -> getRequestExecute( i ),
                          &RequestExecute::getLastRequestFromQueue,
                          ourQue,
                          &OurQueue::sendAvailableRequestToThread );

        QObject::connect( ourQue -> getRequestExecute( i ),
                          &RequestExecute::sendRequestToQueue,
                          ourQue,
                          &OurQueue::putRequestInQueue );

        QObject::connect( ourQue -> getRequestExecute( i ),
                          &RequestExecute::databaseNotAvailable,
                          dbConnection,
                          &OurDataBaseKeepConnection::databaseNotAvailable );

        QObject::connect( dbConnection,
                          &OurDataBaseKeepConnection::databaseAvailable,
                          ourQue -> getRequestExecute( i ),
                          &RequestExecute::connectToDatabase );
    }



    for ( ; i < THREADS_COUNT_HIGH_PRIORITY + THREADS_COUNT_LOW_PRIORITY; i++ ) {
        ourQue -> addRequestExecute( new RequestExecute( i ) );
        ourQue -> getRequestExecute( i ) -> setPriority( true );

        threads.addObject( ourQue -> getRequestExecute( i ) );

        QObject::connect( ourQue -> getRequestExecute( i ), &RequestExecute::sendResponseClientToServer,
                          pClientService, &ClientService::sendResponseToClient );

        QObject::connect( ourQue -> getRequestExecute( i ), &RequestExecute::sendResponseServerToServer,
                          pClientService, &ClientService::getServerResponse );

        QObject::connect( ourQue -> getRequestExecute( i ),  &RequestExecute::threadFree,
                          ourQue, &OurQueue::setThreadFreeStatus );

        QObject::connect( ourQue -> getRequestExecute( i ),  &RequestExecute::getLastRequestFromQueue,
                          ourQue, &OurQueue::sendAvailableRequestToThread );

        QObject::connect( ourQue -> getRequestExecute( i ),  &RequestExecute::sendRequestToQueue,
                          ourQue, &OurQueue::putRequestInQueue );

        QObject::connect( ourQue -> getRequestExecute( i ), &RequestExecute::databaseNotAvailable,
                          dbConnection, &OurDataBaseKeepConnection::databaseNotAvailable );

        QObject::connect( dbConnection, &OurDataBaseKeepConnection::databaseAvailable,
                          ourQue -> getRequestExecute( i ), &RequestExecute::connectToDatabase );
    }

    threads.addObject( pClientListen );
    threads.addObject( pClientService );

    QObject::connect( pClientService, &ClientService::serviceIsLoaded,
                      pClientListen, &ClientListen::startServer );

    QObject::connect( pClientListen, &ClientListen::clientConnected,
                      pClientService, &ClientService::clientConnected );

    QObject::connect( pClientService,
                      &ClientService::sendRequest,
                      ourQue,
                      &OurQueue::putRequestInQueue );

    QObject::connect( pClientService, &ClientService::sendLastRequestFromQueueToThread,
                      ourQue, &OurQueue::sendAvailableRequestToThread );

    for ( i = 0 ; i < THREADS_COUNT_HIGH_PRIORITY + THREADS_COUNT_LOW_PRIORITY; i++ ) {
        ourQue -> getRequestExecute( i ) -> connectToDatabase();
    }

    threads.startThreads();

    pClientService -> loadService();

    qDebug() << "Я здесь начал - " << GetThreadId( GetCurrentThread() );

//    TestExecute test;
//    test.start();

    return a.exec();
}
