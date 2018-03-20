#ifndef STATICANALYZER_H
#define STATICANALYZER_H

#include <QString>
#include <MacroDefinitions/code/Analyzer/TypeStaticAnalyzer.h>

class StaticAnalyzer {


    quint32 m_IdAboutStaticAnalyzer;
    TypeStaticAnalyzer m_TypeStaticAnalyzer;
    quint32 m_Line;
    QString m_Description;
    QString m_LocationFile;
    quint32 m_IdLocationFile;

public:
    StaticAnalyzer();

    void clear();

    void setIdAboutStaticAnalyzer( quint32 IdAboutStaticAnalyzer );
    void setTypeStaticAnalyzer( TypeStaticAnalyzer typeStaticAnalyzer );
    void setTextTypeStaticAnalyzer( QString text );
    void setLine( quint32 line );
    void setDescription( QString description );
    void setLocationFile( QString locationFile );
    void setIdLocationFile( quint32 idLocationFile );

    quint32 getIdAboutStaticAnalyzer();
    TypeStaticAnalyzer getTypeStaticAnalyzer();
    quint32 getLine();
    QString getDescription();
    QString getLocationFile();
    quint32 getIdLocationFile();
};

#endif // STATICANALYZER_H
