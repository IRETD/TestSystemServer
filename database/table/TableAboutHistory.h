#ifndef TABLEABOUTHISTORY_H
#define TABLEABOUTHISTORY_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
#include <data/history/AboutHistory.h>
#include <MacroDefinitions/Data/Test/StepType.h>
#include <MacroDefinitions/Data/Test/TestResult.h>
#include <code/Test/TestResultsInfo.h>

//!!
//class AboutHistory;

class TableAboutHistory {

    OurDataBase m_Db;

    enum class Field {

        STEP = 1,
        RESULT
    };

    QList < AboutHistory > getAboutHistoryList( const int &idHistory,
                                                Field field,
                                                OurQueryInfo &queryInfo );
public:
    TableAboutHistory( const OurDataBase &db );


    int insert( const int &idHistory,
                const StepType &idStep,
                TestResultsInfo &testResultsInfo,
                OurQueryInfo &queryInfo );
    int insert( const int &idHistory,
                const StepType &idStep,
                TestResult &testResult,
                OurQueryInfo &queryInfo );
    void updateResult( const int &idAboutHistory,
                       TestResultsInfo &testResultsInfo,
                       OurQueryInfo &queryInfo );
    //QList < AboutHistory > getDescriptionStepList( const int &idHistory, OurQueryInfo &queryInfo );
    //QList < AboutHistory > getDescriptionResultList( const int &idHistory, OurQueryInfo &queryInfo );
    QList < AboutHistory > getAboutHistoryList( const int &idHistory,
                                                OurQueryInfo &queryInfo );
};

#endif
