#ifndef OURQUERYINFO_H
#define OURQUERYINFO_H

#include <QString>

#include <QSqlError>

enum {

    NO_ERROR = -1,
    NO_DATABASE_CONNECTION = 2006
};

class OurQueryInfo {

    QSqlError::ErrorType m_TypeError;
    int m_NumberError;
    QString m_Description;
    bool m_Result;

public:
    OurQueryInfo();

    void setTypeError( const QSqlError::ErrorType &typeError );
    void setNumberError( const int &numberError );
    void setDescription( const QString &description );
    void setResult( const bool &result );

    QSqlError::ErrorType getTypeError() const;
    int getNumberError() const;
    QString getDescription() const;
    bool isPermissible();
    bool isConnectionError();
    bool getResult();
};

#endif
