//************************************************************************
// Класс хранения активности клиента на сервера:
// - его буффер, который хранит всю присланную информация на текущий момент
// - количество присланных запросов
// и т.д.
//
//************************************************************************


#ifndef CLIENTREQUEST_H
#define CLIENTREQUEST_H

#include <QByteArray>
#include <QString>
#include <QObject>
#include <QTime>

class ClientRequestStatistics {

    int m_RequestCountLimit;
    int m_RequestTimeSecondLimit;
    int m_CurrentRequestCount;
    QTime m_RequestTimer;

public:
    ClientRequestStatistics();

    void increaseCurrentRequestCount();
    void setRequestCountLimit( int requestCountLimit );
    void setRequestTimeSecondLimit( int requestTimeSecondLimit );
    int getCurrentRequestCount();
    bool isRequestCountLimitExceeded();
};

#endif
