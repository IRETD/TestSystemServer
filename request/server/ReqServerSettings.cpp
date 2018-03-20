#define ifBundleThenAddBugAndReturnNull( queryInfo, functionName, numLine, lineDescription ) { \
    if ( !queryInfo.isPermissible() ) { \
        if ( !queryInfo.isConnectionError() ) { \
            m_BugReport.addBug( db, queryInfo.getDescription(), "ReqServerSettings", \
                                functionName, NULL, numLine, \
                                lineDescription, queryInfo ); \
        } \
        return NULL; \
    } \
}\


#include "ReqServerSettings.h"
#include <response/server/RespServerSettings.h>
#include <database/table/TableServerSettings.h>
#include <database/table/TableClientBufferSettings.h>
#include <database/table/TablePeerAddressBlackList.h>
#include <database/table/TableIdleSettings.h>
#include <database/table/TableRequestSettings.h>

ReqServerSettings::ReqServerSettings() {
}

ResponseServer *ReqServerSettings::doRequest( const OurDataBase &db, OurQueryInfo &queryInfo ) {

    RespServerSettings *pRespServerSettings = new RespServerSettings;

    TablePeerAddressBlackList blackListTable( db );

    BlackList blackList;
    blackListTable.getBlackList( blackList, queryInfo );

    pRespServerSettings -> setBlackList( blackList );

    ServerSettings serverSettings;
    TableClientBufferSettings clientBufferTable( db );
    int clientBufferKilobyteMaxSize = clientBufferTable.getClientBufferMaxSize( DEFAULT_SETTING, queryInfo );
    ifBundleThenAddBugAndReturnNull( queryInfo, "doRequest", 37, " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ) );
    if ( queryInfo.getResult() ) {
        serverSettings.setClientBufferKilobyteMaxSize( clientBufferKilobyteMaxSize );
    }
    else {
        m_BugReport.addBug( db, "Отсутствует clientBufferKilobyteMaxSize ", "ReqServerSettings", "doRequest", NULL, 37,
                            " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ), queryInfo );
    }

    TableServerSettings serverSettingsTable( db );
    QString directoryTest = serverSettingsTable.getDirectoryTest( DEFAULT_SETTING, queryInfo );
    ifBundleThenAddBugAndReturnNull( queryInfo, "doRequest", 48, " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ) );
    if ( queryInfo.getResult() ) {
        serverSettings.setDirectoryTest( directoryTest );
    }
    else {
        m_BugReport.addBug( db, "Отсутствует directoryTest ", "ReqServerSettings", "doRequest", NULL, 48,
                            " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ), queryInfo );
    }

    int timeMinutePeerAddressBlackList = serverSettingsTable.getTimePeerAddressBlackList( DEFAULT_SETTING, queryInfo );
    ifBundleThenAddBugAndReturnNull( queryInfo, "doRequest", 58, " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ) );
    if ( queryInfo.getResult() ) {
        serverSettings.setTimeMinuteInPeerAddressBalckList( timeMinutePeerAddressBlackList );
    }
    else {
        m_BugReport.addBug( db, "Отсутствует timeMinutePeerAddressBlackList ", "ReqServerSettings", "doRequest", NULL, 58,
                            " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ), queryInfo );
    }

    TableIdleSettings idleSettingsTable( db );
    int timeSecond = idleSettingsTable.getTimeSecond( DEFAULT_SETTING, queryInfo );
    ifBundleThenAddBugAndReturnNull( queryInfo, "doRequest", 69, " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ) );
    if ( queryInfo.getResult() ) {
        serverSettings.setIdleTimeSecond( timeSecond );
    }
    else {
        m_BugReport.addBug( db, "Отсутствует timeSecond ", "ReqServerSettings", "doRequest", NULL, 69,
                            " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ), queryInfo );
    }

    TableRequestSettings requestSettingsTable( db );
    int requestCountLimit = requestSettingsTable.getRequestCountLimit( DEFAULT_SETTING, queryInfo );
    ifBundleThenAddBugAndReturnNull( queryInfo, "doRequest", 80, " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ) );
    if ( queryInfo.getResult() ) {
        serverSettings.setRequestCountLimit( requestCountLimit );
    }
    else {
        m_BugReport.addBug( db, "Отсутствует requestCountLimit ", "ReqServerSettings", "doRequest", NULL, 80,
                            " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ), queryInfo );
    }

    int requestTimeSecondLimit = requestSettingsTable.getRequestTimeLimit( DEFAULT_SETTING, queryInfo );
    ifBundleThenAddBugAndReturnNull( queryInfo, "doRequest", 90, " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ) );
    if ( queryInfo.getResult() ) {
        serverSettings.setRequestTimeSecondLimit(requestTimeSecondLimit );
    }
    else {
        m_BugReport.addBug( db, "Отсутствует requestTimeSecondLimit ", "ReqServerSettings", "doRequest", NULL, 90,
                            " DEFAULT_SETTING = " + QString::number( DEFAULT_SETTING ), queryInfo );
    }

    return pRespServerSettings;
}
