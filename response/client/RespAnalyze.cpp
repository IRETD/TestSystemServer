#include "RespAnalyze.h"


RespAnalyze::RespAnalyze( ResponseReciever responseReciever ) : ResponseClient( responseReciever ) {
}


void RespAnalyze::setIdHistory( quint32 idHistory ) {

    m_IdHistory = idHistory;
}


void RespAnalyze::setIdAboutHistory( quint32 idAboutHistory ) {

    m_IdAboutHistory = idAboutHistory;
}


void RespAnalyze::addStaticAnalyzerList( const QList < StaticAnalyzer > &staticAnalyzerList ) {

    m_StaticAnalyzerList.append( staticAnalyzerList );
}


void RespAnalyze::addStaticAnalyzer( const StaticAnalyzer &staticAnalyzer ) {

    m_StaticAnalyzerList.append( staticAnalyzer );
}


void RespAnalyze::addIdSourceCode( quint32 idSourceCode,
                                   QString &sourceCode ) {

    m_IdSourceCodeContainer[ idSourceCode ] = sourceCode;
}


void RespAnalyze::writeInStreamBuffer() {

    m_StreamBuffer << quint32( 0 ) <<
                      static_cast < int > ( ResponseClientType::ANALYZE ) <<
                      m_IdSourceCodeContainer.size();

    ///пишем иcходные коды в поток
    if ( !m_IdSourceCodeContainer.isEmpty() ) {
        auto it = m_IdSourceCodeContainer.begin();
        auto itEnd = m_IdSourceCodeContainer.end();
        while ( it != itEnd ) {

            quint32 idSourceCode = it.key();
            QString sourceCode = it.value();
            m_StreamBuffer << idSourceCode <<
                              sourceCode;

            it++;
        }
    }


    m_StreamBuffer << m_IdHistory <<
                      m_IdAboutHistory <<
                      m_StaticAnalyzerList.size();
    foreach( StaticAnalyzer staticAnalyzer, m_StaticAnalyzerList ) {

        m_StreamBuffer << staticAnalyzer.getIdAboutStaticAnalyzer() <<
                          static_cast < int > ( staticAnalyzer.getTypeStaticAnalyzer() ) <<
                          staticAnalyzer.getDescription() <<
                          staticAnalyzer.getIdLocationFile() <<
                          staticAnalyzer.getLine() <<
                          staticAnalyzer.getLocationFile();
    }

    ///пишем объем ответа :)
    m_StreamBuffer.device() -> seek( 0 );
    m_StreamBuffer << quint32( m_Buffer.size() - sizeof( quint32 ) );
}
