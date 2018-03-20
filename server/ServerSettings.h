#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include <QString>

class ServerSettings {

    int m_IdleTimeSecond;
    int m_ClientBufferKilobyteMaxSize;
    int m_RequestCountLimit;
    int m_RequestTimeSecondLimit;
    int m_TimeMinuteInPeerAddressBlackList;
    QString m_DirectoryTest;

public:
    ServerSettings();

    void setIdleTimeSecond( const int &idleTimeSecond );
    void setClientBufferKilobyteMaxSize( const int &clientBufferMaximumSize );
    void setRequestCountLimit( const int &requestCountLimit );
    void setRequestTimeSecondLimit( const int &requestTimeSecondLimit );
    void setTimeMinuteInPeerAddressBalckList( const int &timeMinuteInPeerAddressBlackList );
    void setDirectoryTest( const QString &directoryTest );

    int getIdleTimeSecond() const;
    int getClientBufferKilobyteMaxSize() const;
    int getRequestCountLimit() const;
    int getRequestTimeLimit() const;
    int getTimeMinuteInPeerAddressBalckList() const;
    QString getDirectoryTest() const;
};

#endif
