#ifndef REQSERVERSETTINGS_H
#define REQSERVERSETTINGS_H

#include <request/server/RequestServer.h>
#include <server/service/BlackList.h>
#include <server/ServerSettings.h>

enum {

    DEFAULT_SETTING = 1
};

class ReqServerSettings : public RequestServer {

    BlackList m_BlackList;
    ServerSettings m_ServerSettings;

public:
    ReqServerSettings();

    ResponseServer *doRequest( const OurDataBase &db, OurQueryInfo &queryInfo );
};

#endif // REQSERVERSETTINGS_H
