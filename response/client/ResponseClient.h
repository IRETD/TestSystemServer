/****************************************************************************
**
** Абстрактный класс определяющий поведение наших результатов по запросам.
**
****************************************************************************/

#ifndef RESPONSE_H
#define RESPONSE_H

#include <QByteArray>
#include <QDataStream>
#include <QTcpSocket>
#include <MacroDefinitions/IdentifierMessage.h>
#include <MacroDefinitions/Response/ResponseReciever.h>

typedef IdentifierMessage ResponseClientType;

class ResponseClient {

protected:
    QDataStream m_StreamBuffer;
    QByteArray m_Buffer;
    int m_IdClient;
    ResponseClientType m_ResponseType;

    // кто получатель запроса
    ResponseReciever m_ResponseReciever;

public:
    /// пускай по умолчанию будет пока что студент
    /// Но на будущее: вполне появится необходимость различать ответы для студента или преподавателя
    /// скрытые под единными указалетел
    ResponseClient( ResponseReciever responseReciever );

    virtual void writeInStreamBuffer() = 0;
    virtual QString serialize();
    virtual void deserialize( QByteArray &byteArr );
    QByteArray &getBuffer();
    void setIdClient( const int &idClient );
    int getIdClient() const;
    void setResponseClientType( const ResponseClientType &responseType );
    ResponseClientType getResponseClientType();
    void clearStream();
    void prepareStream();
    ResponseReciever getResponseReciever();
    void setResponseReciever( ResponseReciever responseReciever );
    void streamProlog( ResponseClientType responseType );
    void streamEpilog();


    template < class TypeData >
    void writeListDataInStream( TypeData &data ) {

        quint32 size = data.size();
        m_StreamBuffer << size;
        for ( int i = 0;
              i < size;
              i++ ) {

            m_StreamBuffer << data[ i ];
        }
    }
};

#endif
