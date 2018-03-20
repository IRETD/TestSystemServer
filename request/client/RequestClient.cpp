#include "RequestClient.h"
#include <database/table/TableBugList.h>
#include <database/table/TableMessageCatalogForClient.h>


RequestClient::RequestClient() {

    m_RequestType = RequestType::CLIENT;
}



void RequestClient::setRequestClientType( const RequestClientType &requestClientType ) {

    m_RequestClientType = requestClientType;
}


RequestClientType RequestClient::getRequestClientType() const {

    return m_RequestClientType;
}
