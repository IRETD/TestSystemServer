#include "TestResultParser.h"
#include <QFile>
#include <QTextStream>


QString TestResultParser::cutStringByTag( QString tag ) {

    //находим начало
    QString text;
    int startPos = m_Text.indexOf( tag );
    if ( startPos != -1 ) {

        startPos = startPos +
                   QString( tag ).length();
        int endPos = m_Text.indexOf( END_OF_LINE,
                                     startPos );
        if ( endPos != -1 ) {
            //обрезаем всю строку
            text = m_Text.mid( startPos,
                               endPos - startPos );
            text = text.trimmed();
        }
    }
    return text;
}

TestResultParser::TestResultParser() {

}


void TestResultParser::setText(QString text) {

    m_Text = text;
}


QString TestResultParser::getTestResult() {

    ///СИМВОЛ ПЕРЕНОСА СТРОКИ НЕ ТРОГАЕМ
    QString testResult;

    int endPos = m_Text.indexOf( END_OF_LINE ) - 1;

    if ( endPos > 0 ) {

        testResult = m_Text.left( endPos );
    }

    return testResult;
}


QString TestResultParser::getTimePassed() {

    return cutStringByTag( TIME_PASSED );
}


QString TestResultParser::getMemoryPeak() {

    return cutStringByTag( PEAK_MEMORY );
}
