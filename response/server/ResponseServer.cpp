#include "ResponseServer.h"


ResponseServer::ResponseServer() {
}


void ResponseServer::setType( ResponseServerType type ) {

    m_Type = type;
}


ResponseServerType ResponseServer::getType() {

    return m_Type;
}
