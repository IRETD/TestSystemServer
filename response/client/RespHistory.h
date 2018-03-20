#ifndef RESPHISTORY_H
#define RESPHISTORY_H

#include <data/history/History.h>
#include <data/history/AboutHistory.h>
#include <response/client/ResponseClient.h>


/*
enum TypeData {

    HISTORY_TEST = 1,
    ABOUT_HISTORY_TEST = 2
};
*/


class RespHistory : public ResponseClient {

    QList < History > m_HistoryList;
    QList < AboutHistory > m_AboutHistoryList;

public:
    RespHistory( ResponseReciever responseReciever );

    void addHistoryList( const QList < History > &historyList );
    void addAboutHistoryList( const QList < AboutHistory > &aboutHistoryList );

    void addHistory( const History &history );
    void addAboutHistory( const AboutHistory &aboutHistory );

    QList < History > getHistoryList();
    QList < AboutHistory > getAboutHistoryList();

    void writeInStreamBuffer();
};


#endif // RESPHISTORY_H
