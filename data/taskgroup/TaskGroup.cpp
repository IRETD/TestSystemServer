#include <QDataStream>
#include "TaskGroup.h"

QDataStream& operator >>( QDataStream &stream,
                          TaskGroup &value ) {

    stream >> value.m_IdLabGroup >>
              value.m_IdTask >>
              value.m_IdGroup;

    return stream;
}

QDataStream& operator << ( QDataStream &stream,
                           TaskGroup &value ) {

    stream << value.m_IdLabGroup <<
              value.m_IdTask <<
              value.m_IdGroup;

    return stream;
}
