#ifndef TEACHERREQHISTORY_H
#define TEACHERREQHISTORY_H

#include <request/client/ReqHistory.h>
#include <TypeDefinitions/BaseTypeDefinitions.h>

class TeacherReqHistory : public ReqHistory {


    // Cписок студентов, для которых необходимо получить историю.
    QList < ID_STUDENT > m_IdStudentList;

    QList < ID_STUDENT > getIdStudentListFromGroupList( QList < Group > groupList );
public:
    TeacherReqHistory();

    void readStream( QDataStream &stream );
    ResponseClient *doRequest( const OurDataBase &db,
                               OurQueryInfo &queryInfo );
};

#endif
