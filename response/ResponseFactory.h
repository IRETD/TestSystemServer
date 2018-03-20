#ifndef RESPONSEFACTORY_H
#define RESPONSEFACTORY_H

#include <response/client/ResponseClient.h>
#include <response/server/ResponseServer.h>
#include <response/client/ResponseClientName.h>

class ResponseFactory
{
public:
    ResponseFactory();

    virtual ResponseServer *createServerRequest( const ResponseServerType &typeResponse );
    virtual ResponseClient *createClientRequest( const ResponseClientType &typeResponse );
};

#endif // RESPONSEFACTORY_H
