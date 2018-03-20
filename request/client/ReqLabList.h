#ifndef REQLABLIST_H
#define REQLABLIST_H

#include <request/client/RequestClient.h>
#include <response/client/RespDisciplineTask.h>
#include <TypeDefinitions/BaseTypeDefinitions.h>

class ReqLabList : public RequestClient {

protected:
    //Возаращает список id дисциплин, для которых и составил список лабораторных
    QList< ID_DISCIPLINE > getLabList( const OurDataBase &db,
                                       OurQueryInfo &queryInfo,
                                       RespDisciplineTask *respDisciplineTask,
                                       QList < ID_LAB > idLabList,
                                       QList<ID_USER_LAB> idUserLabList = QList < ID_USER_LAB > () );

    void getDisciplineList( const OurDataBase &db,
                            OurQueryInfo &queryInfo,
                            RespDisciplineTask *respDisciplineTask,
                            /// по умолчанию - пустой список
                            QList< ID_DISCIPLINE > idDisciplineList );

    void doReqLabList();

public:
    ReqLabList();

     ResponseClient *doRequest( const OurDataBase &db,
                                OurQueryInfo &queryInfo );
};

#endif // REQLABLIST_H
