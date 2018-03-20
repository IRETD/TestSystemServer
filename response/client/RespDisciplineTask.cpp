#include "RespDisciplineTask.h"
#define TEMPLATE_DECLARATION template < class TaskType >


void RespDisciplineTask::writeDisciplinesInStream() {

    writeListDataInStream( m_DisciplineList );
}


void RespDisciplineTask::writeLabsInStream() {

    writeListDataInStream( m_LabList );
}


RespDisciplineTask::RespDisciplineTask( ResponseReciever responseReciever ) : ResponseClient( responseReciever ) {
}


void RespDisciplineTask::addDiscipline( const Discipline &discipline ) {

    m_DisciplineList.push_back( discipline );
}


void RespDisciplineTask::addLab(const Lab &task ) {

    m_LabList.push_back( task );
}


void RespDisciplineTask::addLab(QList < Lab > &taskList ) {

    m_LabList.append( taskList );
}


// Инициализация ВСЕХ лаборатных список idUserLab.
void RespDisciplineTask::addIdUserLabList( QList < ID_USER_LAB > idUserLabList )  {

    for ( int i = 0;
          i < idUserLabList.size();
          i++ ) {

        if ( i < m_LabList.size() ) {

            m_LabList[ i ].setIdUserLab( idUserLabList.at( i ) );
        }
    }
}


void RespDisciplineTask::writeInStreamBuffer() {

    clearStream();
    streamProlog( ResponseClientType::DISCIPLINE_TASK );

    writeDisciplinesInStream();
    writeLabsInStream();

    prepareStream();
}
