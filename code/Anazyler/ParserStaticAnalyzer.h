#ifndef PARSERSTATICANALYZER_H
#define PARSERSTATICANALYZER_H
#include <QString>
#include <QList>
#include <code/Anazyler/StaticAnalyzer.h>

class ParserStaticAnalyzer {

    QString m_Text;
    QList < StaticAnalyzer > m_ParseResult;

public:

    ParserStaticAnalyzer();
    void loadData( QString text );
    void startParse();
    QList < StaticAnalyzer > getParseResult();
};

#endif // PARSERSTATICANALYZER_H
