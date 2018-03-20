/****************************************************************************
**
** Запрос на историю по сдаче лабораторной работы.
**
****************************************************************************/

#ifndef RESPLABHISTORY_H
#define RESPLABHISTORY_H

#include <response/client/ResponseClient.h>
#include <response/client/subclasses/history.h>
#include <QVector>

class RespLabHistory : public ResponseClient {

    QVector <History> m_Lab; // вектор с историей по лабораторным

public:
    RespLabHistory();

    void addLabHist(History h);
    void writeInStream(QDataStream &stream);
};

#endif
