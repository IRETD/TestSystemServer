#include "TestData.h"


TestData::TestData() {
}


QStringList TestData::getInputDataList() {

    return m_InputDataList;
}


QStringList TestData::getOutputDataList() {

    return m_OutputDataList;
}


void TestData::addInputData( const QString &inputData ) {

    m_InputDataList.append( inputData );
}


void TestData::addOutputData( const QString &outputData ) {

    m_OutputDataList.append( outputData );
}
