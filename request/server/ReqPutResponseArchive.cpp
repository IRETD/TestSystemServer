#include "ReqPutResponseArchive.h"
#include <database/table/TableResponseArchive.h>

ReqPutResponseArchive::ReqPutResponseArchive() : m_pResponse( nullptr ) {

}


ResponseServer *ReqPutResponseArchive::doRequest( const OurDataBase &db,
                                                  OurQueryInfo &queryInfo ) {

    TableResponseArchive table( db );
    table.insert( m_pResponse -> getIdClient(),
                  m_pResponse -> serialize(),
                  queryInfo );
    return NULL;
}

void ReqPutResponseArchive::setResponse( ResponseClient *pResponse ) {

    m_pResponse = pResponse;
}
