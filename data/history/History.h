#ifndef HISTORY_H
#define HISTORY_H

#include <QString>
#include <QDateTime>

#ifdef IT_IS_TEACHER_CLIENT
    #include <../TestSystem/TestSystem/MacroDefinitions/Data/Test/TestResult.h>
#else
    #ifdef IT_IS_STUDENT_CLIENT
        #include <../TestSystem/TestSystem/MacroDefinitions/Data/Test/TestResult.h>
    #else
        #include <MacroDefinitions/Data/Test/TestResult.h>
    #endif
#endif


class History {

    int m_IdUserLab;
    int m_IdHistory;
    TestResult m_Result;
    QString m_TextResult;
    QDateTime m_DateHistory;

public:
    History();

    void setIdHistory( const int &idHistory );
    void setTextResult( const QString &textResult );
    void setResult( const TestResult &result );
    void setDateHistory( const QDateTime &dateHistory );
    void setIdUserLab( const int idUserLab );

    friend QDataStream& operator >> ( QDataStream &stream,
                                      History &value );
    friend QDataStream& operator << ( QDataStream &stream,
                                      History &value );

    int getIdHistory() const;
    QString getTextResult() const;
    TestResult getResult() const;
    QDateTime getDateHistory() const;
    int getIdUserLab() const;
};

#endif // HISTORY_H
