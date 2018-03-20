#ifndef TESTRESULT_H
#define TESTRESULT_H

#include <QDataStream>

enum class TestResult {

    UNDEFINED = 0,
    //СООТВЕТСТВИЕ С БД - СПРАВОЧНИК
    DONE = 1,
    FAIL_TEST = 2,
    TESTING = 3,
    SOMETHING_WRONG = 4,
    TIME_LIMIT = 5,
    MEMORY_LIMIT = 6
};

QDataStream& operator >>( QDataStream &out,
                          TestResult &value );
QDataStream& operator <<( QDataStream &out,
                          TestResult &value );

#endif // TESTRESULT_H
