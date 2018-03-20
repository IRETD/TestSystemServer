#include "StudentRespHistory.h"



StudentRespHistory::StudentRespHistory() {
}


void StudentRespHistory::setIdStudent( ID_STUDENT idStudent ) {

    m_IdStudent = idStudent;

}

/*

QDataStream &operator >> ( QDataStream &stream,
                           StudentRespHistory &value ) {

    stream >> value.m_IdStudent >>
              value.m_HistoryByteArray;

    return stream;
}
*/
QDataStream &operator >> ( QDataStream &stream,
                           StudentRespHistory &value ) {

    stream >> value.m_IdStudent >>
              value.m_HistoryList >>
              value.m_AboutHistoryList;

    return stream;
}


QDataStream &operator << ( QDataStream &stream,
                           StudentRespHistory &value ) {

    stream << value.m_IdStudent <<
              value.m_HistoryList <<
              value.m_AboutHistoryList;

    return stream;
}


/*
QDataStream &operator << ( QDataStream &stream,
                           StudentRespHistory const value ) {

    stream << value.m_IdStudent <<
              value.m_HistoryByteArray;

    return stream;
}
*/

ID_STUDENT StudentRespHistory::getIdStudent() {

    return m_IdStudent;
}


QList < History > StudentRespHistory::getHistoryList() {

    return m_HistoryList;
}


QList < AboutHistory > StudentRespHistory::getAboutHistoryList()  {

    return m_AboutHistoryList;
}



template < class T >
void StudentRespHistory::addHistory( T &data ) {

    m_HistoryList.append( data );
}


template < class T >
void StudentRespHistory::addAboutHistory( T &data ) {

    m_AboutHistoryList.append( data );
}
