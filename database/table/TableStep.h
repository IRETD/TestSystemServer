#ifndef TABLESTEP_H
#define TABLESTEP_H

#include <database/OurDataBase.h>
#include <database/OurQueryInfo.h>
#include <MacroDefinitions/Data/Test/StepType.h>

class TableStep {

    OurDataBase m_Db;

public:
    TableStep( const OurDataBase &db );

    QString getName( const StepType &idStep, OurQueryInfo &queryInfo );
};

#endif
