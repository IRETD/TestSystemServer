#include "TestParamLimits.h"

TestParamLimits::TestParamLimits() {

    m_TimeLimitInMilliseconds = 0;
    m_MemoryLimitInBytes = 0;

    m_IsThereMemoryLimits = false;
    m_IsThereTimeLimits = false;
}


void TestParamLimits::setTimeLimitByMilliseconds( quint32 milliseconds ) {

    m_TimeLimitInMilliseconds = milliseconds;
    m_IsThereTimeLimits = true;
}


void TestParamLimits::setMemoryLimitByBytes( quint32 bytes ) {

    m_MemoryLimitInBytes = bytes;
    m_IsThereMemoryLimits = true;
}


bool TestParamLimits::isThereTimeLimits()  {

    return m_IsThereTimeLimits;
}

bool TestParamLimits::isThereMemoryLimits() {

    return m_IsThereMemoryLimits;
}


quint32 TestParamLimits::getTimeLimitByMilliseconds() {

    return m_TimeLimitInMilliseconds;
}


quint32 TestParamLimits::getMemoryLimitByBytes() {

    m_MemoryLimitInBytes;
}
