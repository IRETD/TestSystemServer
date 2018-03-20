#include "ParserStaticAnalyzer.h"
#include <QXmlStreamReader>
#include <MacroDefinitions/code/Analyzer/ParserTagNames.h>
#include <code/Anazyler/StaticAnalyzer.h>


ParserStaticAnalyzer::ParserStaticAnalyzer() {
}


void ParserStaticAnalyzer::loadData( QString text ) {

    m_Text = text;

}

void ParserStaticAnalyzer::startParse() {

    QXmlStreamReader reader( m_Text );

    StaticAnalyzer staticAnalyzer;
    while ( !reader.atEnd() ) {

        reader.readNext();
        //ЖДЕМ НУЖНЫЙ ТЭГ
        if ( reader.name().toString() == NEEDED_TAG ) {
            QXmlStreamAttributes attributes = reader.attributes();
            staticAnalyzer.setLocationFile( attributes.value( FILE_LOCATION_ATTRIBUTE ).toString() );
            staticAnalyzer.setLine( attributes.value( LINE_ATTRIBUTE ).toInt() );
            staticAnalyzer.setTextTypeStaticAnalyzer( attributes.value( ERROR_TYPE_ATTRIBUTE ).toString() );
            staticAnalyzer.setDescription( attributes.value( DESCRIPTION_ATTRIBUTE ).toString() );
            m_ParseResult.append( staticAnalyzer );
        }

        /*
        //читаем номер строки с ошибкой
        if ( reader.name() == ERROR_LINE ) {

            QString numLine = reader.readElementText();
            staticAnalyzer.setLine( numLine.toInt() );
        }

        //читаем тип ошибки
        if ( reader.name() == ERROR_TYPE ) {

            QString type = reader.readElementText();
            staticAnalyzer.setTypeStaticAnalyzer( static_cast < TypeStaticAnalyzer > ( type.toInt() ) );
        }

        //читаем текст ошибки
        if ( reader.name() == ERROR_TEXT ) {

            staticAnalyzer.setDescription( reader.readElementText() );

            ///Это последний ТЕГ, если до него добрлись,
            /// значит мы прочила ВСЕ о текущей ошибке
            /// добавляем ее
            m_ParseResult.append( staticAnalyzer );

            //очищаем, уже старые, данные
            staticAnalyzer.clear();
        }
        */

    }
}

QList < StaticAnalyzer > ParserStaticAnalyzer::getParseResult() {

    return m_ParseResult;
}
