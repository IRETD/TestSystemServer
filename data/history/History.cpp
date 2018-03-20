#include "History.h"
#include <QDataStream>


History::History() {


}


void History::setIdHistory(const int &idHistory) {

    m_IdHistory = idHistory;
}


void History::setTextResult( const QString &textResult ) {

    m_TextResult = textResult;
}


void History::setResult( const TestResult &result ) {

    m_Result = result;
}


void History::setDateHistory(const QDateTime &dateHistory) {

    m_DateHistory = dateHistory;
}


void History::setIdUserLab( const int idUserLab ) {

    m_IdUserLab = idUserLab;
}


QDataStream &operator >> ( QDataStream &stream,
                           History &value ) {

    stream >> value.m_IdUserLab >>
              value.m_IdHistory >>
              value.m_Result >>
              value.m_TextResult >>
              value.m_DateHistory;

    return stream;
}


//пишем данные с группы в поток
QDataStream &operator << ( QDataStream &stream,
                           History &value ) {

    stream << value.m_IdUserLab <<
              value.m_IdHistory <<
              value.m_Result <<
              value.m_TextResult <<
              value.m_DateHistory;

    return stream;
}


int History::getIdHistory() const {

    return m_IdHistory;
}


QString History::getTextResult() const {

    return m_TextResult;
}


TestResult History::getResult() const {

    return m_Result;
}


QDateTime History::getDateHistory() const {

    return m_DateHistory;
}


int History::getIdUserLab() const {

    return m_IdUserLab;
}


