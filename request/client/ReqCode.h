#ifndef REQCODE_H
#define REQCODE_H

#include <request/client/RequestClient.h>
#include <response/client/ResponseClient.h>
#include <QObject>
#include <code/TestData.h>
#include <response/client/RespCode.h>
#include <response/client/RespMessage.h>
#include <MacroDefinitions/Data/Test/TestResult.h>
#include <MacroDefinitions/Data/Test/StepType.h>
#include <code/Test/TestResultsInfo.h>
#include <TypeDefinitions/BaseTypeDefinitions.h>

class RespHistory;

enum {

    FOLDER = 1,
    CODE_FILE = 2,

    UNKNOWN_INPUT_DATA_FROM_CLIENT = 1
};


class ReqCode : public QObject,
                public RequestClient {

    Q_OBJECT

private:
    // Список id преподов, которым следует СРАЗУ отправлять результаты.
    QList < ID_USER > m_IdTeacherList;

    quint32 m_IdUserLab;
    QByteArray m_FileZipBuffer;
    QString m_DirectoryTest;
    QList < TestData > getTestDataList( const OurDataBase &db, const int &idVariant, OurQueryInfo &queryInfo );

    void compilationError( const OurDataBase &db, const QString &pathCodeFolder, OurQueryInfo &queryInfo );
    void compilationComplete( const OurDataBase &db, OurQueryInfo &queryInfo );
    void testingProgram( const OurDataBase &db, const QString &pathCodeFolder, const QString &exeFile, OurQueryInfo &queryInfo );
    TestResult analyze( const OurDataBase &db,
                        quint32 idAboutHistory,
                        const QString &pathCodeFolder,
                        OurQueryInfo &queryInfo );

    void sendHistory( const OurDataBase &db,
                      const ID_TYPE &idHistory,
                      const ID_TYPE &idUserLab,
                      const TestResult &idResult,
                      OurQueryInfo &queryInfo,
                      const QDateTime &dateTime = QDateTime() );

    // метод отправки истории ПРЕПОДАВАТЕЛЮ
    // Предполагается, что отправляется СОВМЕСТНО СО СТУДЕНТОМ.
    // Поэтому информация берется из запроса составленного ДЛЯ СТУДЕНТА!
    void sendToTeacher( const OurDataBase &db,
                        OurQueryInfo &queryInfo,
                        ID_USER_LAB idUserLab,
                        RespHistory *pRespHistory );

    /*
    QString getColumnNameForAboutTest( const OurDataBase &db,
                                       const ColumnNameAboutHistory &idAboutHistoryTable,
                                       OurQueryInfo &queryInfo);
                                       */

    void sendAboutHistory( const OurDataBase &db,
                           const ID_USER_LAB &idUserLab,
                           const int &idHistory,
                           const int &idAboutHistory,
                           const StepType &idStep,
                           TestResultsInfo &testResultsInfo,
                           OurQueryInfo &queryInfo );

    QList < ID_USER > getIdTeacherList( const OurDataBase &db,
                                        OurQueryInfo &queryInfo,
                                        ID_USER_LAB idUserLab );


signals:
    void sendResponseClient( ResponseClient* );

public:
    ReqCode();

    ResponseClient *doRequest( const OurDataBase &db, OurQueryInfo &queryInfo );

    void setDirectoryTest( const QString &directoryTest );
    QString getDirectoryTest() const;

    void readStream( QDataStream &stream );
};

#endif
