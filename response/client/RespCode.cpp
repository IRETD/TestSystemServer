#include "RespCode.h"
#include <response/client/ResponseClientName.h>

RespCode::RespCode( ResponseReciever responseReciever ) : ResponseClient( responseReciever ) {
}

void RespCode::writeInStreamBuffer() {

    m_StreamBuffer << quint32( 0 ) << static_cast <int> ( ResponseClientType::CODE );

    for ( int i = 0; i < m_StageList.size(); i++ )
        m_StreamBuffer << m_StageList[ i ].getName() << m_StageList[ i ].getResult();

    m_StreamBuffer.device() -> seek( 0 );
    m_StreamBuffer << quint32( m_Buffer.size() - sizeof( quint32 ) );
}


void RespCode::addStage( const Stage &codeStage ) {

    m_StageList.append( codeStage );
}


QList <Stage> RespCode::getStage() {

    return m_StageList;
}


QString RespCode::serialize() {

    QByteArray byteArr;
    QDataStream stream( &byteArr, QIODevice::WriteOnly );
    stream << static_cast <int> ( ResponseClientType::CODE ) << m_IdClient << m_StageList.size();

    for ( int i = 0; i < m_StageList.size(); i++ )
        stream << m_StageList[ i ].getName() << m_StageList[ i ].getResult();

    QString result = QString::fromUtf8( byteArr.data(), byteArr.size() );
    return result;
}


void RespCode::deserialize( QByteArray &byteArr ) {

    QDataStream stream( &byteArr, QIODevice::ReadOnly );
    Stage codeStage;
    QString name;
    QString result;
    int codeStageSize = 0;

    stream >> m_IdClient >> codeStageSize;

    for ( int i = 0; i < codeStageSize; i++ ) {
        stream >> name >> result;
        codeStage.setName( name );
        codeStage.setResult( result );
        m_StageList.append( codeStage );
    }

    writeInStreamBuffer();
}
