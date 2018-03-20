#ifndef REQHISTORY_H
#define REQHISTORY_H

#include <request/client/RequestClient.h>
#include <request/teacher/TeacherReqLabList.h>

class ReqHistory : public RequestClient {


    QList < ID_USER_LAB > m_IdUserLabFilterList;

public:
    ReqHistory();

    ResponseClient *doRequest(const OurDataBase &db, OurQueryInfo &queryInfo);
    void setIdUserLabFilter( QList < ID_USER_LAB > idUserLabFilterList );
};

#endif // REQHISTORY_H
