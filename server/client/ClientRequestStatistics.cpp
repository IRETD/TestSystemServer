#include "ClientRequestStatistics.h"


ClientRequestStatistics::ClientRequestStatistics() {

    m_RequestTimer.start();
    m_CurrentRequestCount = 0;
    m_RequestCountLimit = 100;
    m_RequestTimeSecondLimit = 60;
}


//----------------------------------------------------------------
// Устанавливаем предел по времени для отслеживания лимита по
// запросам.
//----------------------------------------------------------------
void ClientRequestStatistics::setRequestCountLimit( int requestCountLimit ) {

    m_RequestCountLimit = requestCountLimit;
}


void ClientRequestStatistics::setRequestTimeSecondLimit( int requestTimeSecondLimit ) {

    m_RequestTimeSecondLimit = requestTimeSecondLimit;

}


//----------------------------------------------------------------
// Счетчик запросов клиента
//----------------------------------------------------------------
void ClientRequestStatistics::increaseCurrentRequestCount() {

    m_CurrentRequestCount++;
    int test = m_RequestTimer.elapsed();
    int passedSecondTime = m_RequestTimer.elapsed() / 1000;
    if ( passedSecondTime > m_RequestTimeSecondLimit ) {
        m_RequestTimer.restart();
        m_CurrentRequestCount = 0;
    }
}


bool ClientRequestStatistics::isRequestCountLimitExceeded() {

    return m_CurrentRequestCount > m_RequestCountLimit;
}
