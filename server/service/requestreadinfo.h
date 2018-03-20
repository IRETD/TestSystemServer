#ifndef REQUESTREADINFO_H
#define REQUESTREADINFO_H

enum class ReadStatus {

    INPUT_DATA_ARE_COMPLETE = 0,
    INPUT_DATA_ARE_INCOMPLETE = -1,
    INPUT_DATA_ARE_UNEXPECTED = -2
};

class RequestReadInfo {

    ReadStatus m_ReadStatus;
public:
    RequestReadInfo();

    ReadStatus getReadStatus();
    void setReadStatus( const ReadStatus &readStatus );
};

#endif // REQUESTREADINFO_H
