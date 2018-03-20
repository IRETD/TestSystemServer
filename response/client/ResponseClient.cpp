#include <response/client/ResponseClient.h>


ResponseClient::ResponseClient( ResponseReciever responseReciever /* = ResponseReciever::STUDENT */) : m_StreamBuffer( &m_Buffer,
                                                                                                                       QIODevice::ReadWrite ) {

    m_StreamBuffer.setVersion( QDataStream::Qt_5_2 );
    m_ResponseReciever = responseReciever;
}


QString ResponseClient::serialize() {
    // ничего не делаем =)
    return NULL;
}


void ResponseClient::deserialize ( QByteArray &byteArr ) {
    // ничего не делаем =)
}


QByteArray &ResponseClient::getBuffer() {

    return m_Buffer;
}


void ResponseClient::setIdClient( const int &idClient ) {

    m_IdClient = idClient;
}


int ResponseClient::getIdClient() const {

    return m_IdClient;
}


void ResponseClient::setResponseClientType( const ResponseClientType &responseType ) {

    m_ResponseType = responseType;
}


ResponseClientType ResponseClient::getResponseClientType() {

    return m_ResponseType;
}


void ResponseClient::clearStream() {

    m_Buffer.clear();
    m_StreamBuffer.device() -> seek( 0 );
}


void ResponseClient::prepareStream() {

    m_StreamBuffer.device() -> seek( 0 );
    m_StreamBuffer << quint32( m_Buffer.size() -
                               sizeof( quint32 ) );
}


ResponseReciever ResponseClient::getResponseReciever() {

    return m_ResponseReciever;
}


void ResponseClient::setResponseReciever(ResponseReciever responseReciever) {

    m_ResponseReciever = responseReciever;
}


void ResponseClient::streamProlog( ResponseClientType responseType ) {

    m_StreamBuffer << quint32( 0 ) <<
                      static_cast < int > ( responseType );
}


void ResponseClient::streamEpilog() {

    prepareStream();
}
