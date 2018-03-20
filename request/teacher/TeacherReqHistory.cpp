#include "TeacherReqHistory.h"
#include "TeacherReqLabList.h"
#include <response/teacher/TeacherRespDisciplineTask.h>
#include <request/client/ReqHistory.h>
#include <response/client/RespHistory.h>
#include <response/teacher/TeacherRespHistory.h>
#include <QSet>

QList < ID_STUDENT > TeacherReqHistory::getIdStudentListFromGroupList( QList < Group > groupList ) {

    quint32 count = groupList.size();
    QSet < ID_STUDENT > idStudentSet;
    for ( int i = 0;
          i < count;
          i++ ) {

        Group group = groupList[ i ];
        QList < Student > &studentList = group.getStudentList();
        quint32 studentCount = studentList.size();
        for ( int j = 0;
              j < studentCount;
              j++ ) {

            Student &student = studentList[ j ];
            idStudentSet.insert( student.getIdStudent() );
        }

    }

    return idStudentSet.toList();
}

TeacherReqHistory::TeacherReqHistory() {

}


void TeacherReqHistory::readStream( QDataStream &stream ) {

    // Читаем список студентов, для которых необходимо получить историю
    stream >> m_IdStudentList;
}


ResponseClient *TeacherReqHistory::doRequest( const OurDataBase &db,
                                              OurQueryInfo &queryInfo ) {

    TeacherRespHistory *pTeacherRespHistory = nullptr;
    // Если список студентов ПУСТ.
    // Значит поучаем ВСЕХ студентов, которые закреплены за преподом.

    if ( m_IdStudentList.empty() ) {

        QScopedPointer < TeacherReqLabList > pReqLabList( new TeacherReqLabList );
        // устанавливаем id преподавателя.
        pReqLabList.data() -> setIdClient( m_IdClient );
        TeacherRespDisciplineTask *pResp = static_cast < TeacherRespDisciplineTask* > ( pReqLabList.data() -> doRequest( db,
                                                                                                                         queryInfo ) );
        QList < Group > groupList = pResp -> getGroupList();
        m_IdStudentList = getIdStudentListFromGroupList( groupList );

        // Пока что так удаляем =(
        delete pResp;
    }

    // В этой точке мы имеем список студентов (их айдишники),
    // по которым нам НУЖНА история.
    // Формируем истории.

    // на будущее.
    // наверняка можно СРАЗУ забирать из базы МАССИВ данных
    // по множеству студентов.
    quint32 count = m_IdStudentList.size();

    // Если есть какие то студенты - выделяем память под ответ!
    // Ведь будем туда писать истории студентов :)
    if ( count > 0 ) {

        pTeacherRespHistory = new TeacherRespHistory( static_cast < ResponseReciever > ( m_RequestSender ) );
    }

    for ( int i = 0;
          i < count;
          i++ ) {

        ID_STUDENT idStudent = m_IdStudentList[ i ];
        QScopedPointer < ReqHistory > pReqHistory( new ReqHistory );
        pReqHistory.data() -> setIdClient( idStudent );
        RespHistory *pRespHistory = static_cast < RespHistory* > ( pReqHistory.data() -> doRequest( db,
                                                                                                    queryInfo ) );

        // Пишем историю в буфер!
        pRespHistory -> writeInStreamBuffer();
        // указываем id студента и кидаем весь БУФЕР из ответа по его истории.
        pTeacherRespHistory -> addStudentHistory( idStudent,
                                                  pRespHistory -> getHistoryList(),
                                                  pRespHistory -> getAboutHistoryList() );

        // Опять этот delete :(
        // Надо переходить на УМНЫЕ указатели.
        delete pRespHistory;
    }

    return pTeacherRespHistory;
}
