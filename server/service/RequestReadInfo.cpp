#include "RequestReadInfo.h"


RequestReadInfo::RequestReadInfo() {

    m_ReadStatus = ReadStatus::INPUT_DATA_ARE_COMPLETE;
}


ReadStatus RequestReadInfo::getReadStatus() {

    return m_ReadStatus;
}


void RequestReadInfo::setReadStatus( const ReadStatus &readStatus ) {

    m_ReadStatus = readStatus;
}
