#include "AnalyzeWorker.h"
#include <QProcess>

AnalyzeWorker::AnalyzeWorker() {
}


void AnalyzeWorker::setAnalyzeDirectory( QString directory ) {

    m_Directory = directory;
}


void AnalyzeWorker::setOutputDataFile( QString outputDataFile ) {

    m_OutputDataFile = outputDataFile;
}


ProcessResult AnalyzeWorker::startAnalyze() {

    QString argumentsLine = QString( " --xml " ) +
                            QString( " -v " ) +
                            QUOTE + m_Directory + QUOTE; //ПУТЬ ДО ПАПКИ БЕРЕМ В КАВЫЧКИ, ОБЯЗАТЕЛЬНО!!!
    QProcess process;
    process.setNativeArguments( argumentsLine );
    process.setStandardErrorFile( m_OutputDataFile ); //здесь уже кавычки не нужны, система сама настроит
    process.start( "cppcheck" );
    if ( !process.waitForStarted() ) {

        return ProcessResult::ERROR_START;
    }

    if ( !process.waitForFinished() ) {

        return ProcessResult::ERROR_FINISH;
    }

    return ProcessResult::ERROR_NONE;
}
