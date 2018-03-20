//************************************************************************
// Класс интерпретации запросов клиента.
//
//************************************************************************


#ifndef STREAMREADER_H
#define STREAMREADER_H

#include <QDataStream>
#include <QtNetwork/QTcpSocket>
#include <QString>
#include <server/client/Client.h>
#include <request/RequestFactory.h>
#include <server/service/RequestReadInfo.h>
#include <memory>

class StreamReader {

public:
    StreamReader();

    RequestClient *readStream( Client &client,
                              const RequestFactory &factory,
                              RequestReadInfo &readInfo );
};

#endif
