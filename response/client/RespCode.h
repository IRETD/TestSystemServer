#ifndef RESPCODE_H
#define RESPCODE_H

#include <response/client/ResponseClient.h>
#include <response/client/subclasses/Stage.h>

class Stage;

class RespCode : public ResponseClient {

    QList < Stage > m_StageList;

public:
    RespCode( ResponseReciever responseReciever );

    void writeInStreamBuffer();
    void addStage( const Stage &codeStage );
    QList < Stage > getStage();
    QString serialize();
    void deserialize( QByteArray &byteArr );
};

#endif
