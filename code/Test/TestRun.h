#ifndef TESTRUN_H
#define TESTRUN_H

#include <QString>
#include <code/Test/TestParamLimits.h>
#include <MacroDefinitions/code/ProcessResult.h>

class TestRun {

    #define NO_TIME_LIMITS - 1
    #define QUOTE "\""
    #define SPACE " "

    QString m_ExeFilePath;
    QString m_InputFilePath;
    QString m_OutputFilePath;
    QString m_ResultsFilePath;
    TestParamLimits m_TestParamLimits;

public:
    TestRun();
    void setExeFile( QString exeFile );
    void setInputFile( QString inputFile );
    void setOutputFile( QString outputFile );
    void setResultsFile( QString resultsFile );
    void setLimits( TestParamLimits testParamLimits );
    ProcessResult run();
};

#endif // TESTRUN_H
