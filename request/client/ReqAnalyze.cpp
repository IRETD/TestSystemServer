#include "ReqAnalyze.h"
#include <database/table/TableStaticAnalyzer.h>
#include <database/table/TableAboutStaticAnalyzer.h>
#include <response/client/RespAnalyze.h>
#include <code/TestDirectory.h>
#include <assert.h>


ReqAnalyze::ReqAnalyze() {

}


void ReqAnalyze::readStream( QDataStream &stream ) {


    stream >> m_IdHistory >>
              m_IdAboutHistory;
}


ResponseClient *ReqAnalyze::doRequest( const OurDataBase &db,
                                       OurQueryInfo &queryInfo ) {

    RespAnalyze *pRespAnalyze = NULL;

    TableStaticAnalyzer tableStaticAnalyzer( db );

    OurQueryInfo queryInfoFroStaticAnalyzer;
    quint32 idStaticAnalyzer = tableStaticAnalyzer.getIdStaticAnalyzer( m_IdAboutHistory,
                                                                        queryInfoFroStaticAnalyzer );
    //если нашлась такая запись с idStaticAnalyzer
    if ( queryInfoFroStaticAnalyzer.getResult() ) {
        //но это еще ни о чем не говорит, так как быть может самих описаний анализа еще нет
        //(aboutStaticAnalyzer)
        TableAboutStaticAnalyzer tableAboutStaticAnalyzer( db );
        OurQueryInfo aboutStaticAnalyzerQueryInfo;
        QList < StaticAnalyzer > aboutStaticAnalyzerList = tableAboutStaticAnalyzer.getStaticAnalyzerList( idStaticAnalyzer,
                                                                                                           aboutStaticAnalyzerQueryInfo );
        if ( aboutStaticAnalyzerQueryInfo.getResult() ) {
            pRespAnalyze = new RespAnalyze( static_cast < ResponseReciever > ( m_RequestSender ) );
            pRespAnalyze -> setIdHistory( m_IdHistory );
            pRespAnalyze -> setIdAboutHistory( m_IdAboutHistory );
            pRespAnalyze -> addStaticAnalyzerList( aboutStaticAnalyzerList );
            ///ДОБАЛВЯЕМ ИСХОДНЫЕ КОДЫ
            QHash < QString,
                    quint32 > m_SourceCodeIdTable;
            for ( int i = 0; i < aboutStaticAnalyzerList.size(); i++ ) {

                quint32 idLocationFile;
                QString locationFile = aboutStaticAnalyzerList[ i ].getLocationFile();
                if ( m_SourceCodeIdTable.contains( locationFile ) ) {

                    idLocationFile = m_SourceCodeIdTable[ locationFile ];
                }
                else {

                    idLocationFile = m_SourceCodeIdTable.size();
                    m_SourceCodeIdTable[ locationFile ] = idLocationFile;
                }

                //устанавливаем id на файл для текущего анализа
                aboutStaticAnalyzerList[ i ].setIdLocationFile( idLocationFile );

                //указываем что все норм, информация есть
                queryInfo.setResult( true );
            }

            ///формируем исходные коды к анализам
            /// ФОРМИРОВАНИЕ ИСХОДНЫХ КОДОВ (ЧТЕНИЕ)
            if ( !m_SourceCodeIdTable.isEmpty() ) {

                auto it = m_SourceCodeIdTable.begin();
                auto itEnd = m_SourceCodeIdTable.end();
                while( it != itEnd ) {

                    QString filePath = it.key();
                    TestDirectory directory;
                    QString sourceCode;
                    ///если код прочитали и все ОК :)
                    /// ИНАЧЕ - БЕДА!
                    bool resultRead = directory.readFromFileByFullPath( filePath,
                                                                        sourceCode );
                    assert( resultRead != false );
                    if ( resultRead ) {
                        assert( !sourceCode.isEmpty() );
                        quint32 idSourceCode = it.value();
                        pRespAnalyze -> addIdSourceCode( idSourceCode,
                                                         sourceCode );
                    }

                    it++;
                }
            }
        }
    }

    return pRespAnalyze;
}
