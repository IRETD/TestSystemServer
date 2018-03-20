#include "TestResultsInfo.h"


TestResultsInfo::TestResultsInfo() {

   clear();
}

void TestResultsInfo::clear() {

    m_TestResult = TestResult::UNDEFINED;
    m_ExitCode = 0;
    m_PeakMemory.clear();
    m_TimePassed.clear();
    m_TestResultDescription.clear();
    m_AdditionalColumn = AdditionalColumnType::NONE_ADDITIONAL_COLUMN;
}


void TestResultsInfo::setExitCode( int exitCode ) {

    m_ExitCode = exitCode;
}


void TestResultsInfo::setTimePassed( QString timePassed ) {

    m_TimePassed = timePassed;
}


void TestResultsInfo::setPeakMemory( QString peakMemory ) {

    m_PeakMemory = peakMemory;
}

void TestResultsInfo::setTestResultDescription( QString testResultDescription ) {

    m_TestResultDescription = testResultDescription;
    //ПО ТЕКСТУ СРАЗУ УСТАНАВЛИВАЕМ КОД
    //ДАБЫ В ПОСЛЕДУЮЩЕМ БЫСТРЕЕ ОТБИРАТЬ РЕЗУЛЬТАТ
    if ( m_TestResultDescription == SUCCESSFULLY_TERMINATED_TEXT ) {

        setTestResult( TestResult::DONE );
    }

    if ( m_TestResultDescription == MEMORY_LIMIT_TEXT ) {

        setTestResult( TestResult::MEMORY_LIMIT );
    }

    if ( m_TestResultDescription == TIME_LIMIT_TEXT ) {

        setTestResult( TestResult::TIME_LIMIT );
    }
}


void TestResultsInfo::setTestResult( TestResult testResult ) {

    m_TestResult = testResult;
}


void TestResultsInfo::setAdditionalColumn( AdditionalColumnType additionalColumn ) {

    m_AdditionalColumn = additionalColumn;
}


int TestResultsInfo::getExitCode() {

    return m_ExitCode;
}


QString TestResultsInfo::getTimePassed() {

    return m_TimePassed;
}


QString TestResultsInfo::getPeakMemory() {

    return m_PeakMemory;
}


TestResult TestResultsInfo::getTestResult() {

    return m_TestResult;
}


AdditionalColumnType TestResultsInfo::getAdditionalColumn() {

    return m_AdditionalColumn;
}
