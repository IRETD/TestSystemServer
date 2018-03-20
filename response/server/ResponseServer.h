#ifndef RESPONSESERVER_H
#define RESPONSESERVER_H

#include <QString>
#include <response/server/ResponseServerName.h>

class ResponseServer {

protected:
    ResponseServerType m_Type;

public:
    ResponseServer();

    void setType( ResponseServerType type );
    ResponseServerType getType();
};

#endif
