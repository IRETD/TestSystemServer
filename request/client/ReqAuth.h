#ifndef REQAUTH_H
#define REQAUTH_H

#include <request/client/RequestClient.h>
#include <response/client/ResponseClient.h>
#include <response/client/RespAuth.h>

class ReqAuth : public RequestClient {

    enum {
        NO_SUCH_USER = QUERY_NO_DATA
    };

    QString m_Login;
    QString m_Pass;

    int doAuth( const OurDataBase &db,
                OurQueryInfo &queryInfo );

public:
    ReqAuth();

    void readStream( QDataStream &stream );

    ResponseClient *doRequest( const OurDataBase &db, OurQueryInfo &queryInfo );
};

#endif
