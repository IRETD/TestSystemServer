#ifndef REQUESTSENDER_H
#define REQUESTSENDER_H

#include <QDataStream>

enum class RequestSender {

    STUDENT = 1,
    TEACHER = 2
};

inline QDataStream& operator >>( QDataStream &out,
                                 RequestSender &value ) {

    quint32 result;
    out >> result;
    value = static_cast < RequestSender > ( result );

    return out;
}

inline QDataStream& operator << (QDataStream &out, RequestSender &value ) {

    quint32 result;
    result = static_cast < quint32 > ( value );
    out << result;

    return out;
}

#endif // REQUESTSENDER_H
