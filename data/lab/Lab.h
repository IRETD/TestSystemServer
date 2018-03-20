#ifndef LAB_H
#define LAB_H

#include <QString>
#include <QDateTime>

class Lab {

    int m_idLab;
    int m_IdUserLab;
    int m_IdDiscipline;
    QString m_Name;
    QString m_Purpose;
    QDateTime m_DesiredDate;
    QDateTime m_CriticalDate;

public:
    Lab();

    void setIdLab( const int &idLab );
    void setIdUserLab( const int &idUserLab );
    void setIdDiscipline( const int &idDiscipline );
    void setName( const QString &name );
    void setPurpose( const QString &purpose );
    void setDesiredDate( const QDateTime &desiredDate );
    void setCriticalDate( const QDateTime &criticalDate );

    int getIdLab();
    int getIdUserLab();
    int getIdDiscipline();
    QString getName() const;
    QString getPurpose();
    QDateTime getDesiredDate();
    QDateTime getCriticalDate();
};

#endif // LAB_H
