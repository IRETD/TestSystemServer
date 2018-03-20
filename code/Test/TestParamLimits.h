#ifndef TESTPARAMLIMITS_H
#define TESTPARAMLIMITS_H

#include <QObject>

class TestParamLimits {

    quint32 m_TimeLimitInMilliseconds;
    quint32 m_MemoryLimitInBytes;

    bool m_IsThereTimeLimits;
    bool m_IsThereMemoryLimits;
public:
    TestParamLimits();
    void setTimeLimitByMilliseconds( quint32 milliseconds );
    void setMemoryLimitByBytes( quint32 bytes );
    bool isThereTimeLimits();
    bool isThereMemoryLimits();

    quint32 getTimeLimitByMilliseconds();
    quint32 getMemoryLimitByBytes();

};

#endif // TESTPARAMLIMITS_H
