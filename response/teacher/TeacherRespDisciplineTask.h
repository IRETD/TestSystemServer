#ifndef TEACHERRESPLABLIST_H
#define TEACHERRESPLABLIST_H

#include <request/teacher/TeacherReqLabList.h>
#include <response/client/RespDisciplineTask.h>

#include <request/client/ReqLabList.h>
#include "../../TestTeacher/Data/Group/Group.h"
#include <data/taskgroup/TaskGroup.h>
#include <../../TestTeacher/Data/Task/Task.h>
#include <../../TestTeacher/MyStorageType/SingleKeyWithContainerValueContainer.h>
#include <../../TestTeacher/MyStorageType/DoubleKeyContainer.h>
#include <../../TestTeacher/MyStorageType/SingleKeyContainer.h>

#include <data/history/History.h>
#include <data/history/AboutHistory.h>

typedef Task TeacherTask;
class AboutHistory;

class TeacherRespDisciplineTask : public RespDisciplineTask {

    QList < TaskGroup > m_TaskGroupList;


    /*

    // храним группы по их id
    // опять же, для быстрого поиска
    SingleKeyContainer < ID_GROOP,
                         Group > m_IdGroopGroopContainer;
    // привязка списка студентов к конекртрной группе
    // для ускорения поиска
    SingleKeyWithContainerValueContainer < ID_GROOP,
                                           Student > m_IdGroopStudentList;

    */

    SingleKeyWithContainerValueContainer < ID_STUDENT,
                                           History > m_IdStudent_HistoryList_Container;
    SingleKeyWithContainerValueContainer < ID_STUDENT,
                                           AboutHistory > m_IdStudent_AboutHistoryList_Container;

    DoubleKeyContainer < ID_LAB_GROOP,
                         ID_STUDENT,
                         ID_USER_LAB > m_IdLabGroup_IdStudent_IdUserLab_Container;

                        /*QPair < ID_USER_LAB_LIST,
                                 ID_LAB_LIST >
                       > m_IdStudent_IdUserLabIdLabPairOfList_Container;*/


    QList < Group > m_GroupList;

    void writeLabsInStream();
    void writeTaskGroupInStream();
    void writeGroupsInStream();
    void writeHistoryInStream();
    void writeIdUserLabInStream();

public:
    TeacherRespDisciplineTask( ResponseReciever responseReciever );

    void addTaskGroup( TaskGroup taskGroup );
    void addTaskGroupList ( QList < TaskGroup > taskGroupList );

    void addGroup( QList < Group > groupList );

    void addHistoryToStudent( ID_STUDENT idStudent,
                              QList < History > historyList );
    void addAboutHistoryToStudent( ID_STUDENT idStudent,
                                   QList < AboutHistory > aboutHistoryList );

    void addIdUserLabToIdStudentByIdLabGroup( ID_LAB_GROOP idLabGroup,
                                              ID_STUDENT idStudent,
                                              ID_USER_LAB idUserLab );

    // Получаем значение из УЖЕ существующего списка.
    ID_LAB_GROOP getIdLabGroopFromTaskGroupList( ID_GROOP idGroup,
                                                 ID_LAB idLab);

    /*
    void addStudentIdUserLabListToIdLabList( ID_STUDENT idStudent,
                                             ID_USER_LAB_LIST idUserLabList,
                                             ID_LAB_LIST idLabList );
    */

    /// Скорее всего этот метод не нужен
    /*
    void setGroup( ID_GROOP idGroup,
                   Group group );
    /// Скорее всего этот метод не нужен
    void setStudentList( ID_GROOP idGroup,
                         QList < Student > studentList );
    */

    QList < Group > getGroupList();
    void writeInStreamBuffer();
};

#endif // TEACHERRESPLABLIST_H
