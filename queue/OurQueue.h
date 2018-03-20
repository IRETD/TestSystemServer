#ifndef OURQUEUE_H
#define OURQUEUE_H

#include <request/client/RequestClient.h>
#include <QQueue>
#include <QThread>
#include <thread/OurThreads.h>
#include <event/OurEvent.h>
#include <request/RequestExecute.h>
#include <QVector>
#include <QHash>

class OurQueue : public QObject {

    Q_OBJECT

    enum {
        NO_FREE_THREAD = -1,
        QUEUES_ARE_EMPTY = -2
    };

    QVector < RequestExecute* > m_ReqExecArr;
    QQueue < Request* > m_ReqHighQueue;
    QQueue < Request* > m_ReqLowQueue;
    OurEvent *m_pThreadEvent;

    int findFreeThread();

public:

    OurQueue( QObject *pObjct = 0 );

    void addRequestExecute( RequestExecute *const pRequestExecute );
    RequestExecute *getRequestExecute( const int &index );

public slots:

    void setThreadFreeStatus( const int &idThread );
    void putRequestInQueue(Request *pRequest );
    void sendAvailableRequestToThread();
};

#endif // OURQUEUE_H
