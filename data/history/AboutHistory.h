#ifndef ABOUTHISTORY_H
#define ABOUTHISTORY_H

#include <QString>
//#include <data/history/History.h>
// Если подключение идет из проекта клиента препода
#ifdef IT_IS_TEACHER_CLIENT
#include <../TestSystem/TestSystem/MacroDefinitions/Data/Test/TestResult.h>
#include <../TestSystem/TestSystem/MacroDefinitions/Data/Test/StepType.h>
#else
#include <MacroDefinitions/Data/Test/TestResult.h>
#include <MacroDefinitions/Data/Test/StepType.h>
#endif

class History;

class AboutHistory {

    int m_IdAboutHistory;
    int m_IdHistory;
    TestResult m_Result;
    StepType m_StepType;
    QString m_Description;
    QString m_TextResult;
    QString m_Memory;
    QString m_Time;
    QString m_AdditionalColumn;

public:
    AboutHistory();

    friend QDataStream& operator >> ( QDataStream &stream,
                                      AboutHistory &value );
    friend QDataStream& operator << ( QDataStream &stream,
                                      AboutHistory &value );

    void setIdAboutHistory( const int &idAboutHistory );
    void setResult( const TestResult &result );
    void setIdHistory( const int &idHistory );
    void setTextResult( const QString &textResult );
    void setDescription( const QString &description );
    void setMemory( QString memory );
    void setTime( QString time );
    void setStepType( StepType stepType );
    //void setColumnName( const QString &columnName );
    void setAdditionalColumn( QString additionalColumn );

    int getIdHistory() const;
    quint32 getIdAboutHistory() const;
    TestResult getResult() const;
    StepType getStepType();
    QString getTextResult() const;
    QString getMemory();
    QString getTime();
    QString getDescription() const;
    QString getAdditionalColumn();
    //QString getColumnName() const;
};

#endif // ABOUTHISTORY_H
