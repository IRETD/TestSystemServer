#include "ReqLabList.h"
#include <database/table/TableUserLab.h>
#include <database/table/TableVariantLab.h>
#include <database/table/TableLab.h>
#include <database/table/TableDiscipline.h>
#include <data/lab/Discipline.h>
#include <response/client/RespDisciplineTask.h>
#include <database/table/UniversalTable.h>
#include <MacroDefinitions/Request/Client/DefinitionsForReqLabList.h>

/// QList < int > idUserLabList - пустой, т.к. этот же метод наследуется
/// классом TeacherReqLabList, а для препода список idUserLabList неактуален.
QList < ID_DISCIPLINE > ReqLabList::getLabList(const OurDataBase &db,
                                              OurQueryInfo &queryInfo,
                                              RespDisciplineTask *respDisciplineTask,
                                              QList<ID_LAB> idLabList,
                                              QList < ID_USER_LAB > idUserLabList /* = QList < int > () */ ) {


    QSet < ID_DISCIPLINE > idDisciplineSet;
    ////ПОЛУЧАТЬ СРАЗУ СПИСОК TASK ПРИ ВЫБОРКЕ
    for ( int i = 0;
          i < idLabList.size();
          i++ ) {

        TableLab labTable( db );
        ID_LAB idLab = idLabList.at( i );
        Lab lab = labTable.getLab( idLab,
                                   queryInfo );
        respDisciplineTask -> addLab( lab );

        idDisciplineSet << lab.getIdDiscipline();
    }

    //Инициализация списком idUserLab
    //В случае с преподом - он будет пустым.
    //для студента же - СОДЕРЖИТ ВАЖНЫЕ ЗНАЧЕНИЯ idUserLab
    ///Плохо конечно, но пока пускай будет так
    respDisciplineTask -> addIdUserLabList( idUserLabList );

    return idDisciplineSet.toList();
}


void ReqLabList::getDisciplineList( const OurDataBase &db,
                                   OurQueryInfo &queryInfo,
                                   RespDisciplineTask *respDisciplineTask,
                                   QList < ID_DISCIPLINE > idDisciplineList ) {

    ///ЧАСТАЯ ВЫБОРКА
    for ( int i = 0; i < idDisciplineList.size(); i++ ) {

        ID_DISCIPLINE idDiscipline = idDisciplineList.at( i );
        Discipline discipline;

        TableDiscipline disciplineTable( db );
        discipline = disciplineTable.getDiscipline( idDiscipline,
                                                    queryInfo );
        respDisciplineTask -> addDiscipline( discipline );
    }
}


void ReqLabList::doReqLabList() {


}


ReqLabList::ReqLabList() {
}


ResponseClient *ReqLabList::doRequest( const OurDataBase &db,
                                       OurQueryInfo &queryInfo ) {

    RespDisciplineTask *pRespDisciplineTask = new RespDisciplineTask( static_cast < ResponseReciever > ( m_RequestSender ) );
    QList < ID_LAB > idLabList;
    QList < ID_USER_LAB > idUserLabList;

    TableUserLab userLab( db );

    idUserLabList = userLab.getIdUserLab( m_IdClient,
                                          queryInfo );
    //формируем список idLab
    //очень надо бы сократить число выборок
    /// а то для каждой id выборка
    for ( int i = 0;
          i < idUserLabList.size();
          i++ ) {


        ID_VARIANT idVariant = userLab.getIdVariant( idUserLabList.at( i ),
                                              queryInfo );
        TableVariantLab variantLab( db );
        ID_LAB idLab = variantLab.getIdLab( idVariant,
                                         queryInfo );
        idLabList.push_back( idLab );
    }


    QList < ID_DISCIPLINE > idDisciplineList = getLabList( db,
                                                         queryInfo,
                                                         pRespDisciplineTask,
                                                         idLabList,
                                                         ///idUserLabList НЕ нужен в случае с преподавателем :(
                                                         ///Для препода он ПУСТ
                                                         idUserLabList );
    getDisciplineList( db,
                       queryInfo,
                       pRespDisciplineTask,
                       idDisciplineList );

    return pRespDisciplineTask;
}
