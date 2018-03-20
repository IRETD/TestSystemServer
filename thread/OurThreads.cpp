#include <thread/OurThreads.h>

OurThreads::OurThreads() {
}

void OurThreads::addObject( QObject *pObjct ) {

    QThread *pThread = new QThread();
    m_ThreadList[ pObjct ] = pThread;
    pObjct -> moveToThread( pThread );
}

void OurThreads::startThreads() {

    QHash < QObject*, QThread* >::iterator it = m_ThreadList.begin();
    QHash < QObject*, QThread* >::iterator end = m_ThreadList.end();

    for ( ; it != end; it++ )
        if ( !it.value() -> isRunning() )
            it.value() -> start();
}

QThread *OurThreads::getThread( QObject *pObjct ) {
    QHash < QObject*, QThread* >::iterator it = m_ThreadList.begin();
    QHash < QObject*, QThread* >::iterator end = m_ThreadList.end();
    for (; it != end; ++it)
        if (it.key() == pObjct)
            return it.value();

    return NULL;
}

void OurThreads::startThread( QObject *pObjct ) {
    QHash < QObject*, QThread* >::iterator it = m_ThreadList.begin();
    QHash < QObject*, QThread* >::iterator end = m_ThreadList.end();
    for ( ; it != end; it++ )
        if ( it.key() == pObjct )
            if ( !it.value() -> isRunning() ) {
                it.value() -> start();
                break;
            }
}
