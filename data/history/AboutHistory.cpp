#include "AboutHistory.h"
#include <QDataStream>

AboutHistory::AboutHistory() {

    m_Description.clear();
    m_TextResult.clear();
    m_Memory.clear();
    m_Time.clear();
    m_StepType = StepType::UNDEFINED;
}


QDataStream &operator >> ( QDataStream &stream,
                           AboutHistory &value ) {

    stream >> value.m_IdHistory >>
              value.m_IdAboutHistory >>
              value.m_Result >>
              value.m_StepType >>
              value.m_Description >>
              value.m_TextResult >>
              value.m_Memory >>
              value.m_Time >>
              value.m_AdditionalColumn;
    return stream;
}


//пишем данные с группы в поток
QDataStream &operator << ( QDataStream &stream,
                           AboutHistory &value ) {

    stream << value.m_IdHistory <<
              value.m_IdAboutHistory <<
              value.m_Result <<
              value.m_StepType <<
              //static_cast < int > ( value.getResult() ) <<
              //value.getTextResult() <<
              //static_cast < int > ( IdColumnAboutHistory::STEP ) <<
              value.m_Description <<
              //static_cast < int > ( IdColumnAboutHistory::RESULT ) <<
              value.m_TextResult <<
              //static_cast < int > ( IdColumnAboutHistory::MEMORY ) <<
              value.m_Memory <<
              //static_cast < int > ( IdColumnAboutHistory::TIME ) <<
              value.m_Time <<
              value.m_AdditionalColumn;
             // value.getColumnName();

    return stream;
}


void AboutHistory::setIdAboutHistory( const int &idAboutHistory ) {

    m_IdAboutHistory = idAboutHistory;
}



void AboutHistory::setResult( const TestResult &result ) {

    m_Result = result;
}


void AboutHistory::setIdHistory( const int &idHistory ) {

    m_IdHistory = idHistory;
}


void AboutHistory::setTextResult( const QString &textResult ) {

    m_TextResult = textResult;
}


void AboutHistory::setDescription( const QString &description ) {

    m_Description = description;
}


void AboutHistory::setMemory( QString memory ) {

    m_Memory = memory;
}

void AboutHistory::setTime(QString time) {

    m_Time = time;
}


void AboutHistory::setStepType( StepType stepType ) {

    m_StepType = stepType;
}


void AboutHistory::setAdditionalColumn(QString additionalColumn ) {

    m_AdditionalColumn = additionalColumn;
}


/*
void AboutHistory::setColumnName( const QString &columnName ) {

    m_ColumnName = columnName;
}
*/


int AboutHistory::getIdHistory() const {

    return m_IdHistory;
}


quint32 AboutHistory::getIdAboutHistory() const {

    return m_IdAboutHistory;
}



TestResult AboutHistory::getResult() const {

    return m_Result;
}


StepType AboutHistory::getStepType() {

    return m_StepType;
}


QString AboutHistory::getTextResult() const {

    return m_TextResult;
}


QString AboutHistory::getMemory() {

    return m_Memory;
}


QString AboutHistory::getTime() {

    return m_Time;
}


QString AboutHistory::getDescription() const {

    return m_Description;
}


QString AboutHistory::getAdditionalColumn() {

    return m_AdditionalColumn;
}

/*
QString AboutHistory::getColumnName() const {

    return m_ColumnName;
}
*/
