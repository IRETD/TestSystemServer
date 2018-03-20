#ifndef REQPUTRESPONSEARCHIVE_H
#define REQPUTRESPONSEARCHIVE_H

#include <request/server/RequestServer.h>
#include <response/server/ResponseServer.h>
#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>


class ReqPutResponseArchive : public RequestServer {

    ResponseClient *m_pResponse;

public:
    ReqPutResponseArchive();

    ResponseServer *doRequest( const OurDataBase &db, OurQueryInfo &queryInfo );

    void setResponse(ResponseClient *pResponse );
};

#endif
