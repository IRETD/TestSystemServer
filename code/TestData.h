//************************************************************************
// Класс хранения тестовых данных для теструемой программы
//
//************************************************************************

#ifndef TESTDATA_H
#define TESTDATA_H

#include <QStringList>

class TestData {

    QStringList m_InputDataList;
    QStringList m_OutputDataList;

public:
    TestData();

    QStringList getInputDataList();
    QStringList getOutputDataList();
    void addInputData( const QString &inputData );
    void addOutputData( const QString &outputData );
};

#endif
