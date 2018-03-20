#ifndef RESPLEAVE_H
#define RESPLEAVE_H

#include <response/client/ResponseClient.h>

class RespLeave : public ResponseClient {

    QString m_Message;

public:
    RespLeave( ResponseReciever responseReciever );

    void writeInStreamBuffer();
    void setMessage( const QString &message );
};

#endif // RESPLEAVE_H
