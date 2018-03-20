#include "StreamReader.h"
#include <request/RequestFactory.h>
#include <request/client/RequestClient.h>


StreamReader::StreamReader() {

}


RequestClient* StreamReader::readStream( Client &client,
                                       const RequestFactory &factory,
                                       RequestReadInfo &readInfo ) {

    RequestClient *pRequestClient( nullptr );
    QDataStream stream( client.getClientBuffer() );
    stream.setVersion( QDataStream::Qt_5_2 );
    //Если мы не считывали размер запроса
    if ( client.getRecievedRequestSize() == REQUEST_SIZE_IS_NOT_READ ) {
        //Если клиент прислал размер запроса
        if ( client.getClientBuffer().size() >= sizeof( quint32 ) ) {
            quint32 size = REQUEST_SIZE_IS_NOT_READ;
            stream >> size;
            //запоминаем размер запроса
            client.setRecievedRequestSize( size );
        }
    }


    readInfo.setReadStatus( ReadStatus::INPUT_DATA_ARE_INCOMPLETE );

    quint32 sizeRequest = client.getRecievedRequestSize();
    //Убеждаемся, что размер запроса был считан и были получены все блоки данных.
    if ( sizeRequest != REQUEST_SIZE_IS_NOT_READ &&
         client.getClientBuffer().size() >= sizeRequest ) {
        //считываем ОТПРАВИТЕЛЯ запроса
        RequestSender requestSender;
        stream >> requestSender;

        int typeRequest;
        stream >> typeRequest;
        RequestClientType requestClientType = static_cast <RequestClientType> ( typeRequest );

        RequestClient *pRequest = factory.createClientRequest( requestClientType,
                                                               requestSender );
        if ( pRequest != NULL ) {

            ///НЕ ЗАБЫВАЕМ УСТАНАВЛИВАТЬ ИНФОРМАЦИЮ О ТОМ, КТО ИМЕННО
            ///ЯВЛЯЕТСЯ ОТПРАВИТЕЛЕМ
            pRequest -> setRequestSender( static_cast < RequestSender > ( requestSender ) );
            pRequest -> readStream( stream );
            readInfo.setReadStatus( ReadStatus::INPUT_DATA_ARE_COMPLETE );
        }
        else {
            readInfo.setReadStatus( ReadStatus::INPUT_DATA_ARE_UNEXPECTED );
        }

        pRequestClient = pRequest;
    }

    QByteArray availableDataFromStream  = stream.device() -> readAll();
    client.setClientBuffer( availableDataFromStream );

    return pRequestClient;
}
