#ifndef STUDENT_TASK_H
#define STUDENT_TASK_H

#include <QString>
#include <QDateTime>

class StudentTask {

    #define THERE_IS_NO_ID_USERLAB -1
    quint32 m_idLab;
    quint32 m_IdUserLab;
    quint32 m_IdDiscipline;
    QString m_Name;
    QString m_Purpose;
    QDateTime m_DesiredDate;
    QDateTime m_CriticalDate;

public:
    StudentTask();

    friend QDataStream& operator >> ( QDataStream &stream,
                                      StudentTask &value );
    friend QDataStream& operator << ( QDataStream &stream,
                                      StudentTask &value );

    void setIdLab( quint32 const &idLab );
    void setIdUserLab( quint32 const &idUserLab );
    void setIdDiscipline( quint32 const &idDiscipline );
    void setName( const QString &name );
    void setPurpose( const QString &purpose );
    void setDesiredDate( const QDateTime &desiredDate );
    void setCriticalDate( const QDateTime &criticalDate );

    //Понадобилось 2 метода - 1 const (в местах использования константных ссылок)
    //в другом без константных ссылок
    quint32 getIdLab() const;
    quint32 getIdLab();

    quint32 getIdUserLab();
    quint32 getIdDiscipline();
    QString getName() const;
    QString getPurpose();
    QDateTime getDesiredDate();
    QDateTime getCriticalDate();
};

#endif // STUDENT_TASK_H
