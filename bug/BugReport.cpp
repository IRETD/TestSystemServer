#define ifBundleThenAddBugAndReturnMessage( queryInfo, functionName, numLine, lineDescription ) { \
    if ( !queryInfo.isPermissible() ) { \
        if ( !queryInfo.isConnectionError() ) { \
            addBug( db, queryInfo.getDescription(), "BugReport", \
                                functionName, NULL, numLine, \
                                lineDescription, queryInfo ); \
        } \
        return getDefaultMessage(); \
    } \
}\

#include "BugReport.h"
#include <database/table/TableMessageCatalogForClient.h>
#include <database/table/TableBugList.h>


BugReport::BugReport() {
}



// Кажется, это очень старый код.
// Осмотрено 21.04.2016

RespMessage *BugReport::getMessage( const OurDataBase &db, const MessageType &messageType, OurQueryInfo &queryInfo ) {

    TableMessageCatalogForClient messageTable( db );
    QString message = messageTable.getMessage( messageType, queryInfo );
    ifBundleThenAddBugAndReturnMessage( queryInfo, "getMessage", 24, " messageType = " + QString::number( static_cast < int > ( messageType ) ) );

    RespMessage *pRespMessage = new RespMessage( ResponseReciever::STUDENT );

    if ( message.isEmpty() ) {
        addBug(db, "Не найдено сообщение!", "BugReport", "getMessage",
               "messageType = "  + QString::number ( static_cast < int > ( messageType ) ),
               20, NULL, queryInfo);
        pRespMessage -> setMessageAsDefault();
    }
    else {
        pRespMessage -> setMessage( message );
    }

    return pRespMessage;
}


RespMessage *BugReport::getDefaultMessage() {

    RespMessage *pRespMessage = new RespMessage( ResponseReciever::STUDENT );
    pRespMessage -> setMessageAsDefault();
    return pRespMessage;
}


void BugReport::addBug( const OurDataBase &db, const QString &description, const QString &className,
                        const QString &functionName, const QString &functionInputData, const int bugLineNumber,
                        const QString &bugLineDescritpion, OurQueryInfo &queryInfo ) {

    TableBugList bagListTable( db );
    bagListTable.insert( description, QDateTime::currentDateTime(), className, functionName, functionInputData, bugLineNumber,
                         bugLineDescritpion, queryInfo );
}
