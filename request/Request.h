#ifndef REQUEST_H
#define REQUEST_H
#include <QByteArray>

#include <database/OurDataBase.h>
#include <response/client/ResponseClient.h>
#include <bug/BugReport.h>
#include <MacroDefinitions/Request/Client/RequestSender.h>

enum class RequestType {

    CLIENT = 1,
    SERVER = 2
};

class Request  {

protected:
    RequestType m_RequestType;
    bool m_Priority;
    BugReport m_BugReport;

    RequestSender m_RequestSender;
    int m_IdClient;
    QString m_ClassName;

public:
    Request();

    void setPriority( const bool &priority );
    bool getPriority();

    void setRequestType( const RequestType &requestType );
    RequestType getRequestType();

    void setRequestSender( RequestSender requestSender );
    virtual void readStream( QDataStream &stream );
    void setIdClient( const int &idClient );
    int getIdClient() const;
    RequestSender getRequestSender();

};


#endif
