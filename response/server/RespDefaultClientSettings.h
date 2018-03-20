#ifndef RESPDEFAULTCLIENTSETTINGS_H
#define RESPDEFAULTCLIENTSETTINGS_H

#include <response/server/ResponseServer.h>

class RespDefaultClientSettings : public ResponseServer {

    int m_ClientBufferSize;
    int m_RequstCountLimit;
    int m_RequestTimeLimit;

public:
    RespDefaultClientSettings();
};

#endif
