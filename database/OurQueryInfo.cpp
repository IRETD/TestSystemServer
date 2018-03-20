#include "OurQueryInfo.h"

OurQueryInfo::OurQueryInfo() {

    m_TypeError = QSqlError::NoError;
    m_NumberError = -1;
    m_Description = "";
    m_Result = false;
}

void OurQueryInfo::setTypeError( const QSqlError::ErrorType &typeError ) {

    m_TypeError = typeError;
}


void OurQueryInfo::setNumberError( const int &numberError ) {

    m_NumberError = numberError;
}


void OurQueryInfo::setDescription( const QString &description ) {

    m_Description = description;
}


void OurQueryInfo::setResult( const bool &result ) {

    m_Result = result;
}


QSqlError::ErrorType OurQueryInfo::getTypeError() const {

    return m_TypeError;
}


int OurQueryInfo::getNumberError() const {

    return m_NumberError;
}


QString OurQueryInfo::getDescription() const {

    return m_Description;
}


bool OurQueryInfo::isPermissible() {

    return m_TypeError == QSqlError::NoError;
}


bool OurQueryInfo::isConnectionError() {

    return m_NumberError == NO_DATABASE_CONNECTION;
}


bool OurQueryInfo::getResult() {

    return m_Result;
}
