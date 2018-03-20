#ifndef RESPMESSAGE_H
#define RESPMESSAGE_H


#include <response/client/ResponseClient.h>

class RespMessage : public ResponseClient {

    QString m_Message;

public:
    RespMessage( ResponseReciever responseReciever );

    void writeInStreamBuffer();
    void setMessage( const QString &message );
    void setMessageAsDefault();
};

#endif // RESPMESSAGE_H
