#ifndef REQUESTFACTORY_H
#define REQUESTFACTORY_H

#include <request/client/RequestClient.h>
#include <request/server/RequestServer.h>
#include <request/client/RequestClientName.h>
#include <request/server/RequestServerName.h>

class RequestFactory {

public:
    RequestFactory();

    virtual RequestClient *createClientRequest( const RequestClientType &typeRequest,
                                                const RequestSender &requestSender ) const;
    virtual RequestServer *createServerRequest( const RequestServerType &typeRequest ) const;
};

#endif
