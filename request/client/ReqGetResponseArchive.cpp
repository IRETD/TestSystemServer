#include "ReqGetResponseArchive.h"
#include <database/table/TableResponseArchive.h>


ReqGetResponseArchive::ReqGetResponseArchive( const ResponseFactory &factory ) {

    m_ResponseFactory = factory;
}


ResponseClient *ReqGetResponseArchive::doRequest( const OurDataBase &db,
                                                  OurQueryInfo &queryInfo ) {

    TableResponseArchive table( db );
    QList <QString> listArchiveResponse = table.getValue( m_IdClient, queryInfo );

    //Не будем отправлять клиенту сообщений!
    if ( !queryInfo.isPermissible() ) {
        if ( !queryInfo.isConnectionError() ) {
            m_BugReport.addBug( db, queryInfo.getDescription(), "ReqGetResponseArchive",
                                "doRequest", NULL, 14,
                                " m_IdClient = " + QString::number( m_IdClient ), queryInfo );
        }
        return NULL;//m_BugReport.getDefaultMessage();
    }

    ResponseClient *pResponse = NULL;
    for ( int i = 0; i < listArchiveResponse.size(); i++ ) {
        QString valueResponse = listArchiveResponse.at( i );
        QByteArray byteArr( valueResponse.toUtf8() );
        QDataStream stream( &byteArr, QIODevice::ReadOnly );

        int typeResponse;
        stream >> typeResponse;
        ResponseClientType responseClientType = static_cast < ResponseClientType > ( typeResponse );
        pResponse = m_ResponseFactory.createClientRequest( responseClientType );

        if ( pResponse != NULL ) {
            byteArr = stream.device() -> readAll();
            pResponse -> deserialize( byteArr );
        }
    }

    if ( !listArchiveResponse.isEmpty() ) {
        table.deleteValues( m_IdClient, queryInfo );
    }

    //Не будем отправлять клиенту сообщений!
    if ( !queryInfo.isPermissible() ) {
        if ( !queryInfo.isConnectionError() ) {
            m_BugReport.addBug( db, queryInfo.getDescription(), "ReqGetResponseArchive",
                                "doRequest", NULL, 44,
                                " m_IdClient = " + QString::number( m_IdClient ), queryInfo );
        }
        return NULL;//m_BugReport.getDefaultMessage();
    }

    return pResponse;
}


void ReqGetResponseArchive::setResponseClientFactory( const ResponseFactory &factory ) {

    m_ResponseFactory = factory;
}
