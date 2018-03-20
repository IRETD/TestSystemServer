#ifndef RESPONSERECIEVER_H
#define RESPONSERECIEVER_H
#include <MacroDefinitions/Request/Client/RequestSender.h>

enum class ResponseReciever {

    STUDENT = RequestSender::STUDENT,
    TEACHER = RequestSender::TEACHER
};

#endif // RESPONSERECIEVER_H
