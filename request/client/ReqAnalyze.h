#ifndef REQANALYZE_H
#define REQANALYZE_H

#include <request/client/RequestClient.h>
#include <response/client/ResponseClient.h>

class ReqAnalyze : public RequestClient {

    quint32 m_IdHistory;
    quint32 m_IdAboutHistory;

public:
    ReqAnalyze();

    void readStream( QDataStream &stream );

    ResponseClient *doRequest( const OurDataBase &db, OurQueryInfo &queryInfo );
};

#endif // REQANALYZE_H
