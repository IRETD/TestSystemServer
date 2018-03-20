#ifndef STUDENTRESPHISTORY_H
#define STUDENTRESPHISTORY_H

#include <../../TestSystem/TestSystem/TypeDefinitions/BaseTypeDefinitions.h>
#include <QByteArray>
#include <QDataStream>
#ifdef IT_IS_SERVER
    #include <data/history/History.h>
    #include <data/history/AboutHistory.h>
#else
    #include "../../TestSystem/TestSystem/data/history/History.h"
    #include "../../TestSystem/TestSystem/data/history/AboutHistory.h"
#endif



// Хранит ВСЮ историю о студенте.

class StudentRespHistory {

    ID_STUDENT m_IdStudent;

    // История сдачи студентом в БАЙТАХ.
    QList < History > m_HistoryList;
    QList < AboutHistory > m_AboutHistoryList;

public:
    StudentRespHistory();

    StudentRespHistory( ID_STUDENT idStudent,
                        QList < History > historyList,
                        QList < AboutHistory > aboutHistoryList ) {

        m_IdStudent = idStudent;
        m_HistoryList = historyList;
        m_AboutHistoryList = aboutHistoryList;
    }

    /*
    friend QDataStream& operator >> ( QDataStream &stream,
                                      StudentRespHistory &value );
                                      */
    friend QDataStream& operator >> ( QDataStream &stream,
                                      StudentRespHistory &value );

    friend QDataStream& operator << ( QDataStream &stream,
                                      StudentRespHistory &value );
    /*
    friend QDataStream& operator << ( QDataStream &stream,
                                      StudentRespHistory const value );
    */

    void setIdStudent( ID_STUDENT idStudent );

    template < class T >
    void addHistory( T& );
    template < class T >
    void addAboutHistory( T &aboutHistory );

    ID_STUDENT getIdStudent();
    QList < History > getHistoryList();
    QList < AboutHistory > getAboutHistoryList();
};

#endif // STUDENTRESPHISTORY_H
