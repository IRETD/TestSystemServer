/*
 * Для прослеживания процесса "простоя" клиентов на стороне сервера
 * необходимо установить слежку активности клиентов на начальном этапе их работы с сервером.
 *
 * Для этого этапа и был выделен данный класс.
 * Известно МАКСИМАЛЬНОЕ время простоя клиента ( int m_LimitSecondForIdle ) изначально.
 * Необходимо задать идентификационный номер клиента в системе, для начала отслеживания его "простоя" в системе.
 * По истечению заданного лимита - испускается сигнал clientIsIdle( int ) где в качестве параметра передается номер клиента.
 *
 */


#ifndef IDLELIST_H
#define IDLELIST_H

#include <QObject>
#include <QHash>
#include <QTime>
#include <QTimer>

enum {

    MILLISECONDS_PER_SECOND = 1000
};

class IdleList : public QObject {

    Q_OBJECT

    //таймер который отсчитывает момент проверки клиентов
    QTimer m_Timer;
    //на каждого клиента по его id назначается время его поступления
    QHash < int, QTime > m_IdleTable;
    //число кратное периоду таймера отсчета проверки клиентов на простое
    int m_TimerStartSecond;
    //лимит времени по простою для клиента В СЕКУНДАХ
    int m_LimitSecondForIdle;


    void checkIdleTableForEmpty();
private slots:
    //проверяем весь список клиентов
    void checkIdleList();

signals:
    //испускаем сигнал, если клиент превысил время простоя
    void clientIsIdle( int );

public:
    IdleList( QObject *pObjct = 0 );
    IdleList( const IdleList& copySource );
    void addClient( int idClient );
    void removeClient( int idClient );
    bool contain( int idClient );
    void setLimitSecondForIdle( const int &limitSecond );
    IdleList& operator=( const IdleList& copySource );
};

#endif // IDLELIST_H
