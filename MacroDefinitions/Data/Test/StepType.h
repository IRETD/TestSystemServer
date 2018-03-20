#ifndef STEPTYPE_H
#define STEPTYPE_H

#include <QDataStream>

enum class StepType {

    UNDEFINED = 0,
    //СООТВЕТСТВИЕ В БАЗЕ ДАННЫХ - СПРАВОЧНИК
    COMPILATION = 1,
    TEST = 2,
    ANALYZE = 3
};

QDataStream& operator >> ( QDataStream &out,
                           StepType &value );

QDataStream& operator << ( QDataStream &out,
                           StepType &value );


#endif
