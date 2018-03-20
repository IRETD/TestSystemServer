#ifndef IDCREATOR_H
#define IDCREATOR_H

#include <QObject>
#include <QQueue>

class IdCreator : public QObject {

    enum {

        CLIENT_IS_NOT_AUTH_ID = -1
    };

    int m_IdCounterForNotAuthorized;
    QQueue < int > m_QueueId;

public:
    IdCreator( QObject *pObjct = 0 );

    int getIdForNotAuthorizedClient();
    void addId( int id );
};

#endif // IDCREATOR_H
