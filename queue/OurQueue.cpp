#include "queue/OurQueue.h"
#include <QCoreApplication>
#include <QTest>
#include <windows.h>

OurQueue::OurQueue( QObject *parent ) : QObject( parent ) {

}


void OurQueue::setThreadFreeStatus( const int &idThread ) {

    m_ReqExecArr[ idThread ] -> setStatus( true );
}

//----------------------------------------------------------------
// Поиск свободного потока.
//----------------------------------------------------------------
int OurQueue::findFreeThread() {

    //состояние очередей
    bool lowQueueStatus = !m_ReqLowQueue.isEmpty();
    bool highQueueStatus = !m_ReqHighQueue.isEmpty();

    for ( int i = 0; i < m_ReqExecArr.size(); i++ ) {
        if ( m_ReqExecArr[ i ] -> getStatus() ) {

            if ( m_ReqExecArr[ i ] -> getPriority() ) {

                if ( highQueueStatus ) {
                    m_ReqExecArr[ i ] -> setStatus( false );
                    return i;
                }

            }
            else {
            //ОБРАТИ ВНИМАНИЕ!!!!!!!!!!!!!!!!!!!!!!!
                if ( lowQueueStatus ) {
                    m_ReqExecArr[ i ] -> setStatus( false );
                    return i;
                }
            }
        }

    }

    return NO_FREE_THREAD;
}


//----------------------------------------------------------------
// СЛОТ
// Отправляем запрос на исполнение в свободный поток.
// Нужно учесть, что свободных потоков может и не быть на текущий момент,
// либо же попросту очереди запросов пусты :)
//----------------------------------------------------------------
void OurQueue::sendAvailableRequestToThread() {

    int id = findFreeThread();

    if ( id != NO_FREE_THREAD && id != QUEUES_ARE_EMPTY ) {
        m_pThreadEvent = new OurEvent();

        if ( m_ReqExecArr[ id ] -> getPriority() ) {
            m_pThreadEvent -> setRequest( m_ReqHighQueue.dequeue() );
        }
        else {
            m_pThreadEvent -> setRequest( m_ReqLowQueue.dequeue() );
        }


        qDebug() << "OurQueue postEvent " << GetThreadId( GetCurrentThread() );
        QCoreApplication::postEvent( m_ReqExecArr[ id ], m_pThreadEvent );
    }
}


//----------------------------------------------------------------
// СЛОТ
// Поместить запрос в соответствующую очередь в зависимости
// от приоритета этого запроса.
//
// Пока что учитываем 2 приоритета - низкий и высокий
//----------------------------------------------------------------
void OurQueue::putRequestInQueue( Request* pRequest ) {

    if ( pRequest -> getPriority() ) {
        m_ReqHighQueue.enqueue( pRequest );
    }
    else {
        m_ReqLowQueue.enqueue( pRequest );
    }
}


void OurQueue::addRequestExecute( RequestExecute *const pRequestExecute ) {

    m_ReqExecArr.push_back( pRequestExecute );
}


RequestExecute *OurQueue::getRequestExecute( const int &index ) {

    return m_ReqExecArr[ index ];
}
