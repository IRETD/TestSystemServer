#ifndef TESTRESULTPARSER_H
#define TESTRESULTPARSER_H

#include <QString>

class TestResultParser {

    #define END_OF_LINE "\n"
    #define TIME_PASSED "time passed:"
    #define PEAK_MEMORY "peak memory:"

    QString m_Text;

    QString cutStringByTag( QString header );

public:

    TestResultParser();
    void setText( QString text );
    QString getTestResult();
    QString getTimePassed();
    QString getMemoryPeak();
};

#endif // TESTRESULTPARSER_H
