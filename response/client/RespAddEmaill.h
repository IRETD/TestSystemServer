#ifndef RESPADDEMAILL_H
#define RESPADDEMAILL_H

#include <response/client/ResponseClient.h>

class RespAddEmail : public ResponseClient {

    bool m_Result;

public:
    RespAddEmail();

    void setResult(bool b);
    void writeInStream();
};

#endif
