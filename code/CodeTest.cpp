#include "CodeTest.h"
#include <QProcess>
#include <QObject>
#include <QTime>
#include <QTextStream>
#include <QStringList>
#include <log/MyLog.h>
#include <QDir>
#include <QDebug>
#include <code/TestDirectory.h>
#include <MacroDefinitions/code/TestFilesName.h>
#include <code/Test/TestRun.h>
#include <code/Test/TestResultParser.h>

//----------------------------------------------------------------
// СЛОТ
// Считываем выходные данные тестируемой программы.
//----------------------------------------------------------------
bool CodeTest::compareOutputResults( const QStringList &programOutputDataList,
                                     const QStringList &testOutputDataList ) {

    bool result = false;

    qDebug() << "program " << programOutputDataList << "\n";
    qDebug() << " test " << testOutputDataList << "\n";
    if ( programOutputDataList.size() == testOutputDataList.size() ) {

        result = true;

        for ( int i = 0; i < testOutputDataList.size(); i++ ) {

            QString outputDataTest = testOutputDataList.at( i );
            /// УДАЛЯЕМ СИМВОЛЫ ПЕРЕНОСА В КОНЦЕ СТРОК, ЧТОБЫ
            /// НЕ БЫЛО ПРОБЛЕМ ПРИ СРАВНЕНИИ
            /// runexe в файл с результатами работы программы
            /// в конце добавляет пробел!!!! Поэтому его надо убирать через trimmed.
            /// Пример
            /// ("-1 0 1 2 3 3 4 5 6 7 ") это вывод программы записанный runexe в файл
            /// ("-1 0 1 2 3 3 4 5 6 7") это тестовые данные из базы
            outputDataTest = outputDataTest.trimmed();
            QString outputDataProgram = programOutputDataList.at( i );
            outputDataProgram = outputDataProgram.trimmed();
            qDebug() << outputDataProgram << endl;
            qDebug() << outputDataTest;
            if ( outputDataProgram != outputDataTest ) {
                // !!!!
                result = false;
                break;
            }
        }
    }

    return result;
}


CodeTest::CodeTest() {

}

CodeTest::~CodeTest() {

}


TestResultsInfo CodeTest::doTest( const QStringList &inputDataList,
                                  const QStringList &outputDataList,
                                  const QString &fileExePath,
                                  const QString &fileExeName,
                                  const TestParamLimits testParamLimits /* = TestParamLimits() */ ) {

//    QDir::setCurrent( workingDirectory );
//    m_Process.setWorkingDirectory( workingDirectory );

    TestDirectory testDirectory;
    testDirectory.setCurrentDirectory( fileExePath );
    //пока не обрабатываем плачевную ситуацию о невозможности создать файл
    ///testDirectory.createFile( INPUT_TEST_FILE_NAME );
    ///writeInFile СОЗДАЕТ - ЕСЛИ НЕ СУЩЕСТВУЕТ,
    /// ПОЭТОМУ ОТДЕЛЬНО ВЫЗЫВАТЬ СОЗДАНИЕ БЕССМЫСЛЕННО :)
    testDirectory.writeInFile( INPUT_TEST_FILE_NAME,
                               inputDataList );
    TestRun testRun;
    testRun.setExeFile( fileExePath +
                        "/" + //разделитель для указания имени файла после пути
                        fileExeName );
    testRun.setInputFile( fileExePath +
                          "/" +
                          INPUT_TEST_FILE_NAME );

    testDirectory.createFile( OUTPUT_TEST_FILE_NAME );

    QString pathToOutputFile = fileExePath +
                               "/" +
                               OUTPUT_TEST_FILE_NAME;
    testRun.setOutputFile( pathToOutputFile );

    //Создаем сами файл ЯВНО перед началом теста
    testDirectory.createFile( RESULTS_TEST_FILE_NAME );

    QString pathToResultsFile = fileExePath +
                                "/" +
                                RESULTS_TEST_FILE_NAME;
    testRun.setResultsFile( pathToResultsFile );
    testRun.setLimits( testParamLimits );
    ///ЗАПУСКАЕМ ТЕСТ

    TestResultsInfo testResultsInfo;
    if ( testRun.run() == ProcessResult::ERROR_NONE ) {

        ///ПАРСИМ РЕЗУЛЬТАТЫ ИТОГОВ ТЕСТИРОВАНИЯ
        ///там результаты по памяти, времени.
        QString textOfResultsFile;
        //если результаты успешно считали
        if ( testDirectory.readFromFile( RESULTS_TEST_FILE_NAME,
                                         textOfResultsFile ) ) {
            TestResultParser resultParser;
            resultParser.setText( textOfResultsFile );
            testResultsInfo.setTestResultDescription( resultParser.getTestResult() );
            testResultsInfo.setTimePassed( resultParser.getTimePassed() );
            testResultsInfo.setPeakMemory( resultParser.getMemoryPeak() );

            ///ЕСЛИ РЕЗУЛЬТАТ ТЕСТИРОВАНИЯ ПОЛОЖИТЕЛЕН, СВЕРЯЕМ ВЫВОД ПРОГРАММЫ
            /// С ЖЕЛАЕМЫМ, ДАБЫ ОКОНЧАТЕЛЬНО ЗАВЕРШИТЬ ТЕСТИРОВАНИЕ

            if ( testResultsInfo.getTestResult() == TestResult::DONE ) {

                QStringList resultDataList;
                ///ЕСЛИ ВЫВОД ПРОГРАММЫ ИЗ ФАЙЛА УСПЕШНО СЧИТАЛСЯ

                // УКАЗЫВАЕМ ЗДЕСЬ НЕ ПУТЬ, А КОНКРЕТНОЕ ИМЯ ФАЙЛА!!!
                if ( testDirectory.readFromFile( OUTPUT_TEST_FILE_NAME,
                                                 resultDataList ) ) {

                    ///СВЕРЯЕМ ВЫВОД ОТ ПРОГРАММЫ И ПО ТЕСТУ
                    /// записываем ИТОГОВЫЙ результат тестирования
                    testResultsInfo.setTestResult( compareOutputResults( resultDataList,
                                                                         outputDataList ) ? TestResult::DONE:
                                                                                            TestResult::FAIL_TEST );
                }
            }
        }
    }

    return testResultsInfo;
}
