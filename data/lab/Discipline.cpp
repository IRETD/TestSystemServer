#include "Discipline.h"
#include <QDataStream>

Discipline::Discipline() {
}


QDataStream& operator >> ( QDataStream &stream,
                           Discipline &value ) {

    stream >> value.m_IdDiscipline >>
              value.m_Name >>
              value.m_Description;

    return stream;
}


QDataStream& operator << ( QDataStream &stream,
                           Discipline &value ) {

    stream << value.m_IdDiscipline <<
              value.m_Name <<
              value.m_Description;

    return stream;
}


void Discipline::setIdDiscipline( const int &idDiscipline ) {

    m_IdDiscipline = idDiscipline;
}


int Discipline::getIdDiscipline() const {

    return m_IdDiscipline;
}


void Discipline::setDescription( const QString &description ) {

    m_Description = description;
}


void Discipline::setName( const QString &name ) {

    m_Name = name;
}


QString Discipline::getName() const {

    return m_Name;
}


QString Discipline::getDescription() const {

    return m_Description;
}


