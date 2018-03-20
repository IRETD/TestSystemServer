//************************************************************************
// Переподключаемся к базе данных если произошло разъединение.
//
//************************************************************************

#ifndef OURDATABASEKEEPCONNECTION_H
#define OURDATABASEKEEPCONNECTION_H

#include <QObject>
#include <QTimer>

// Был создан специальный клиент БД, который будет проверять
// состояние сервера, а это его данные для авторизации.

static const QString LOGIN = "attemptconnect";
static const QString PASSWORD = "attemptconnect";
static const QString NAME_CONNECTION = "attemptconnect";

class OurDataBaseKeepConnection : public QObject {

    Q_OBJECT

    QTimer timerAttemptConnection;

public:
    OurDataBaseKeepConnection( QObject *parent = 0 );

signals:
    void databaseAvailable();

public slots:
    void databaseNotAvailable();

private slots:
    void attemptConnection();

};

#endif
