#-------------------------------------------------
#
# Project created by QtCreator 2013-09-05T18:42:56
#
#-------------------------------------------------

QT       += core network testlib sql gui-private xml

QT       += gui

CONFIG += debug

DEFINES += IT_IS_SERVER


QMAKE_CXXFLAGS += -std=gnu++11


TARGET = testSystem
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    \
    server/Server.cpp \
    server/listen/ClientListen.cpp \
    server/service/ClientService.cpp \
    server/service/StreamReader.cpp \
    server/client/Client.cpp \
    server/service/BlackList.cpp \
    server/service/IdleList.cpp \
    server/service/IdCreator.cpp \
    server/client/ClientSettings.cpp \
    server/client/ClientRequestStatistics.cpp \
    \
    queue/OurQueue.cpp \
    \
    event/OurEvent.cpp \
    \
    response/client/subclasses/Stage.cpp \
    response/client/subclasses/LabList.cpp \
    response/client/subclasses/Restriction.cpp \
    response/client/ResponseClient.cpp \
    response/client/RespAuth.cpp \
    response/client/RespCode.cpp \
    response/server/ResponseServer.cpp \
    response/server/RespDefaultClientSettings.cpp \
    request/server/RequestServer.cpp \
    \
    thread/OurThreads.cpp \
    \
    database/OurDataBase.cpp \
    database/table/TableHistory.cpp \
    database/table/TableUser.cpp \
    database/table/TableAboutHistory.cpp \
    database/table/TableTest.cpp \
    database/table/TableStep.cpp \
    database/table/TableResult.cpp \
    database/table/TableUserLab.cpp \
    database/table/TableVariantLab.cpp \
    database/table/TableResponseArchive.cpp \
    database/table/TableTestInput.cpp \
    database/table/TableTestOutput.cpp \
    database/OurDataBaseKeepConnection.cpp \
    \
    thread/MyMutex.cpp \
    \
    log/MyLog.cpp \
    \
    code/CodeTest.cpp \
    code/TestData.cpp \
    code/TestDirectory.cpp \
    code/CodeCompile.cpp \
    \
    request/RequestExecute.cpp \
    request/client/ReqAuth.cpp \
    request/client/ReqCode.cpp \
    request/client/ReqGetResponseArchive.cpp \
    request/server/ReqPutResponseArchive.cpp \
    request/client/RequestClient.cpp \
    request/Request.cpp \
    request/RequestFactory.cpp \
    \
    zip/ZipArchiver.cpp \
    server/ServerSettings.cpp \
    response/server/RespServerSettings.cpp \
    response/ResponseFactory.cpp \
    response/server/RespAuthClient.cpp \
    database/table/TableAuthorizationHistory.cpp \
    response/client/RespLeave.cpp \
    database/table/TableMessageCatalogForClient.cpp \
    response/client/RespMessage.cpp \
    database/table/TableBugList.cpp \
    bug/BugReport.cpp \
    request/server/ReqServerSettings.cpp \
    database/table/TableServerSettings.cpp \
    database/table/TableClientBufferSettings.cpp \
    database/table/TableRequestSettings.cpp \
    database/table/TablePeerAddressBlackList.cpp \
    database/table/TableIdleSettings.cpp \
    database/OurQueryInfo.cpp \
    server/service/RequestReadInfo.cpp \
    request/client/ReqLabList.cpp \
    database/table/TableDiscipline.cpp \
    database/table/TableLab.cpp \
    data/history/History.cpp \
    data/history/AboutHistory.cpp \
    request/client/ReqHistory.cpp \
    response/client/RespHistory.cpp \
    response/client/RespDisciplineTask.cpp \
    code/Test/TestParamLimits.cpp \
    code/Test/TestResultsInfo.cpp \
    code/Test/TestResultParser.cpp \
    code/Test/TestRun.cpp \
    code/Anazyler/StaticAnalyzer.cpp \
    code/Anazyler/ParserStaticAnalyzer.cpp \
    code/Anazyler/AnalyzeWorker.cpp \
    database/table/TableStaticAnalyzer.cpp \
    database/table/TableAboutStaticAnalyzer.cpp \
    request/client/ReqAnalyze.cpp \
    response/client/RespAnalyze.cpp \
    database/table/TableAdditionalColumnAboutHistory.cpp \
    database/table/TableLabGroop.cpp \
    database/table/UniversalTable.cpp \
    data/lab/Discipline.cpp \
    response/teacher/TeacherRespDisciplineTask.cpp \
    request/teacher/TeacherReqLabList.cpp \
    data/taskgroup/TaskGroup.cpp \
    ../../TestTeacher/Data/Group/Group.cpp \
    ../../TestTeacher/Data/Group/Student/Student.cpp \
    ../../TestTeacher/MyStorageType/DoubleKeyContainer.cpp \
    ../../TestTeacher/MyStorageType/DoubleKeyWithContainerValueContainer.cpp \
    ../../TestTeacher/MyStorageType/SingleKeyContainer.cpp \
    ../../TestTeacher/MyStorageType/SingleKeyWithContainerValueContainer.cpp \
    ../../TestTeacher/MyStorageType/TripleKeyContainer.cpp \
    MacroDefinitions/Data/Test/TestResult.cpp \
    ../../TestTeacher/Data/Task/Task.cpp \
    data/lab/StudentTask.cpp \
    MacroDefinitions/Data/Test/StepType.cpp \
    request/teacher/TeacherReqHistory.cpp \
    response/teacher/TeacherRespHistory.cpp \
    response/teacher/struct/StudentRespHistory.cpp


HEADERS += \
    \
    server/Server.h \
    server/listen/ClientListen.h \
    server/service/ClientService.h \
    server/service/StreamReader.h \
    server/client/Client.h \
    server/service/BlackList.h \
    server/service/IdleList.h \
    server/service/IdCreator.h \
    server/client/ClientSettings.h \
    \
    queue/OurQueue.h \
    \
    event/OurEvent.h \
    \
    response/client/subclasses/Stage.h \
    response/client/subclasses/LabList.h \
    response/client/subclasses/Restriction.h \
    response/client/ResponseClient.h \
    response/client/RespAuth.h \
    response/client/RespAddEmail.h \
    response/client/RespCode.h \
    response/server/ResponseServer.h \
    response/server/RespDefaultClientSettings.h \
    response/client/ResponseClientName.h \
    \
    thread/OurThreads.h \
    \
    database/OurDataBase.h \
    database/table/TableHistory.h \
    database/table/TableUser.h \
    database/table/TableAboutHistory.h \
    database/table/TableTest.h \
    database/table/TableStep.h \
    database/table/TableResult.h \
    database/table/TableUserLab.h \
    database/table/TableVariantLab.h \
    database/table/TableResponseArchive.h \
    database/table/TableTestInput.h \
    database/table/TableTestOutput.h \
    database/OurDataBaseKeepConnection.h \
    \
    thread/MyMutex.h \
    \
    log/MyLog.h \
    \
    code/CodeTest.h \
    code/TestData.h \
    code/TestDirectory.h \
    code/CodeCompile.h \
    \
    request/RequestExecute.h \
    request/client/ReqAuth.h \
    request/client/ReqCode.h \
    request/client/ReqGetResponseArchive.h \
    request/server/ReqPutResponseArchive.h \
    request/client/RequestClient.h \
    request/Request.h \
    request/RequestFactory.h \
    \
    zip/ZipArchiver.h \
    request/server/RequestServer.h \
    server/client/ClientRequestStatistics.h \
    server/ServerSettings.h \
    response/server/ResponseServerName.h \
    response/server/RespServerSettings.h \
    request/client/RequestClientName.h \
    request/server/RequestServerName.h \
    response/ResponseFactory.h \
    response/server/RespAuthClient.h \
    database/table/TableAuthorizationHistory.h \
    response/client/RespLeave.h \
    database/table/TableMessageCatalogForClient.h \
    response/client/RespMessage.h \
    database/table/TableBugList.h \
    bug/BugReport.h \
    request/server/ReqServerSettings.h \
    database/table/TableServerSettings.h \
    database/table/TableClientBufferSettings.h \
    database/table/TableRequestSettings.h \
    database/table/TablePeerAddressBlackList.h \
    database/table/TableIdleSettings.h \
    database/OurQueryInfo.h \
    server/service/RequestReadInfo.h \
    request/client/ReqLabList.h \
    database/table/TableDiscipline.h \
    database/table/TableLab.h \
    data/history/History.h \
    data/history/AboutHistory.h \
    request/client/ReqHistory.h \
    response/client/RespHistory.h \
    MacroDefinitions/IdentifierMessage.h \
    MacroDefinitions/Request/Client/AuthResult.h \
    response/client/RespDisciplineTask.h \
    MacroDefinitions/Data/Test/TestResult.h \
    MacroDefinitions/Data/Test/IdColumnAboutHistory.h \
    code/Test/TestParamLimits.h \
    code/Test/TestResultsInfo.h \
    code/Test/TestResultParser.h \
    code/Test/TestRun.h \
    MacroDefinitions/code/ProcessResult.h \
    MacroDefinitions/code/TestFilesName.h \
    MacroDefinitions/code/Test/TextOfTestResult.h \
    code/Anazyler/StaticAnalyzer.h \
    MacroDefinitions/code/Analyzer/TypeStaticAnalyzer.h \
    MacroDefinitions/code/Analyzer/TypeStaticAnalyzerText.h \
    code/Anazyler/ParserStaticAnalyzer.h \
    MacroDefinitions/code/Analyzer/ParserTagNames.h \
    code/Anazyler/AnalyzeWorker.h \
    database/table/TableStaticAnalyzer.h \
    MacroDefinitions/code/Analyzer/AnalyzeFileName.h \
    database/table/TableAboutStaticAnalyzer.h \
    request/client/ReqAnalyze.h \
    response/client/RespAnalyze.h \
    MacroDefinitions/database/table/TableAboutHistory/AdditionalColumnType.h \
    database/table/TableAdditionalColumnAboutHistory.h \
    data/Groop/IdLabGroopIdGroop.h \
    database/table/TableLabGroop.h \
    database/table/UniversalTable.h \
    response/client/subclasses/lablist.h \
    response/client/RespAddEmaill.h \
    response/client/resplabhistory.h \
    server/service/requestreadinfo.h \
    MacroDefinitions/Request/Client/RequestSender.h \
    MacroDefinitions/Request/Client/DefinitionsForReqAuth.h \
    data/lab/Discipline.h \
    response/client/subclasses/lablist.h \
    server/service/requestreadinfo.h \
    response/client/subclasses/lablist.h \
    server/service/requestreadinfo.h \
    MacroDefinitions/Request/Client/DefinitionsForReqLabList.h \
    MacroDefinitions/Response/ResponseReciever.h \
    response/teacher/TeacherRespDisciplineTask.h \
    request/teacher/TeacherReqLabList.h \
    MacroDefinitions/Request/Teacher/DefinitionsForTeacherReqLabList.h \
    response/client/subclasses/lablist.h \
    server/service/requestreadinfo.h \
    ../../TestTeacher/Data/Group/Group.h \
    ../../TestTeacher/Data/Group/Student/Student.h \
    ../../TestTeacher/MyStorageType/DoubleKeyContainer.h \
    ../../TestTeacher/MyStorageType/DoubleKeyWithContainerValueContainer.h \
    ../../TestTeacher/MyStorageType/SingleKeyContainer.h \
    ../../TestTeacher/MyStorageType/SingleKeyWithContainerValueContainer.h \
    ../../TestTeacher/MyStorageType/TripleKeyContainer.h \
    data/taskgroup/TaskGroup.h \
    ../../TestTeacher/Data/Task/Task.h \
    data/lab/StudentTask.h \
    MacroDefinitions/Data/Test/StepType.h \
    MacroDefinitions/Data/Student/IdColumnStudentList.h \
    request/teacher/TeacherReqHistory.h \
    TypeDefinitions/BaseTypeDefinitions.h \
    response/teacher/TeacherRespHistory.h \
    response/teacher/struct/StudentRespHistory.h \
    MacroDefinitions/CilentType.h \
    MacroDefinitions/Data/Test/IdColumnHistory.h

QTPLUGIN += QSQLMYSQL

