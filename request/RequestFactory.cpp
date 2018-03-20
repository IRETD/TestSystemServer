#include <request/RequestFactory.h>
#include <request/client/ReqAuth.h>
#include <request/client/ReqCode.h>
#include <request/client/ReqLabList.h>
#include <request/Request.h>
#include <request/client/ReqHistory.h>
#include <request/client/ReqAnalyze.h>
#include <request/teacher/TeacherReqLabList.h>
#include <request/teacher/TeacherReqHistory.h>

#include <request/server/ReqServerSettings.h>

RequestFactory::RequestFactory() {

}


RequestClient *RequestFactory::createClientRequest( const RequestClientType &typeRequest,
                                                    const RequestSender &requestSender ) const {

    RequestClient *pRequest = NULL;

    if ( typeRequest == RequestClientType::AUTHORIZATION ) {
        pRequest = new ReqAuth();
        pRequest -> setPriority( false );
        pRequest -> setRequestClientType( typeRequest );
    }

    if ( typeRequest == RequestClientType::CODE ) {
        pRequest = new ReqCode();
        pRequest -> setPriority( true );
        pRequest -> setRequestClientType( typeRequest );
    }

    if ( typeRequest == RequestClientType::DISCIPLINE_TASK ) {

        //Исполнение запроса на список всех дисциплин с лабами для препода и студента несколько отличны
        //поэтому и ввели такие разграничения
        if ( requestSender == RequestSender::STUDENT ) {

            pRequest = new ReqLabList;
        }

        if ( requestSender == RequestSender::TEACHER ) {

            pRequest = new TeacherReqLabList;
        }

        pRequest -> setPriority( false );
        pRequest -> setRequestClientType( typeRequest );
    }

    if ( typeRequest == RequestClientType::HISTORY ) {

        // По разному обрабатываем запрос по разному и для студента
        // и для препода.
        if ( requestSender == RequestSender::STUDENT ) {

            pRequest = new ReqHistory;
        }

        if ( requestSender == RequestSender::TEACHER ) {

            pRequest = new TeacherReqHistory;
        }

        pRequest -> setPriority( false );
        pRequest -> setRequestClientType( typeRequest );
    }

    if ( typeRequest == RequestClientType::ANALYZE ) {

        pRequest = new ReqAnalyze;
        pRequest -> setPriority( false );
        pRequest -> setRequestClientType( typeRequest );
    }

    if ( pRequest != NULL ) {
        pRequest -> setRequestType( RequestType::CLIENT );
    }

    return pRequest;
}


RequestServer *RequestFactory::createServerRequest( const RequestServerType &typeRequest ) const {

    RequestServer *pRequest = NULL;

    if ( typeRequest == RequestServerType::SERVER_SETTINGS ) {
        pRequest = new ReqServerSettings;
        pRequest -> setPriority( false );
    }

    if ( pRequest != NULL ) {
        pRequest -> setRequestType( RequestType::SERVER );
        pRequest -> setPriority( false );
    }

    return pRequest;
}

