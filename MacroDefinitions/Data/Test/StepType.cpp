#include <QDataStream>

enum class StepType;

QDataStream& operator >> ( QDataStream &out,
                           StepType &value ) {

    quint32 result;
    out >> result;
    value = static_cast < StepType > ( result );

    return out;
}


QDataStream& operator << ( QDataStream &out,
                           StepType &value ) {

    quint32 result;
    result = static_cast < quint32 > ( value );
    out << result;

    return out;
}
