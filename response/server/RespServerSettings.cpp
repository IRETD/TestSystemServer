#include "RespServerSettings.h"

RespServerSettings::RespServerSettings() {

    m_Type = ResponseServerType::RESPONSE_SERVER_SETTINGS;
}


ServerSettings RespServerSettings::getServerSettings() const {

    return m_ServerSettings;
}

IdleList RespServerSettings::getIdleList() const {

    return m_IdleList;
}


void RespServerSettings::setServerSettings( const ServerSettings &settings ) {

    m_ServerSettings = settings;
}


void RespServerSettings::setBlackList( const BlackList &blackList ) {

    m_BlackList = blackList;
}


void RespServerSettings::setIdleList( const IdleList &idleList ) {

    m_IdleList = idleList;
}


BlackList RespServerSettings::getBlackList() const {

    return m_BlackList;
}
