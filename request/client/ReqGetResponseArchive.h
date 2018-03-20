#ifndef REQGETRESPONSEARCHIVE_H
#define REQGETRESPONSEARCHIVE_H

#include <request/client/RequestClient.h>
#include <response/client/ResponseClient.h>
#include <response/ResponseFactory.h>
#include <database/OurQueryInfo.h>

class ReqGetResponseArchive : public RequestClient {

    ResponseFactory m_ResponseFactory;

public:
    ReqGetResponseArchive( const ResponseFactory &factory );

    ResponseClient *doRequest( const OurDataBase &db, OurQueryInfo &queryInfo );
    void setResponseClientFactory( const ResponseFactory &factory );
};

#endif
