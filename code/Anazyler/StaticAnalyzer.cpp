#include "StaticAnalyzer.h"
#include <MacroDefinitions/code/Analyzer/TypeStaticAnalyzerText.h>


StaticAnalyzer::StaticAnalyzer() {

    clear();
}


void StaticAnalyzer::clear() {

    m_TypeStaticAnalyzer = TypeStaticAnalyzer::UNDEFINED_ANALYZE;
    m_Line = 0;
    m_Description.clear();
    m_LocationFile.clear();
}


void StaticAnalyzer::setIdAboutStaticAnalyzer( quint32 IdAboutStaticAnalyzer ) {

    m_IdAboutStaticAnalyzer = IdAboutStaticAnalyzer;
}


void StaticAnalyzer::setTypeStaticAnalyzer( TypeStaticAnalyzer typeStaticAnalyzer ) {

    m_TypeStaticAnalyzer = typeStaticAnalyzer;
}


void StaticAnalyzer::setTextTypeStaticAnalyzer( QString text ) {

    //ПО ТЕКСТУ ОПРЕДЕЛЯЕМ ТИП
    if ( text == ERROR_TYPE_ANALYZE_TEXT ) {

        setTypeStaticAnalyzer( TypeStaticAnalyzer::ERROR_ANALYZE );
    }
}


void StaticAnalyzer::setLine( quint32 line ) {

    m_Line = line;
}


void StaticAnalyzer::setDescription( QString description ) {

    m_Description = description;
}


void StaticAnalyzer::setLocationFile( QString locationFile ) {

    m_LocationFile = locationFile;
}


void StaticAnalyzer::setIdLocationFile( quint32 idLocationFile ) {

    m_IdLocationFile = idLocationFile;
}


quint32 StaticAnalyzer::getIdAboutStaticAnalyzer() {

    return m_IdAboutStaticAnalyzer;
}


TypeStaticAnalyzer StaticAnalyzer::getTypeStaticAnalyzer() {

    return m_TypeStaticAnalyzer;
}


quint32 StaticAnalyzer::getLine() {

    return m_Line;
}


QString StaticAnalyzer::getDescription() {

    return m_Description;
}


QString StaticAnalyzer::getLocationFile() {

    return m_LocationFile;
}


quint32 StaticAnalyzer::getIdLocationFile() {

    return m_IdLocationFile;
}
