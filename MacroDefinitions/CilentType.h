#ifndef CILENTTYPE_H
#define CILENTTYPE_H

#include <MacroDefinitions/Request/Client/RequestSender.h>
enum class ClientType {

    UNKNOWN = 0,
    STUDENT = RequestSender::STUDENT,
    TEACHER = RequestSender::TEACHER
};

#endif // CILENTTYPE_H
