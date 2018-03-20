#ifndef TASK_GROUP_H
#define TASK_GROUP_H


/*
 * Хранит в себе три поля из таблицы lab_groop
 * В общем - предназначена для хранения связи между лабораторными и группами
 * имеющимися в БД
 * Без этой структуры НЕВОЗМОЖНО определить, какие группы назначены на лабораторную
 *
 * m_IdLabGroup - идентифицирует связь id_lab с id_groop.
 * m_IdLab - id лабораторной.
 * m_IdGroop - id группы.
 */

#include <QDataStream>

#ifndef IT_IS_SERVER
    #include <../TestSystem/TestSystem/TypeDefinitions/BaseTypeDefinitions.h>
#else
    #include <TypeDefinitions/BaseTypeDefinitions.h>
#endif

struct TaskGroup {


    ID_LAB_GROOP m_IdLabGroup;
    ID_LAB m_IdTask;
    ID_GROOP m_IdGroup;

    TaskGroup() {


    }

    TaskGroup( ID_LAB_GROOP idLabGroop,
               ID_LAB idTask,
               ID_GROOP idGroup ) {

        m_IdLabGroup = idLabGroop;
        m_IdTask = idTask;
        m_IdGroup = idGroup;
    }

    TaskGroup ( QPair < int,
                        QPair < int,
                                int >
                      > pair ) {

        m_IdLabGroup = pair.first;
        m_IdTask = pair.second.first;
        m_IdGroup = pair.second.second;
    }


    friend QDataStream& operator >>( QDataStream &stream,
                                     TaskGroup &value );
    friend QDataStream& operator << ( QDataStream &stream,
                                      TaskGroup &value );
};


#endif
