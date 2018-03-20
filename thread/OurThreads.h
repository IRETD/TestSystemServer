#ifndef OURTHREADS_H
#define OURTHREADS_H

#include <QVector>
#include <QThread>
#include <QHash>

class OurThreads {

    QHash < QObject*, QThread* > m_ThreadList;
    int m_Count;

public:
    OurThreads();

    void addObject( QObject *const pObjct );

    QThread* getThread( QObject *const pObjct );
    void startThread( QObject *const pOjbct );
    void startThreads();
};

#endif
