/****************************************************************************
**
** Результат авторизации
**
****************************************************************************/

#ifndef RESPAUTH_H
#define RESPAUTH_H

#include <response/client/ResponseClient.h>
#include <MacroDefinitions/Request/Client/AuthResult.h>

class RespAuth : public ResponseClient {

    AuthResult m_Result;
    int m_NewId;
    QString m_Message;

public:
    RespAuth( ResponseReciever responseReciever );

    void setResult( const AuthResult &result );
    void setMessage( const QString &message );
    void writeInStreamBuffer();
    void setNewId( const int &newId );
    int getNewId() const;
    AuthResult getResult() const;
};

#endif
