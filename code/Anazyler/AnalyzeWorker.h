#ifndef ANALYZEWORKER_H
#define ANALYZEWORKER_H

#include <QString>
#include <MacroDefinitions/code/ProcessResult.h>

class AnalyzeWorker {

    #define QUOTE "\""

    QString m_OutputDataFile;
    QString m_Directory;


public:
    AnalyzeWorker();

    void setAnalyzeDirectory( QString directory );
    void setOutputDataFile( QString outputDataFile );
    ProcessResult startAnalyze();
};

#endif
