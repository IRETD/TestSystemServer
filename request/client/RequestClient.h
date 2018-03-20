#ifndef REQUESTCLIENT_H
#define REQUESTCLIENT_H

#include <request/Request.h>
#include <MacroDefinitions/IdentifierMessage.h>
#include <bug/BugReport.h>
#include <database/OurQueryInfo.h>

typedef IdentifierMessage RequestClientType;

class RequestClient : public Request {

protected:
    RequestClientType m_RequestClientType;

public:
    RequestClient();

    virtual ResponseClient *doRequest( const OurDataBase &db, OurQueryInfo &queryInfo ) = 0;

    void setRequestClientType( const RequestClientType &requestClientType );
    RequestClientType getRequestClientType() const;
};

#endif // REQUESTCLIENT_H
