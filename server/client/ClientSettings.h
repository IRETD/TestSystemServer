#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H

#include <QTime>

class ClientSettings {

    int m_RequestCountLimit;
    int m_RequestTimeLimit;

    int m_BufferMaximumSize;

public:
    ClientSettings();

    void setRequestCountLimit( const int &requestCountLimit );
    void setRequestTimeLimit( const int &requestTimeLimit );
    void setBufferMaximumSize( const int &bufferMaximumSize );
    int getBufferMaximumSize();
    int getRequestCountLimit();
    int getRequestTimeLimit();
};

#endif // CLIENTSETTINGS_H
