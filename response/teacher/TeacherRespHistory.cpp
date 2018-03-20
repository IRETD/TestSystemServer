#include "TeacherRespHistory.h"


TeacherRespHistory::TeacherRespHistory(ResponseReciever responseReciever) : ResponseClient( responseReciever ) {
}


void TeacherRespHistory::addStudentHistory( ID_STUDENT idStudent,
                                            QList < History > historyList,
                                            QList < AboutHistory > aboutHistoryList ) {

    m_StudentRespHistoryList.push_back( StudentRespHistory( idStudent,
                                                            historyList,
                                                            aboutHistoryList ) );
}


void TeacherRespHistory::writeInStreamBuffer() {

    clearStream();
    streamProlog( ResponseClientType::HISTORY );

    m_StreamBuffer << m_StudentRespHistoryList;

    prepareStream();
}
