#ifndef REQUESTSERVER_H
#define REQUESTSERVER_H

#include <request/Request.h>
#include <response/server/ResponseServer.h>
#include <database/OurQueryInfo.h>


class RequestServer : public Request {

public:
    RequestServer();

    virtual ResponseServer *doRequest( const OurDataBase &db, OurQueryInfo &queryInfo ) = 0;
};

#endif
