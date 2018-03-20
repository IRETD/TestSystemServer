#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include <QString>

class Discipline {

    int m_IdDiscipline;
    QString m_Name;
    QString m_Description;

public:
    Discipline();

    friend QDataStream& operator >> ( QDataStream &stream,
                                      Discipline &value );
    friend QDataStream& operator << ( QDataStream &stream,
                                      Discipline &value );

    void setIdDiscipline( const int &idDiscipline );
    int getIdDiscipline() const;
    void setDescription( const QString &description );
    void setName( const QString &name );
    QString getName() const;
    QString getDescription() const;
};

#endif
