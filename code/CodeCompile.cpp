#include <code/CodeCompile.h>
#include <QDebug>
#include <QTime>
#include <QString>
#include <string>
#include <QTextStream>
#include <QByteArray>
#include <QFile>
#include <thread/MyMutex.h>


CodeCompile::CodeCompile( QObject *pObjct ) : QObject( pObjct ) {

}


//----------------------------------------------------------------
// Процесс компиляции исходного кода
//----------------------------------------------------------------
int CodeCompile::compile( const QString &path, const QString &exeFilePath ) {

    QString fullPath = path + "/*.cpp";

    QStringList arg;
    arg << fullPath << QString( "-o" ) <<  path + "/" + exeFilePath;

    QProcess process;
    process.start( "g++", arg );
    process.waitForStarted();
    process.waitForFinished();

    int result = process.exitCode();

    // В каких то ситуация g++ возвращал 1
    // Хотя с кодом все ок. Разобраться в чем причина!!!!
    // Возможно из-за варнингов?
    if ( result == COMPILATION_COMPLETED ||
         result == 1 ) {

         result = COMPILATION_COMPLETED;
         m_ExeFile = exeFilePath;
    }

    return result;
}


QString CodeCompile::getExe() {

    return m_ExeFile;
}
