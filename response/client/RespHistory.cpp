#include "RespHistory.h"
#include <MacroDefinitions/Data/Test/TestResult.h>
#include <MacroDefinitions/Data/Test/StepType.h>

RespHistory::RespHistory( ResponseReciever responseReciever ) : ResponseClient( responseReciever ) {
}


void RespHistory::addHistoryList( const QList < History > &historyList ) {

    m_HistoryList.append( historyList );
}


void RespHistory::addAboutHistoryList( const QList < AboutHistory > &aboutHistoryList ) {

    m_AboutHistoryList.append( aboutHistoryList );
}


void RespHistory::addHistory( const History &history ) {

    m_HistoryList.append( history );
}


void RespHistory::addAboutHistory( const AboutHistory &aboutHistory ) {

    m_AboutHistoryList.append( aboutHistory );
}


void RespHistory::writeInStreamBuffer() {

    clearStream();

    streamProlog( ResponseClientType::HISTORY );

    writeListDataInStream( m_HistoryList );
    writeListDataInStream( m_AboutHistoryList );

    streamEpilog();
}


QList < History > RespHistory::getHistoryList() {

    return m_HistoryList;
}


QList < AboutHistory > RespHistory::getAboutHistoryList() {

    return m_AboutHistoryList;
}

