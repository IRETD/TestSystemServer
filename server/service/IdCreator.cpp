#include "IdCreator.h"


IdCreator::IdCreator( QObject *pObjct ) : QObject( pObjct ) {

    m_IdCounterForNotAuthorized = 0;
}


int IdCreator::getIdForNotAuthorizedClient() {

    int idClient = CLIENT_IS_NOT_AUTH_ID;

    if ( !m_QueueId.isEmpty() ) {
        idClient = m_QueueId.dequeue();
    }
    else {
        m_IdCounterForNotAuthorized--;
        idClient = m_IdCounterForNotAuthorized;
    }

    return idClient;
}


void IdCreator::addId(int id) {

    m_QueueId.enqueue( id );
}
