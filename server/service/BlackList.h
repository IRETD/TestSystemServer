#ifndef BLACKLIST_H
#define BLACKLIST_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QTime>
#include <QHash>

class BlackList : public QObject {

    Q_OBJECT

    int m_TimerPeerAddressMinuteStart;
    int m_LimitMinuteForPeerAddress;
    QHash < QString, QDateTime > m_PeerAddressTable;
    QTimer m_TimerPeerAddress;

private slots:
    void checkPeerAddress();

public:
    BlackList( QObject *pObjct = 0 );

    BlackList( const BlackList& copySource );

    void addPeerAddress( const QString &peerAddress , QDateTime &endTime );
    void addPeerAddress( const QString &peerAddress );
    bool removePeerAddress( const QString &peerAddress );
    bool contain( const QString &peerAddress );
    void setLimitMinutePeerAddress( const int &limitMinute );
    QHash < QString, QDateTime > getPeerAddressTable();
    BlackList& operator=( const BlackList& copySource );


};

#endif // BLACKLIST_H
