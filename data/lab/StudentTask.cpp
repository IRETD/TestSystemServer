#include "StudentTask.h"
#include <assert.h>
#include <QDataStream>


StudentTask::StudentTask() {

    m_IdUserLab = THERE_IS_NO_ID_USERLAB;
}


QDataStream& operator >> ( QDataStream &stream,
                           StudentTask &value ) {


}


QDataStream& operator << ( QDataStream &stream,
                           StudentTask &value ) {

    stream << value.m_IdUserLab <<
              value.m_IdDiscipline <<
              value.m_idLab <<
              value.m_Name <<
              value.m_Purpose <<
              value.m_DesiredDate <<
              value.m_CriticalDate;

    return stream;
}

void StudentTask::setIdLab( quint32 const &idLab ) {

    m_idLab = idLab;
}


void StudentTask::setIdUserLab( quint32 const &idUserLab ) {

    m_IdUserLab = idUserLab;
}


void StudentTask::setIdDiscipline( quint32 const &idDiscipline ) {

    m_IdDiscipline = idDiscipline;
}


void StudentTask::setName( const QString &name ) {

    m_Name = name;
}


void StudentTask::setPurpose( const QString &purpose ) {

    m_Purpose = purpose;
}


void StudentTask::setDesiredDate( const QDateTime &desiredDate ) {

    m_DesiredDate = desiredDate;
}


void StudentTask::setCriticalDate( const QDateTime &criticalDate ) {

    m_CriticalDate = criticalDate;
}


quint32 StudentTask::getIdLab() const {

    return m_idLab;
}

quint32 StudentTask::getIdLab() {

    return m_idLab;
}


quint32 StudentTask::getIdUserLab() {

    //assert( m_IdUserLab != THERE_IS_NO_ID_USERLAB );
    return m_IdUserLab;
}


quint32 StudentTask::getIdDiscipline() {

    return m_IdDiscipline;
}


QString StudentTask::getName() const {

    return m_Name;
}


QString StudentTask::getPurpose() {

    return m_Purpose;
}


QDateTime StudentTask::getDesiredDate() {

    return m_DesiredDate;
}


QDateTime StudentTask::getCriticalDate() {

    return m_CriticalDate;
}
