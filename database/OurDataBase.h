//************************************************************************
// Класс отвечающий за подключение к базе данных.
//
//************************************************************************

#ifndef OURDATABASE_H
#define OURDATABASE_H

#include <QtSql/QtSql>
#include <QMutex>
#include <QDateTime>
#include <QObject>

enum {

    QUERY_NO_DATA = -1, // Пустой ответ запроса.
    QUERY_ERROR = -2, // Ошибка выполнения запроса.
    RECORD_ERROR = -3 // Ошибка выборки записи после выполнения запроса.
};

class OurDataBase {

protected:
    QSqlDatabase m_Db;
    QString m_ConnectionName;

public:
    OurDataBase();

    bool connectToDataBase( const QString &login, const QString &password,
                            const QString &nameConnection, const int &port = 3306, const QString &hostName = "localhost",
                            const QString &databaseName = "db" );

    bool startTransaction();
    bool commit();
    bool rollback();
    bool getStatus();
    bool isConnectionActive();

    QSqlError getLastError();

    QString getConnectionName();
};

#endif
