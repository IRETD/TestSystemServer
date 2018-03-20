#ifndef RESPAUTHCLIENT_H
#define RESPAUTHCLIENT_H

#include <response/server/ResponseServer.h>


class RespAuthClient : ResponseServer {

    int m_OldId;
    int m_NewId;

public:
    RespAuthClient();

    void setOldId( const int &oldId );
    void setNewId( const int &newId );
    int getOldId();
    int getNewId();
};

#endif // RESPAUTHCLIENT_H
