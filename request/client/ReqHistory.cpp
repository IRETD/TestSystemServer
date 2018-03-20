#include "ReqHistory.h"
#include <response/client/RespHistory.h>
#include <database/table/TableHistory.h>
#include <database/table/TableAboutHistory.h>
#include <database/table/TableUserLab.h>


ReqHistory::ReqHistory() {

    m_IdUserLabFilterList.clear();

}

ResponseClient *ReqHistory::doRequest( const OurDataBase &db,
                                       OurQueryInfo &queryInfo ) {


    RespHistory *pRespHistory = new RespHistory( static_cast < ResponseReciever > ( m_RequestSender ) );

    TableHistory historyTable( db );

    // Если фильтр id_user_lab пуст, то выбриаем ВСЕ что может принадлежать
    // студенту.
    // В противном случае - берем фильтр ЦЕЛИКОМ.
    if ( m_IdUserLabFilterList.isEmpty() ) {

        TableUserLab userLabTable( db );
        m_IdUserLabFilterList = userLabTable.getIdUserLab( m_IdClient,
                                                           queryInfo );
    }

    for ( quint32 i = 0;
          i < m_IdUserLabFilterList.size();
          i++ ) {

        ID_USER_LAB idUserLab = m_IdUserLabFilterList.at( i );
        QList < History > historyList = historyTable.getHistoryList( idUserLab,
                                                                     queryInfo );

        if ( !historyList.isEmpty() ) {

            for ( int j = 0; j < historyList.size(); j++ ) {

                History history = historyList.at( j );
                TableAboutHistory aboutHistoryTable( db );

                QList < AboutHistory > aboutHistoryList = aboutHistoryTable.getAboutHistoryList( history.getIdHistory(),
                                                                                                 queryInfo );
                if ( !aboutHistoryList.isEmpty() ) {

                    pRespHistory -> addAboutHistoryList( aboutHistoryList );
                }
                /*
                //получем отдельно список наименований этапов
                QList < AboutHistory > descriptionResultList = aboutHistoryTable.getDescriptionResultList( history.getIdHistory(), queryInfo );
                if ( !descriptionResultList.isEmpty() ) {

                    pRespHistory -> addAboutHistoryList( descriptionResultList );
                }

                //получаем список результатов к каждому из этапов
                QList < AboutHistory > stepResultList = aboutHistoryTable.getDescriptionStepList( history.getIdHistory(), queryInfo );
                if( !stepResultList.isEmpty() ) {

                    pRespHistory -> addAboutHistoryList( stepResultList );
                }
                */

            }

            pRespHistory -> addHistoryList( historyList );
        }

    }

    return pRespHistory;
}


void ReqHistory::setIdUserLabFilter( QList < ID_USER_LAB > idUserLabFilterList )  {

    m_IdUserLabFilterList = idUserLabFilterList;
}
