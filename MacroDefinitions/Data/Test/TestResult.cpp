#include <QDataStream>
#include "TestResult.h"

QDataStream& operator >>( QDataStream &out,
                          TestResult &value ) {

    quint32 result;
    out >> result;
    value = static_cast < TestResult > ( result );

    return out;
}

QDataStream& operator << ( QDataStream &out,
                           TestResult &value ) {

    quint32 result;
    result = static_cast < quint32 > ( value );
    out << result;

    return out;
}
