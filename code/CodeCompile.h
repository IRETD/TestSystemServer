//************************************************************************
// Этот класс содержит необходимые методы для получения исполняемого файла,
// по исходному коду клиента.
//
//************************************************************************

#ifndef CODECOMPILE_H
#define CODECOMPILE_H

#include <QObject>
#include <QString>
#include <QProcess>

enum {

    COMPILATION_COMPLETED = 0
};

class CodeCompile : public QObject {

   Q_OBJECT

   QString m_ExeFile;

public:
    CodeCompile( QObject *pObjct = 0 );

    int compile( const QString &path,
                 const QString &exeFileName );
    QString getExe();
};

#endif
