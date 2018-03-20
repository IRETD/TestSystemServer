#include "RespLeave.h"


RespLeave::RespLeave( ResponseReciever responseReciever ) : ResponseClient( responseReciever ) {

}


void RespLeave::writeInStreamBuffer() {

}


void RespLeave::setMessage( const QString &message ) {

    m_Message = message;
}
