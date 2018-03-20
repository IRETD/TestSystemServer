#include "Lab.h"


Lab::Lab() {

    m_IdUserLab = -1;
}

void Lab::setIdLab( const int &idLab ) {

    m_idLab = idLab;
}


void Lab::setIdUserLab( const int &idUserLab ) {

    m_IdUserLab = idUserLab;
}


void Lab::setIdDiscipline( const int &idDiscipline ) {

    m_IdDiscipline = idDiscipline;
}


void Lab::setName( const QString &name ) {

    m_Name = name;
}


void Lab::setPurpose( const QString &purpose ) {

    m_Purpose = purpose;
}


void Lab::setDesiredDate( const QDateTime &desiredDate ) {

    m_DesiredDate = desiredDate;
}


void Lab::setCriticalDate( const QDateTime &criticalDate ) {

    m_CriticalDate = criticalDate;
}


int Lab::getIdLab() {

    return m_idLab;
}


int Lab::getIdUserLab() {

    return m_IdUserLab;
}


int Lab::getIdDiscipline() {

    return m_IdDiscipline;
}


QString Lab::getName() const {

    return m_Name;
}


QString Lab::getPurpose() {

    return m_Purpose;
}


QDateTime Lab::getDesiredDate() {

    return m_DesiredDate;
}


QDateTime Lab::getCriticalDate() {

    return m_CriticalDate;
}
