#ifndef AUTHRESULT_H
#define AUTHRESULT_H

#include <QDataStream>

enum class AuthResult {

    AUTHORIZATION_FAULT = 0,
    AUTHORIZATION_SUCCESS
};

inline QDataStream& operator >>(QDataStream &out, AuthResult &value ) {

    quint32 result;
    out >> result;
    value = static_cast < AuthResult > ( result );

    return out;
}

inline QDataStream& operator << (QDataStream &out, AuthResult &value ) {

    quint32 result;
    result = static_cast < quint32 > ( value );
    out << result;

    return out;
}

#endif // AUTHRESULT_H
