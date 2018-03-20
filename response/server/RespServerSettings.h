#ifndef RESPSERVERSETTINGS_H
#define RESPSERVERSETTINGS_H

#include <response/server/ResponseServer.h>
#include <server/ServerSettings.h>
#include <server/service/BlackList.h>
#include <server/service/IdleList.h>

class RespServerSettings : public ResponseServer {

    BlackList m_BlackList;
    ServerSettings m_ServerSettings;
    IdleList m_IdleList;

public:
    RespServerSettings();

    void setServerSettings( const ServerSettings &settings );
    void setBlackList( const BlackList &blackList );
    void setIdleList( const IdleList &idleList );

    BlackList getBlackList() const;
    ServerSettings getServerSettings() const;
    IdleList getIdleList() const;
};

#endif // RESPSERVERSETTINGS_H
