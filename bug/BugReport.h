#ifndef BUGREPORT_H
#define BUGREPORT_H

#include <database/OurDataBase.h>
#include <response/client/RespMessage.h>
#include <database/OurQueryInfo.h>

enum class MessageType {

    CORRECT_DATA_AUTH = 1,
    INCORRECT_DATA_AUTH = 3,
    UNEXPECTED_ERROR = 4
};

class BugReport {

public:
    BugReport();

    RespMessage *getMessage( const OurDataBase &db, const MessageType &messageType, OurQueryInfo &queryInfo );
    RespMessage *getDefaultMessage();
    void addBug( const OurDataBase &db, const QString &description, const QString &className, const QString &functionName,
                     const QString &functionInputData, const int bugLineNumber,
                     const QString &bugLineDescritpion, OurQueryInfo &queryInfo );
    bool prepareQueryInfo( const OurQueryInfo &queryInfo );
};

#endif // BUGREPORT_H
