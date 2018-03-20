#ifndef TESTRESULTSINFO_H
#define TESTRESULTSINFO_H

#include <QString>
#include <MacroDefinitions/Data/Test/TestResult.h>
#include <MacroDefinitions/code/Test/TextOfTestResult.h>
#include <MacroDefinitions/database/table/TableAboutHistory/AdditionalColumnType.h>

class TestResultsInfo {

    int m_ExitCode;
    QString m_TimePassed;
    QString m_PeakMemory;
    QString m_TestResultDescription;
    TestResult m_TestResult;
    AdditionalColumnType m_AdditionalColumn;

public:
    TestResultsInfo();

    void clear();

    void setExitCode( int exitCode );
    void setTimePassed( QString timePassed );
    void setPeakMemory( QString peakMemory );
    void setTestResultDescription( QString testResultDescription );
    void setTestResult( TestResult testResult );
    void setAdditionalColumn( AdditionalColumnType additionalColumn );

    int getExitCode();
    QString getTimePassed();
    QString getPeakMemory();
    QString getTestResultDescription();
    TestResult getTestResult();
    AdditionalColumnType getAdditionalColumn();
};

#endif // TESTRESULTSINFO_H
