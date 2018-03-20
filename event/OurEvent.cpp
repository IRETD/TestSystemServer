#include "event/OurEvent.h"


OurEvent::OurEvent() : QEvent( ( Type ) eventType ) {
}


void OurEvent::setRequest( Request *pRequest ) {

    m_pRequest = pRequest;
}

Request *OurEvent::getRequest() {

    return m_pRequest;
}
