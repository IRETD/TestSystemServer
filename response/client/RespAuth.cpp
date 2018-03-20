#include <response/client/RespAuth.h>
#include <response/client/ResponseClientName.h>


RespAuth::RespAuth( ResponseReciever responseReciever ) : ResponseClient( responseReciever ) {
}


void RespAuth::setResult( const AuthResult &result ) {

    m_Result = result;
}


void RespAuth::setMessage( const QString &message ) {

    m_Message = message;
}


void RespAuth::writeInStreamBuffer() {

    m_StreamBuffer << quint32( 0 ) <<
                      static_cast < int > ( ResponseClientType::AUTHORIZATION ) <<
                      m_Result <<
                      m_Message;
    m_StreamBuffer.device() -> seek(0);
    m_StreamBuffer << quint32(  m_Buffer.size() - sizeof( quint32 ) );
}


void RespAuth::setNewId( const int &newId ) {

    m_NewId = newId;
}


int RespAuth::getNewId() const {

    return m_NewId;
}


AuthResult RespAuth::getResult() const {

    return m_Result;
}
