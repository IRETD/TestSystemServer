//************************************************************************
// Класс отвечающий за процесс тестирования программы.
//
//************************************************************************


#ifndef CODETEST_H
#define CODETEST_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QByteArray>
#include <code/Test/TestParamLimits.h>
#include <Code/Test/TestResultsInfo.h>

class CodeTest : public QObject {

    Q_OBJECT

    ///СРАВНИВАЕТ РЕЗУЛЬТАТЫ ПРОГРАММЫ НА ВЫХОДЕ И РЕЗУЛЬТАТЫ ТЕСТА НА ВЫХОДЕ
    bool compareOutputResults( const QStringList &programOutputDataList,
                               const QStringList &testOutputDataList );

public:
    CodeTest();
    ~CodeTest();

    TestResultsInfo doTest( const QStringList &inputDataList,
                            const QStringList &outputDataList,
                            const QString &fileExePath,
                            const QString &fileExeName,
                            const TestParamLimits testParamLimits = TestParamLimits() );
};

#endif
