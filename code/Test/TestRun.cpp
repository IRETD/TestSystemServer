#include "TestRun.h"
#include <QProcess>
#include <QDebug>

TestRun::TestRun() {
}

void TestRun::setExeFile(QString exeFile) {

    m_ExeFilePath = exeFile;
}


void TestRun::setInputFile( QString inputFile ) {

    m_InputFilePath = inputFile;
}


void TestRun::setOutputFile( QString outputFile ) {

    m_OutputFilePath = outputFile;
}


void TestRun::setResultsFile( QString resultsFile ) {

    m_ResultsFilePath = resultsFile;
}


void TestRun::setLimits( TestParamLimits testParamLimits ) {

    m_TestParamLimits = testParamLimits;
}


ProcessResult TestRun::run() {

    //составляем строку с параметрами на лимиты по времени и памяти
    QString limitsText;
    if ( m_TestParamLimits.isThereMemoryLimits() ) {

        limitsText.append( QString( " -m " ) +
                           m_TestParamLimits.getMemoryLimitByBytes() +
                           QString( " " ) ); //оставляем после указания параметра пробел
    }

    if ( m_TestParamLimits.isThereTimeLimits() ) {

        limitsText.append( QString( " -t " ) +
                           m_TestParamLimits.getTimeLimitByMilliseconds() +
                           QString( "ms " ) ); //оставляем после указания параметра пробел
    }

    /*
    QStringList arg;

    ///ОБЯЗАТЕЛЬНО ПУТИ ОБРАМЛЯЕМ В КАВЫЧКИ!!!!
    /// QUOTE
    arg << QString( "-i" ) <<
           QUOTE + m_InputFilePath + QUOTE <<
           QString( "-o") <<
           QUOTE + m_OutputFilePath + QUOTE;

    //если определены пределы по времени или памяти
    if ( !limitsText.isEmpty() ) {
        arg << QUOTE + limitsText + QUOTE;
    }

    arg << QUOTE + m_ExeFilePath + QUOTE  <<
           ">" <<
           QUOTE + m_ResultsFilePath + QUOTE;
    */

    QString argumentsLine = QString( " -i " ) +
            QUOTE + m_InputFilePath + QUOTE +
            QString( " -o ") +
            QUOTE + m_OutputFilePath + QUOTE;

    if ( !limitsText.isEmpty() ) {
        argumentsLine = argumentsLine +
                SPACE +
                QUOTE + limitsText + QUOTE;
    }

    argumentsLine = argumentsLine +
            SPACE +
            QUOTE + m_ExeFilePath + QUOTE;

    QProcess process;
    process.setNativeArguments( argumentsLine );
    process.setStandardOutputFile( m_ResultsFilePath );
    process.start( "runexe" );
    if ( !process.waitForStarted() ) {

        return ProcessResult::ERROR_START;
    }

    //если был указан лимит по времени, то все нормально - ожидаем до конца,
    //в противном случае - лимит 30 СЕКУНД!!!!! (параметр по умолчанию)
    bool result = ( m_TestParamLimits.isThereTimeLimits() ) ? process.waitForFinished( NO_TIME_LIMITS ) :
                                                              process.waitForFinished();

    //qDebug() << process.readAll();
    return ( result ) ? ProcessResult::ERROR_NONE :
                        ProcessResult::ERROR_FINISH_TIMEOUT;

}
