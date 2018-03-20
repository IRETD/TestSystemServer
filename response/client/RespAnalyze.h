#ifndef RESPANALYZE_H
#define RESPANALYZE_H

#include <code/Anazyler/StaticAnalyzer.h>
#include <QList>
#include <response/client/ResponseClient.h>

class RespAnalyze : public ResponseClient {

    quint32 m_IdHistory;
    quint32 m_IdAboutHistory;
    QList < StaticAnalyzer > m_StaticAnalyzerList;
    QHash < quint32,
            QString > m_IdSourceCodeContainer;

public:
    RespAnalyze( ResponseReciever responseReciever );

    void setIdHistory( quint32 idHistory );
    void setIdAboutHistory( quint32 idAboutHistory );
    void addStaticAnalyzerList( const QList < StaticAnalyzer > &staticAnalyzerList );
    void addStaticAnalyzer( const StaticAnalyzer &staticAnalyzer );
    void addIdSourceCode( quint32 idSourceCode,
                          QString &sourceCode );
    void writeInStreamBuffer();
};

#endif
