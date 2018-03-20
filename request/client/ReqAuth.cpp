#include <request/client/ReqAuth.h>
#include <response/client/RespAuth.h>
#include <QDateTime>
#include <log/MyLog.h>
#include <database/table/TableUser.h>
#include <response/server/RespAuthClient.h>
#include <database/table/TableAuthorizationHistory.h>
#include <windows.h>
#include <database/table/TableMessageCatalogForClient.h>
#include <MacroDefinitions/Request/Client/AuthResult.h>
#include <database/table/UniversalTable.h>
#include <MacroDefinitions/Request/Client/DefinitionsForReqAuth.h>


int ReqAuth::doAuth( const OurDataBase &db,
                     OurQueryInfo &queryInfo ) {

    int result = QUERY_NO_DATA;

    if( m_RequestSender == RequestSender::STUDENT ) {

        TableUser user( db );
        result = user.getId( m_Login,
                             m_Pass,
                             queryInfo );
    }


    if( m_RequestSender == RequestSender::TEACHER ) {

        UniversalTable teacherAuthTable( db );
        result = teacherAuthTable.getId( queryInfo,
                                         TABLE_NAME_FOR_TEACHER_AUTH,
                                         ID_FIELD_TITLE_FOR_TEACHER_AUTH,
                                         FIRST_FILED_TITLE_FOR_TEACHER_ATUH,
                                         SECOND_FIELD_TITLE_FOR_TEACHER_AUTH,
                                         m_Login,
                                         m_Pass );
     }

    return result;
}

ReqAuth::ReqAuth() {

    m_Priority = false;
}


void ReqAuth::readStream( QDataStream &stream ) {

    stream >> m_Login >> m_Pass;
}


ResponseClient* ReqAuth::doRequest( const OurDataBase &db, OurQueryInfo &queryInfo ) {

    qDebug() << "ReqAuth" << GetThreadId( GetCurrentThread() );

    // Указываем ПОЛУЧАТЕЛЯ.
    // ОБАЗЯТЕЛЬНО!
    RespAuth *pAuth = new RespAuth( static_cast < ResponseReciever > ( m_RequestSender ) );
    pAuth -> setResponseClientType( ResponseClientType::AUTHORIZATION );

    //если запрос от студента
    OurQueryInfo authQueryInfo;
    int result = doAuth( db,
                         authQueryInfo );

    if ( !authQueryInfo.isPermissible() ) {
        if ( !authQueryInfo.isConnectionError() ) {
            m_BugReport.addBug( db, authQueryInfo.getDescription(), "ReqAuth",
                                "doRequest", NULL, 25,
                                " m_Login = " + m_Login + "m_Pass = " + m_Pass, authQueryInfo );
        }
        return m_BugReport.getDefaultMessage();
    }

    TableMessageCatalogForClient messageTable( db );

    AuthResult authResult = result != QUERY_NO_DATA ? AuthResult::AUTHORIZATION_SUCCESS :
                                                      AuthResult::AUTHORIZATION_FAULT;
    pAuth -> setResult( authResult );
    pAuth -> setNewId( result );

    QString message;

    if ( result != QUERY_NO_DATA ) {
        message = messageTable.getMessage( MessageType::CORRECT_DATA_AUTH, queryInfo );
    }
    else {
        message = messageTable.getMessage( MessageType::INCORRECT_DATA_AUTH, queryInfo );
    }

    if ( !queryInfo.isPermissible() ) {

        if ( !queryInfo.isConnectionError() ) {
            m_BugReport.addBug( db, queryInfo.getDescription(), "ReqAuth",
                                "doRequest", NULL, 25,
                                " m_Login = " + m_Login + "m_Pass = " + m_Pass, queryInfo );
        }

        return m_BugReport.getDefaultMessage();
    }

    pAuth -> setMessage( message );

    return pAuth;
}
