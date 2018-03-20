//************************************************************************
// Передаем данное событие потокам в качестве запроса на исполнение
//************************************************************************


#ifndef OUREVENT_H
#define OUREVENT_H

#include <QEvent>
#include <request/client/RequestClient.h>

class OurEvent : public QEvent {

private:
    Request *m_pRequest;

public:
    OurEvent();

    static const int eventType = User + 1;
    void setRequest(Request *pRequest );
    Request *getRequest();
};

#endif
