#ifndef TEACHERRESPHISTORY_H
#define TEACHERRESPHISTORY_H

#include <response/client/ResponseClient.h>
#include "struct/StudentRespHistory.h"

class TeacherRespHistory : public ResponseClient {

    QList < StudentRespHistory > m_StudentRespHistoryList;

public:
    TeacherRespHistory( ResponseReciever responseReciever );

    void addStudentHistory( ID_STUDENT idStudent,
                            QList < History > historyList,
                            QList < AboutHistory > aboutHistoryList );

    void writeInStreamBuffer();
};

#endif // TEACHERRESPHISTORY_H
