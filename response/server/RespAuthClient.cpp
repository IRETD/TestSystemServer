#include "RespAuthClient.h"


RespAuthClient::RespAuthClient() {
}


void RespAuthClient::setOldId( const int &oldId ) {

    m_OldId = oldId;
}


void RespAuthClient::setNewId( const int &newId ) {

    m_NewId = newId;
}


int RespAuthClient::getOldId() {

    return m_OldId;
}


int RespAuthClient::getNewId() {

    return m_NewId;
}
