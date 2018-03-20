#include "OurDataBaseKeepConnection.h"
#include "OurDataBase.h"


OurDataBaseKeepConnection::OurDataBaseKeepConnection( QObject *parent ) :
    QObject( parent ), timerAttemptConnection( this ) {

    connect( &timerAttemptConnection, &QTimer::timeout, this, &OurDataBaseKeepConnection::attemptConnection );
}


void OurDataBaseKeepConnection::databaseNotAvailable() {

    if ( !timerAttemptConnection.isActive() ) {
        timerAttemptConnection.start( 5000 );
    }
}


void OurDataBaseKeepConnection::attemptConnection() {

    OurDataBase db;

    bool resultConnection = db.connectToDataBase( LOGIN, PASSWORD, NAME_CONNECTION );

    if ( resultConnection ) {
        emit databaseAvailable();
        timerAttemptConnection.stop();
    }
}
