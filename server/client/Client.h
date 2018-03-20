#ifndef CLIENT_H
#define CLIENT_H

#include <QByteArray>
#include <server/client/ClientSettings.h>
#include <server/client/ClientRequestStatistics.h>
#include <TypeDefinitions/BaseTypeDefinitions.h>
#include <MacroDefinitions/CilentType.h>

enum {

    REQUEST_SIZE_IS_NOT_READ = 0
};

class Client {

    ID_USER m_IdClient;
    ClientSettings m_Settings;
    ClientRequestStatistics m_RequestStatistics;
    QByteArray m_ClientBuffer;
    int m_RecievedRequestSize;
    ClientType m_ClientType;

public:
    Client();
    Client( const int &bufferMaximumSize , const int &requestCountLimit, const int &requestTimeLimit );

    void setIdClient( const ID_USER &idClient );
    void setRecievedRequestSize( const int &recievedRequestSize );
    void setClientBuffer( const QByteArray &clientBuffer );
    void addInClientBuffer( const QByteArray &clientBuffer );
    void clearClientBuffer();
    ClientSettings &getSettings();
    ClientRequestStatistics &getRequestStatistics();
    QByteArray &getClientBuffer();
    int getIdClient() const;
    int getRecievedRequestSize() const;
    bool isAuthorized() const;

    void setClientType( ClientType clientType );
    ClientType getClientType();

};

#endif // CLIENT_H
