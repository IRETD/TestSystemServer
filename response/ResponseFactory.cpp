#include "ResponseFactory.h"
#include <response/client/RespAuth.h>
#include <response/client/RespCode.h>


ResponseFactory::ResponseFactory() {
}


ResponseServer *ResponseFactory::createServerRequest( const ResponseServerType &typeResponse ) {


}

// Похоже это ОЧЕНЬ старый код.
// Осмотрено в 21.04.2016

ResponseClient *ResponseFactory::createClientRequest( const ResponseClientType &typeResponse ) {

    ResponseClient *pResponse = NULL;

    switch( typeResponse ) {

        case ResponseClientType::AUTHORIZATION :
            //pResponse = new RespAuth();
            break;

        case ResponseClientType::CODE :
            //pResponse = new RespCode();
            break;
    }

    return pResponse;
}
