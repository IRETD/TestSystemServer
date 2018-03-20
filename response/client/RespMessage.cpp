#include "RespMessage.h"


RespMessage::RespMessage( ResponseReciever responseReciever ) : ResponseClient( responseReciever ) {
}


void RespMessage::writeInStreamBuffer() {

    m_StreamBuffer << quint32( 0 ) << static_cast <int> ( ResponseClientType::MESSAGE ) << m_Message;
    m_StreamBuffer.device() -> seek( 0 );
    m_StreamBuffer << quint32( m_Buffer.size() - sizeof( quint32 ) );
}


void RespMessage::setMessage( const QString &message ) {

    m_Message = message;
}


void RespMessage::setMessageAsDefault() {

    // xD.
    // Очень старый код.
    // Осмотрено 21.04.2016
    m_Message = "Упсс.... что-то пошло не так :( Мы уже работаем над этим!";
}
