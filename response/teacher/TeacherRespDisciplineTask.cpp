#include "TeacherRespDisciplineTask.h"


void TeacherRespDisciplineTask::writeTaskGroupInStream() {


    writeListDataInStream( m_TaskGroupList );
}


void TeacherRespDisciplineTask::writeGroupsInStream() {

    writeListDataInStream( m_GroupList );
}


void TeacherRespDisciplineTask::writeHistoryInStream() {

    m_StreamBuffer << m_IdStudent_HistoryList_Container <<
                      m_IdStudent_AboutHistoryList_Container;

}


void TeacherRespDisciplineTask::writeIdUserLabInStream() {


    m_StreamBuffer << m_IdLabGroup_IdStudent_IdUserLab_Container;
}



// Оставим это пока что ТАК
// Вскоре если понадобится - исправлю.
/// P.S. Просто необходимо внести различия на уровне классов
/// меджу Task студента и Task препода
void TeacherRespDisciplineTask::writeLabsInStream() {

    int labCount = m_LabList.size();
    m_StreamBuffer << labCount;
    for ( int i = 0;
          i < labCount;
          i++ ) {
        Lab lab = m_LabList.at( i );
        ///ОСНОВНОЕ ОТЛИЧИЕ ОТ СТУДЕНТА - НЕ ПИШЕМ idUserLab
        /// Дабы не путаться в последующем
        /// Поэтому и перегрузил так :)
        m_StreamBuffer << lab.getIdDiscipline() <<
                          lab.getIdLab() <<
                          lab.getName() <<
                          lab.getPurpose() <<
                          lab.getDesiredDate() <<
                          lab.getCriticalDate();
    }
}



TeacherRespDisciplineTask::TeacherRespDisciplineTask( ResponseReciever responseReciever ) : RespDisciplineTask( responseReciever ) {
}


void TeacherRespDisciplineTask::addTaskGroup( TaskGroup taskGroup ) {

    m_TaskGroupList.append( taskGroup );
}


void TeacherRespDisciplineTask::addTaskGroupList( QList < TaskGroup > taskGroupList ) {

    m_TaskGroupList.append( taskGroupList );
}


void TeacherRespDisciplineTask::addGroup( QList < Group > groupList ) {

    m_GroupList.append( groupList );
}


void TeacherRespDisciplineTask::addHistoryToStudent( ID_STUDENT idStudent,
                                                     QList < History > historyList ) {

    m_IdStudent_HistoryList_Container.addValue( idStudent,
                                                historyList );
}


void TeacherRespDisciplineTask::addAboutHistoryToStudent( ID_STUDENT idStudent,
                                                          QList < AboutHistory > aboutHistoryList ) {

    m_IdStudent_AboutHistoryList_Container.addValue( idStudent,
                                                     aboutHistoryList );
}

void TeacherRespDisciplineTask::addIdUserLabToIdStudentByIdLabGroup( ID_LAB_GROOP idLabGroup,
                                                                     ID_STUDENT idStudent,
                                                                     ID_USER_LAB idUserLab ) {

    m_IdLabGroup_IdStudent_IdUserLab_Container.addValue( idLabGroup,
                                                         idStudent,
                                                         idUserLab );
}


ID_LAB_GROOP TeacherRespDisciplineTask::getIdLabGroopFromTaskGroupList( ID_GROOP idGroup,
                                                                        ID_LAB idLab ) {

    quint32 size = m_TaskGroupList.size();
    ID_LAB_GROOP idLabGroup = -1;
    for ( int i = 0;
          i < size;
          i++ ) {

        if ( m_TaskGroupList[ i ].m_IdGroup == idGroup &&
             m_TaskGroupList[ i ].m_IdTask == idLab ) {

            idLabGroup = m_TaskGroupList[ i ].m_IdLabGroup;
            break;

        }
    }

    return idLabGroup;
}


/*
// Сопоставление элементов из списка idUserLab к idLab
void TeacherRespDisciplineTask::addStudentIdUserLabListToIdLabList( ID_STUDENT idStudent,
                                                                    ID_USER_LAB_LIST idUserLabList,
                                                                    ID_LAB_LIST idLabList ) {

    QPair < ID_USER_LAB_LIST,
            ID_LAB_LIST > pair;
    pair.first = idUserLabList;
    pair.second = idLabList;
    m_IdStudent_IdUserLabIdLabPairOfList_Container.addValue( idStudent,
                                                             pair );
}
*/

QList < Group > TeacherRespDisciplineTask::getGroupList()  {

    return m_GroupList;
}


/*
void TeacherRespDisciplineTask::setGroup( ID_GROOP idGroup,
                                          Group group )  {

    m_IdGroopGroopContainer.addValue( idGroup,
                                      group );
}

void TeacherRespDisciplineTask::setStudentList( quint32 idGroup,
                                                QList < Student > studentList ) {

    m_IdGroopStudentList.addValue( idGroup,
                                   studentList );
}
*/


void TeacherRespDisciplineTask::writeInStreamBuffer() {

    clearStream();
    streamProlog( ResponseClientType::DISCIPLINE_TASK );

    // Пишем дисицплины
    writeDisciplinesInStream();
    // Пишем лабы.
    writeLabsInStream();
    // Пишем соотв групп к каждой из лабораторных
    writeTaskGroupInStream();
    // Пишем сами группы.
    // Группы это также и сами СТУДЕНТЫ.
    writeGroupsInStream();

    // Пишем ИСТОРИИ сдач студентами


    writeHistoryInStream();
    // Пишем соотв idUserLab для КАЖДОГО студента
    // в idLabGroup.
    writeIdUserLabInStream();

    prepareStream();
}
