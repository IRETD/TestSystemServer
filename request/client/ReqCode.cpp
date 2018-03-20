#define ifBundleThenAddBugAndReturnNull( queryInfo, functionName, numLine, lineDescription ) { \
    if ( !queryInfo.isPermissible() ) { \
        if ( !queryInfo.isConnectionError() ) { \
            m_BugReport.addBug( db, queryInfo.getDescription(), "ReqCode", \
                                functionName, NULL, numLine, \
                                lineDescription, queryInfo ); \
        } \
        return NULL; \
    } \
}\

#define ifBundleThenAddBugAndReturnTestDataList( queryInfo, functionName, numLine, lineDescription ) { \
    if ( !queryInfo.isPermissible() ) { \
        if ( !queryInfo.isConnectionError() ) { \
            m_BugReport.addBug( db, queryInfo.getDescription(), "ReqCode", \
                                functionName, NULL, numLine, \
                                lineDescription, queryInfo ); \
        } \
        return testDataList; \
    } \
}\

#define ifBundleThenAddBugAndReturnMessage( queryInfo, functionName, numLine, lineDescription ) { \
    if ( !queryInfo.isPermissible() ) { \
        if ( !queryInfo.isConnectionError() ) { \
            m_BugReport.addBug( db, queryInfo.getDescription(), "ReqCode", \
                                functionName, NULL, numLine, \
                                lineDescription, queryInfo ); \
        } \
        return m_BugReport.getDefaultMessage(); \
    } \
}\

// description - значение какого поля хотим вставить
// columnName - имя столбца для этого поля
#define sendAboutHistoryMacro( stepType, testResultsInfo ) {\
    sendAboutHistory( db, \
                      m_IdUserLab,\
                      idHistory, \
                      idAboutHistory, \
                      stepType, \
                      testResultsInfo, \
                      queryInfo );\
}\





#include <data/history/AboutHistory.h>
#include <data/history/History.h>
#include <response/client/RespCode.h>
#include <response/client/RespMessage.h>
#include <request/client/ReqCode.h>
#include <code/CodeCompile.h>
#include <code/CodeTest.h>
#include <QDateTime>
#include <response/client/subclasses/Stage.h>
#include <database/table/TableStep.h>
#include <database/table/TableResult.h>
#include <database/table/TableHistory.h>
#include <database/table/TableTest.h>
#include <database/table/TableAboutHistory.h>
#include <database/table/TableUserLab.h>
#include <database/table/TableVariantLab.h>
#include <database/table/TableTestInput.h>
#include <database/table/TableTestOutput.h>
#include <database/table/UniversalTable.h>
#include <code/TestData.h>
#include <code/TestDirectory.h>
#include <zip/ZipArchiver.h>
#include <QCoreApplication>
#include <windows.h>
#include <response/client/RespHistory.h>
#include <database/table/TableStaticAnalyzer.h>
#include <code/Anazyler/AnalyzeWorker.h>
#include <MacroDefinitions/code/Analyzer/AnalyzeFileName.h>
#include <code/Anazyler/ParserStaticAnalyzer.h>
#include <database/table/TableAboutStaticAnalyzer.h>
#include <response/teacher/TeacherRespHistory.h>


// Всякие макроопределения для имен таблиц
#include <MacroDefinitions/Request/Teacher/DefinitionsForTeacherReqLabList.h>


ReqCode::ReqCode() {

    m_ClassName = "ReqCode";
    m_Priority = true;
}


//----------------------------------------------------------------
// Получить тестовые данные для тестируемой программы
//----------------------------------------------------------------
QList < TestData > ReqCode::getTestDataList( const OurDataBase &db, const int &idVariant,
                                             OurQueryInfo &queryInfo ) {

    QList < TestData > testDataList;
    TableTestInput testInputTable( db );
    TableTestOutput testOutputTable( db );
    TableTest testTable( db );

    QList < quint32 > idTestList = testTable.getIdTestList( idVariant, queryInfo );
    ifBundleThenAddBugAndReturnTestDataList( queryInfo, "getDataList", 77, " idVariant = " + QString::number( idVariant ) );

    for ( int indexIdTest = 0; indexIdTest < idTestList.size(); indexIdTest++ ) {
        TestData testData;
        quint32 idTest = idTestList.at( indexIdTest );

        QStringList inputDataList = testInputTable.getInputDataList( idTest, queryInfo );
        ifBundleThenAddBugAndReturnTestDataList( queryInfo, "getDataList", 84, " idTest = " + QString::number( idTest ) );

        for ( int indexInputData = 0; indexInputData < inputDataList.size(); indexInputData++ ) {
            testData.addInputData( inputDataList.at( indexInputData ) );
        }

        QStringList outputDataList = testOutputTable.getOutputDataList( idTest, queryInfo );
        ifBundleThenAddBugAndReturnTestDataList( queryInfo, "getDataList", 91, " idTest = " + QString::number( idTest ) );

        for ( int indexOutputData = 0; indexOutputData < outputDataList.size(); indexOutputData++ ) {
            testData.addOutputData( outputDataList.at( indexOutputData ) );
        }
        testDataList.append( testData );
    }

    return testDataList;
}


//----------------------------------------------------------------
// Занести информацию в бд об ошибке компиляции
//----------------------------------------------------------------
void ReqCode::compilationError( const OurDataBase &db,
                                const QString &pathCodeFolder,
                                OurQueryInfo &queryInfo ) {


    TestResultsInfo testResultsInfo;
    testResultsInfo.setTestResult( TestResult::FAIL_TEST );
    TableHistory historyTable( db );
    QDateTime dateTime = QDateTime::currentDateTime();
    int idHistory = historyTable.insert( m_IdUserLab,
                                         testResultsInfo.getTestResult(),
                                         dateTime,
                                         pathCodeFolder,
                                         queryInfo );
    sendHistory( db,
                 idHistory,
                 m_IdUserLab,
                 testResultsInfo.getTestResult(),
                 queryInfo,
                 dateTime );

    TableAboutHistory aboutHistoryTable( db );
    int idAboutHistory = aboutHistoryTable.insert( idHistory,
                                                   StepType::COMPILATION,
                                                   testResultsInfo,
                                                   queryInfo );
    //отправляем описание этапа;
    sendAboutHistoryMacro( StepType::COMPILATION,
                           testResultsInfo );


    return;
}


//----------------------------------------------------------------
// Тестируем программу клиента
//----------------------------------------------------------------
void ReqCode::testingProgram( const OurDataBase &db,
                              const QString &pathCodeFolder,
                              const QString &exeFile,
                              OurQueryInfo &queryInfo ) {

    TableHistory historyTable( db );
    //начинаем тестирование
    //заносим это в бд

    QDateTime dateTime = QDateTime::currentDateTime();
    int idHistory = historyTable.insert( m_IdUserLab,
                                         TestResult::TESTING,
                                         dateTime,
                                         pathCodeFolder,
                                         queryInfo );
    //начали тестирование
    sendHistory( db,
                 idHistory,
                 m_IdUserLab,
                 TestResult::TESTING,
                 queryInfo,
                 dateTime );


    TestResultsInfo testResultsInfo;
    testResultsInfo.setTestResult( TestResult::DONE );
    //предписываем дополнительный столбец
    TableAboutHistory aboutHistoryTable( db );
    int idAboutHistory = aboutHistoryTable.insert( idHistory,
                                                   StepType::COMPILATION,
                                                   testResultsInfo,
                                                   queryInfo );
    //отправляем информацию о этапе

    sendAboutHistoryMacro( StepType::COMPILATION,
                           testResultsInfo );

    ///ЗДЕСЬ НАЧИНАЕМ НАЛАИЗ ПРИ НЕОБХОДИМОСТИ
    testResultsInfo.setAdditionalColumn( AdditionalColumnType::ANALYZE_ADDITIONAL_COLUMN_TYPE );
    idAboutHistory = aboutHistoryTable.insert( idHistory,
                                               StepType::ANALYZE,
                                               testResultsInfo,
                                               queryInfo );
    //отправляем информацию клиенту о том, что пошел АНАЛИЗ
    testResultsInfo.clear();
    testResultsInfo.setTestResult( TestResult::TESTING );
    sendAboutHistoryMacro( StepType::ANALYZE,
                           testResultsInfo );

    TestResult resultAnalyze = analyze( db,
                                        idAboutHistory,
                                        pathCodeFolder,
                                        queryInfo );

    testResultsInfo.setTestResult( resultAnalyze );
    aboutHistoryTable.updateResult( idAboutHistory,
                                    testResultsInfo,
                                    queryInfo );
    sendAboutHistoryMacro( StepType::ANALYZE,
                           testResultsInfo );


    TableUserLab userLabTable( db );
    int idVariant = userLabTable.getIdVariant( m_IdUserLab, queryInfo );

    TableVariantLab variantLabTable( db );
    int timeLimit = variantLabTable.getTimeLimit( idVariant, queryInfo );
//    ifBundleThenAddBugAndReturnNull( queryInfo, "testingProgram", 181, " idVariant = " + QString::number( idVariant ) );

    QList < TestData > testDataList = getTestDataList( db, idVariant, queryInfo );
//    ifBundleThenAddBugAndReturnNull( queryInfo, "testingProgram", 184, " idVariant = " + QString::number( idVariant ) );

    for ( int numberTest = 0; numberTest < testDataList.size(); numberTest++ ) {

        //устанавливаем начальную информацию по тестированию (НАЧАЛО ТЕСТИРОВАНИЯ)
        TestResultsInfo testResultsInfo;
        testResultsInfo.setTestResult( TestResult::TESTING );
        idAboutHistory = aboutHistoryTable.insert( idHistory,
                                                   StepType::TEST,
                                                   testResultsInfo,
                                                   queryInfo );
        sendAboutHistoryMacro( StepType::TEST,
                               testResultsInfo );


        QStringList inputDataList = testDataList[ numberTest ].getInputDataList();
        QStringList outputDataList = testDataList[ numberTest ].getOutputDataList();

        CodeTest codeTest;
        //добавляем скобочки
        ///???? Мб и не надо, так как я в doTest передаю теперь явно путь и имя exe
        ///QString pathExeFile = "\"" + pathCodeFolder + "/" + exeFile + "\"";


        ///НЕ ЗАБЫДЬ ЗДЕСЬ УКАЗАТЬ ОГРАНИЧЕНИЯ В КАЧЕСТВЕ ПАРАМЕТРА
        /// НАУЧИТЬСЯ СЧИТЫВАТЬ ОГРАНИЧЕНИЯ ИЗ БАЗЫ
        testResultsInfo = codeTest.doTest( inputDataList,
                                           outputDataList,
                                           pathCodeFolder,
                                           exeFile );

        switch( testResultsInfo.getTestResult() ) {

            case TestResult::DONE:

                aboutHistoryTable.updateResult( idAboutHistory,
                                                testResultsInfo,
                                                queryInfo );
                sendAboutHistoryMacro( StepType::TEST,
                                       testResultsInfo );


                break;

            case TestResult::FAIL_TEST :

                aboutHistoryTable.updateResult( idAboutHistory,
                                                testResultsInfo,
                                                queryInfo );
                sendAboutHistoryMacro( StepType::TEST,
                                       testResultsInfo );


                historyTable.updateResult( idHistory,
                                           TestResult::FAIL_TEST,
                                           queryInfo );

                sendHistory( db,
                             idHistory,
                             m_IdUserLab,
                             TestResult::FAIL_TEST,
                             queryInfo,
                             dateTime );

                return;

            case TestResult::TIME_LIMIT :

                aboutHistoryTable.updateResult( idAboutHistory,
                                                testResultsInfo,
                                                queryInfo );
                sendAboutHistoryMacro( StepType::TEST,
                                       testResultsInfo );

                historyTable.updateResult( idHistory,
                                           TestResult::FAIL_TEST,
                                           queryInfo );
                sendHistory( db,
                             idHistory,
                             m_IdUserLab,
                             TestResult::FAIL_TEST,
                             queryInfo,
                             dateTime );

                return;

            case TestResult::MEMORY_LIMIT :

                aboutHistoryTable.updateResult( idAboutHistory,
                                                testResultsInfo,
                                                queryInfo );
                sendAboutHistoryMacro( StepType::TEST,
                                       testResultsInfo );
    //                ifBundleThenAddBugAndReturnNull( queryInfo, "testingProgram", 241, " TEST = " + QString::number( TEST ) +
    //                                                 " TIME_LIMIT = " + QString::number( TIME_LIMIT) );

                historyTable.updateResult( idHistory,
                                           TestResult::FAIL_TEST,
                                           queryInfo );
                sendHistory( db,
                             idHistory,
                             m_IdUserLab,
                             TestResult::FAIL_TEST,
                             queryInfo,
                             dateTime );

                ///DO MEMORY LIMIT ERROR UPDATE IN BASE!!!!
                   ///      Также сделать обновление в базу по памяти и времени в тестах (ВСЕ данные о результатах тестирования
                      ///   помещались в базу).
                         ///Также, возвращать корреткную строку связанную при превышении времени и памяти

            default:
                aboutHistoryTable.updateResult( idAboutHistory,
                                                testResultsInfo,
                                                queryInfo );
                sendAboutHistoryMacro( StepType::TEST,
                                       testResultsInfo );
//                ifBundleThenAddBugAndReturnNull( queryInfo, "testingProgram", 254, " TEST = " + QString::number( TEST ) +
//                                                 " SOMETHING_WRONG = " + QString::number( TIME_LIMIT) );

                historyTable.updateResult( idHistory, TestResult::SOMETHING_WRONG, queryInfo );
                sendHistory( db, idHistory, m_IdUserLab, TestResult::SOMETHING_WRONG, queryInfo, dateTime );

                return;
        }
    }

    historyTable.updateResult( idHistory, TestResult::DONE, queryInfo );
    sendHistory( db, idHistory, m_IdUserLab, TestResult::DONE, queryInfo, dateTime );
}


TestResult ReqCode::analyze( const OurDataBase &db,
                             quint32 idAboutHistory,
                             const QString &pathCodeFolder,
                             OurQueryInfo &queryInfo ) {

    TestResult testResult = TestResult::FAIL_TEST;
    //заносим в БД инфу о анализе
    TableStaticAnalyzer tableStaticAnalyzer( db );
    quint32 idStaticAnalyzer = tableStaticAnalyzer.insert( idAboutHistory,
                                                           TestResult::TESTING,
                                                           queryInfo );

    AnalyzeWorker analyzeWorker;
    analyzeWorker.setAnalyzeDirectory( pathCodeFolder );
    QString pathToAnalyzeFile = pathCodeFolder +
                                "/" +
                                ANALYZE_FILE_NAME;
    analyzeWorker.setOutputDataFile( pathToAnalyzeFile );

    //если анализ прошел УСПЕШНО
    if ( analyzeWorker.startAnalyze() == ProcessResult::ERROR_NONE ) {

        TestDirectory directory;
        directory.setCurrentDirectory( pathCodeFolder );
        QString dataForParser;
        //если ВСЕ считалось
        //ФАЙЛ ДОЛЖЕН ОТКРЫТЬСЯ!!!!
        //ЕГО ДОЛЖЕН БЫЛ СОЗДАТЬ АНАЛИЗАТОР В ЛЮБОМ СЛУЧАЕ,
        //ДАЖЕ ЕСЛИ НЕТУ ОШИБОК
        ///ФАЙЛ ВСЕ РАВНО СОЗДАЕТСЯ, ДАЖЕ ЕСЛИ НЕТУ ОШИБОК
        if ( directory.readFromFile( ANALYZE_FILE_NAME,
                                     dataForParser ) ) {
            ParserStaticAnalyzer parser;
            parser.loadData( dataForParser );
            parser.startParse();
            //Добавляем РЕЗУЛЬТАТЫ АНАЛИЗА В БАЗУ
            QList < StaticAnalyzer > staticAnalyzerResults = parser.getParseResult();
            ///Если результаты с файла не были прочитаны,
            ///значит ошибок НЕТ
            if ( staticAnalyzerResults.isEmpty() ) {

                testResult = TestResult::DONE;
            }

            foreach ( StaticAnalyzer staticAnalyzer,
                      staticAnalyzerResults ) {
                TableAboutStaticAnalyzer tableAboutStaticAnalyzer( db );
                tableAboutStaticAnalyzer.insert( idStaticAnalyzer,
                                                 staticAnalyzer,
                                                 queryInfo );
            }
        }
    }


    return testResult;
}


void ReqCode::sendHistory( const OurDataBase &db,
                           const ID_TYPE &idHistory,
                           const ID_TYPE &idUserLab,
                           const TestResult &idResult,
                           OurQueryInfo &queryInfo ,
                           const QDateTime &dateTime /*= NULL*/) {


    // Отправка СТУДЕНТУ
    RespHistory *pRespHistory = new RespHistory( static_cast < ResponseReciever > ( m_RequestSender ) );

    History history;
    history.setIdHistory( idHistory );
    history.setIdUserLab( idUserLab );
    history.setResult( static_cast < TestResult > ( idResult ) );
    history.setDateHistory( dateTime );

    TableResult resultTable( db );
    QString textResult = resultTable.getResult( idResult,
                                                queryInfo );
    history.setTextResult( textResult );

    pRespHistory -> addHistory( history );
    pRespHistory -> setIdClient( m_IdClient );
    pRespHistory -> setResponseClientType( ResponseClientType::HISTORY );
    pRespHistory -> writeInStreamBuffer();

    emit sendResponseClient( pRespHistory );

    // Отправляем ПРЕПОДАВАТЕЛЮ. Если они конечно в сети.
    sendToTeacher( db,
                   queryInfo,
                   idUserLab,
                   pRespHistory );
}


// ЗАРАНЕЕ предполагается, что структура с историей сформирована,
// т.к. сперва мы ее отправляем СТУДЕНТУ.
void ReqCode::sendToTeacher( const OurDataBase &db,
                             OurQueryInfo &queryInfo,
                             ID_USER_LAB idUserLab,
                             RespHistory *pRespHistory ) {


    // если список id преподов еще пуст, то получаем его.
    if ( m_IdTeacherList.empty() ) {

        m_IdTeacherList = getIdTeacherList( db,
                                            queryInfo,
                                            idUserLab );
    }

    for ( int i = 0;
          i < m_IdTeacherList.size();
          i++ ) {

        ID_USER idTeacher = m_IdTeacherList[ i ];
        TeacherRespHistory *pTeacherResp = new TeacherRespHistory( ResponseReciever::TEACHER );
        pTeacherResp -> setIdClient( idTeacher );

        // Устанавливаем ID студента и буфер в котором записана ИСТОРИЯ
        pTeacherResp -> addStudentHistory( pRespHistory -> getIdClient(),
                                           pRespHistory -> getHistoryList(),
                                           pRespHistory -> getAboutHistoryList() );
        pTeacherResp -> writeInStreamBuffer();
        emit sendResponseClient( pTeacherResp );
    }
}



void ReqCode::sendAboutHistory( const OurDataBase &db,
                                const ID_USER_LAB &idUserLab,
                                const int &idHistory,
                                const int &idAboutHistory,
                                const StepType &idStep,
                                TestResultsInfo &testResultsInfo,
                                OurQueryInfo &queryInfo ) {

    RespHistory *pRespHistory = new RespHistory( static_cast < ResponseReciever > ( m_RequestSender ) );

    AboutHistory aboutHistory;
    aboutHistory.setIdHistory( idHistory );
    aboutHistory.setIdAboutHistory( idAboutHistory );
    aboutHistory.setResult( testResultsInfo.getTestResult() );
    aboutHistory.setStepType( idStep );

    TestResult idResult = testResultsInfo.getTestResult();
    TableResult resultTable( db );
    QString textResult = resultTable.getResult( idResult, queryInfo );
    aboutHistory.setTextResult( textResult );

    TableStep stepTable( db );
    stepTable.getName( idStep, queryInfo );
    aboutHistory.setDescription( stepTable.getName( idStep, queryInfo ) );

    //устанавливаем также время и память
    aboutHistory.setMemory( testResultsInfo.getPeakMemory() );
    aboutHistory.setTime( testResultsInfo.getTimePassed() );

    pRespHistory -> addAboutHistory( aboutHistory );
    pRespHistory -> setIdClient( m_IdClient );
    pRespHistory -> setResponseClientType( ResponseClientType::HISTORY );
    pRespHistory -> writeInStreamBuffer();

    emit sendResponseClient( pRespHistory );

    // Отправляем ПРЕПОДАВАТЕЛЯ. Если они конечно в сети.
    sendToTeacher( db,
                   queryInfo,
                   idUserLab,
                   pRespHistory );
}


QList < ID_USER > ReqCode::getIdTeacherList( const OurDataBase &db,
                                             OurQueryInfo &queryInfo,
                                             ID_USER_LAB idUserLab ) {

    UniversalTable table( db );
    // узнаем вариант работы по idUserLab
    ID_VARIANT idVariant = table.getId( queryInfo,
                                     TABLE_NAME_FOR_USER_LAB,
                                     ID_VARIANT_FIELD_TITLE,
                                     ID_USER_LAB_FIELD_TITLE,
                                     idUserLab
                                    );
    // узнаем id лабы по известному варианту
    ID_LAB idLab = table.getId( queryInfo,
                                 VARIANT_LAB_TABLE_NAME,
                                 ID_LAB_FIELD_TITLE,
                                 ID_VARIANT_FIELD_TITLE,
                                 idVariant
                                );

    // Узнаем номер дисциплины по номеру лабы.
    ID_DISCIPLINE idDiscipline = table.getId( queryInfo,
                                             TABLE_NAME_LAB,
                                             FIELD_TITLE_ID_DISCIPLINE,
                                             ID_LAB_FIELD_TITLE,

                                             idLab
                                            );

    QList < ID_USER > idTeacherList = table.getListId( queryInfo,
                                                       TABLE_NAME_TEACHER_DISCIPLINE,
                                                       FIELD_TITLE_ID_TEACHER,
                                                       FIELD_TITLE_ID_DISCIPLINE,
                                                       idDiscipline
                                                     );

    return idTeacherList;
}

void ReqCode::readStream( QDataStream &stream ) {

    stream >> m_IdUserLab >>
              m_FileZipBuffer;
}


ResponseClient* ReqCode::doRequest( const OurDataBase &db,
                                    OurQueryInfo &queryInfo ) {

    qDebug() << "ReqCode - " << GetThreadId( GetCurrentThread() );

    TableUserLab userLabTable( db );
    bool result = userLabTable.idUserLabExist( m_IdUserLab, m_IdClient, queryInfo );
    ifBundleThenAddBugAndReturnMessage( queryInfo, "doRequest", 270, " m_IdUserLab = " + QString::number( m_IdUserLab ) +
                                        " m_IdClient = " + QString::number( m_IdClient ));

    if ( !result ) {
        m_BugReport.addBug( db, "не найден idUserLab", m_ClassName, "doRequest", NULL, 239, " m_IdUserLab = " + QString::number( m_IdUserLab ) +
                    " m_IdClient = " + QString::number( m_IdClient ), queryInfo );

        return m_BugReport.getDefaultMessage();
    }

    QString strIdUserLab = QString::number( m_IdUserLab );

    TestDirectory directory;
    QString directoryName = directory.createFolder( strIdUserLab, m_DirectoryTest );

    if ( directoryName.isEmpty() ) {
        m_BugReport.addBug( db,
                            "Ошибка создания папки для тестирования " + strIdUserLab, m_ClassName, "doRequest",
                            NULL, 274, " strIdUserLab = " + strIdUserLab, queryInfo );

        return m_BugReport.getDefaultMessage();
    }


    m_DirectoryTest = m_DirectoryTest + "/" + directoryName;

    ZipArchiver archiver;
    if ( archiver.unpackIntoSpecifyPath( m_FileZipBuffer, m_DirectoryTest ) ) {
        CodeCompile compileStage;

        if ( compileStage.compile( m_DirectoryTest, strIdUserLab ) != COMPILATION_COMPLETED ) {
            compilationError( db, m_DirectoryTest, queryInfo );
        }
        else {
            testingProgram( db, m_DirectoryTest, compileStage.getExe(), queryInfo );
        }

    }

    return NULL;
}


void ReqCode::setDirectoryTest( const QString &directoryTest ) {

    m_DirectoryTest = directoryTest;
}


