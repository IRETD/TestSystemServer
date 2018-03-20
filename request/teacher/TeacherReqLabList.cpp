#include "TeacherReqLabList.h"
#include <database/table/UniversalTable.h>
#include <MacroDefinitions/Request/Teacher/DefinitionsForTeacherReqLabList.h>
#include <QPair>
#include <database/table/TableLab.h>
#include <request/client/ReqHistory.h>
#include <response/client/RespHistory.h>
#include <assert.h>

TeacherReqLabList::TeacherReqLabList() {
}



ResponseClient *TeacherReqLabList::doRequest( const OurDataBase &db,
                                              OurQueryInfo &queryInfo ) {

    TeacherRespDisciplineTask *pRespDisciplineTask = new TeacherRespDisciplineTask( static_cast < ResponseReciever > ( m_RequestSender ) );
    QList < ID_DISCIPLINE > idDisciplineList;

    UniversalTable universalTable( db );
    idDisciplineList = universalTable.getListId( queryInfo,
                                                 TABLE_NAME_FOR_TEACHER_REQ_LAB_LIST,
                                                 ID_FIELD_TITLE_FOR_TEACHER_REQ_LAB_LIST,
                                                 FIELD_TITLE_FOR_TEACHER_REQ_LAB_LIST,
                                                 m_IdClient );

    QList < ID_LAB > idLabList = doLabListByIdDiscipline( db,
                                                          queryInfo,
                                                          pRespDisciplineTask,
                                                          idDisciplineList );
    getDisciplineList( db,
                       queryInfo,
                       pRespDisciplineTask,
                       idDisciplineList );

    QList < ID_GROOP > idGroupList = doTaskGroupList( db,
                                                      queryInfo,
                                                      pRespDisciplineTask,
                                                      idLabList );
    QList < Group > groupList = doGroupList( db,
                                             queryInfo,
                                             pRespDisciplineTask,
                                             idGroupList );
    pRespDisciplineTask -> addGroup( groupList );

    return pRespDisciplineTask;

}




/// Получаем список групп
/// В каждую из групп входят студент - поэтому студентов забираем в этом методе тоже из БД

QList < Group > TeacherReqLabList::doGroupList( const OurDataBase &db,
                                                OurQueryInfo &queryInfo,
                                                TeacherRespDisciplineTask *pRespDisciplineTask,
                                                QList < ID_GROOP > idGroupList ) {

    QList < Group > groupList;
    for ( quint32 i = 0;
          i < idGroupList.size();
          i ++ ) {


        Group group;
        ID_GROOP idGroup = idGroupList.at( i );
        UniversalTable groop( db );
        QString nameGroup = groop.getName( queryInfo,
                                           idGroup,
                                           TABLE_NAME_FOR_GROUP,
                                           ID_GROUP_FIELD_TITLE,
                                           NAME_GROOP_FIELD_TITLE );
        group.setIdGroup( idGroup );
        group.setName( nameGroup );

        // получаем список id студентов данной группы
        UniversalTable userGroop( db );
        QList < ID_STUDENT > idStudentList = userGroop.getListId( queryInfo,
                                                                   TABLE_NAME_FOR_USER_GROOP,
                                                                   USER_ID_FILED_TITLE,
                                                                   ID_GROUP_FIELD_TITLE,
                                                                   idGroup
                                                                 );
        // получаем всю личную информацию по студентам на основании списка id
         QList < Student > studentList = doStudentList( db,
                                                        queryInfo,
                                                        idGroup,
                                                        idStudentList );

         // Формируем в pRespDisciplineTask информацию по сдачам каждого студента
         // возвращать ничего не нужно.
         // Вся информация запишется в pRespDisciplineTask
         doStudentsHistory( db,
                            queryInfo,
                            pRespDisciplineTask,
                            idStudentList,
                            idGroup);


         group.addStudent( studentList );

         // по списку id студентов, получаем всю информацию по их сдачам
         // работ.

         /*
         pRespDisciplineTask -> setStudentList( idGroup,
                                                studentList );
         */

         groupList.push_back( group );
    }

    return groupList;
}



QList < ID_LAB > TeacherReqLabList::doLabListByIdDiscipline( const OurDataBase &db,
                                                             OurQueryInfo &queryInfo,
                                                             TeacherRespDisciplineTask *pRespDisciplineTask,
                                                             QList < ID_DISCIPLINE > idDisciplineList ) {


    QList < ID_LAB > idLabList;
    for ( int i = 0;
          i < idDisciplineList.size();
          i++ ) {

        TableLab labTable( db );
        int idDiscipline = idDisciplineList.at( i );
        QList < Lab > labList = labTable.getLabListByIdDiscipline( idDiscipline,
                                                                   queryInfo );
        foreach( Lab const &lab, labList ) {

            idLabList.append( lab.getIdLab() );
        }

        pRespDisciplineTask -> addLab( labList );
    }

    //Инициализация списком idUserLab
    //В случае с преподом - он будет пустым.
    //для студента же - СОДЕРЖИТ ВАЖНЫЕ ЗНАЧЕНИЯ idUserLab

    return idLabList;
}

void TeacherReqLabList::doStudentsHistory( const OurDataBase &db,
                                           OurQueryInfo &queryInfo,
                                           TeacherRespDisciplineTask *pRespDisciplineTask,
                                           QList < ID_STUDENT > idStudentsList,
                                           ID_GROOP idGroup ) {


    for ( quint32 i = 0;
          i < idStudentsList.size();
          i++ ) {

        ID_STUDENT idStudent = idStudentsList[ i ];

        /// САМОЕ ГЛАВНОЕ!!!!!
        /// Я ПОЛАГАЮСЬ НА ТО, ЧТО ПОРЯДОК В ID_USER_LAB_LIST СООТВЕТСТВУЕТ ПОРЯДКУ
        /// ID_VARIANT_LIST
        QPair < ID_USER_LAB_LIST,
                ID_VARIANT_LIST > pairOfList = doIdUserLabIdVariantPairOfList( db,
                                                                               queryInfo,
                                                                               idStudent );

        // генерируем запрос на получение историй по студенту,
        // зная при этом все его idUserLab
        QSharedPointer < ReqHistory > pReqHistory = QSharedPointer < ReqHistory > ( new ReqHistory );
        // ВАЖНЫЙ МОМЕНТ.
        // Устанавливаем фильтр idUserLab,
        // так как мы должны получить истории только ТЕХ предметов,
        // на которые назначен данный преподаватель!
        pReqHistory.data() -> setIdUserLabFilter( pairOfList.first );
        RespHistory *pRespHistory = static_cast < RespHistory * > ( pReqHistory.data() -> doRequest( db,
                                                                                                     queryInfo ) );
        QList < History > historyList = pRespHistory -> getHistoryList();
        QList < AboutHistory > aboutHistory = pRespHistory -> getAboutHistoryList();

        /// !!!!!!!!!!!!!!!!!!!!!!!!!
        /// Конечно же вскоре нужно внедрить УМНЫЙ указатель
        delete pRespHistory;
        assert( pRespHistory != NULL );

        pRespDisciplineTask -> addHistoryToStudent( idStudent,
                                                    historyList );
        pRespDisciplineTask -> addAboutHistoryToStudent( idStudent,
                                                         aboutHistory );
        // получаем список id_lab, которые назначены на студента

        /// САМОЕ ГЛАВНОЕ!!!!!
        /// Я ПОЛАГАЮСЬ НА ТО, ЧТО ПОРЯДОК В ID_LAB СООТВЕТСТВУЕТ ПОРЯДКУ
        /// В pairOfList.first (список idUserLab)
        QList < ID_LAB > idLabList = doIdLabListByIdVariant( db,
                                                             queryInfo,
                                                             pairOfList.second );

        // Формиурем соотв. каждой idLabGroup (группа причисленная к лабе)
        // значение idUserLab (запись о назначении студента на лабу)
        // к КАЖДОМУ студенту группы.
        for ( quint32 j = 0;
              j < idLabList.size();
              j++ ) {

            // ПОЛАГАЮСЬ на то, что в pRespDisciplineTask уже СФОРМИРОВАН
            // список из TaskGroup!!!!
            ID_LAB idLab = idLabList[ j ];
            ID_LAB_GROOP idLabGroup = pRespDisciplineTask->getIdLabGroopFromTaskGroupList( idGroup,
                                                                                           idLab );
            // если idLabGroup БЫЛ найден.
            if ( idLabGroup != -1 ) {
                ID_USER_LAB idUserLab = pairOfList.first[ j ]; // j ??? или i ?? (было i и падало)
                pRespDisciplineTask -> addIdUserLabToIdStudentByIdLabGroup( idLabGroup,
                                                                            idStudent,
                                                                            idUserLab );
            }

        }
        // Далее, получаем значение idLabGroup чтобы привязать
        //

        // по idUserLab невозможно, к сожалению, сказать
        // какая это именно лабораторная работа.
        // Поэтому, необходимо установить взаимосвязь между idUserLab и idLab,
        // что собственно этот метод и делает.
        // У КАЖДОГО студента есть связь для idUserLab и idLab.
        // На клиенте можно будет по всем idUserLab установить лабораторные, к которым
        // они принадлежат.
        /*
        pRespDisciplineTask -> addStudentIdUserLabListToIdLabList( idStudent,
                                                                   pairOfList.first,
                                                                   idLabList );
        */
    }
}


QList < Student > TeacherReqLabList::doStudentList( const OurDataBase &db,
                                                    OurQueryInfo &queryInfo,
                                                    quint32 idGroup,
                                                    QList < ID_STUDENT > idStudentList ) {
    QList < Student > studentList;
    for ( int i = 0;
          i < idStudentList.size();
          i++ ) {

        int idStudent = idStudentList.at( i );
        UniversalTable user( db );
        QString name = user.getName( queryInfo,
                                     idStudent,
                                     STUDENT_TABLE_NAME,
                                     STUDENT_ID_FIELD_TITLE,
                                     STUDENT_NAME_FILED_TITLE );
        Student student;
        student.setName( name );
        student.setIdStudent( idStudent );
        student.setIdGroup( idGroup );

        studentList.push_back( student );
    }

    return studentList;
}


QList < ID_LAB > TeacherReqLabList::doIdLabListByIdVariant( const OurDataBase &db,
                                                            OurQueryInfo &queryInfo,
                                                            QList < ID_VARIANT > idVariantList ) {

    QList < ID_LAB > idLabList;
    for ( quint32 i = 0;
          i < idVariantList.size();
          i++ ) {
        ID_VARIANT idVariant = idVariantList[ i ];
        UniversalTable variantLabTable( db );
        ID_LAB idLab = variantLabTable.getId( queryInfo,
                                              VARIANT_LAB_TABLE_NAME,
                                              ID_LAB_FIELD_TITLE,
                                              ID_VARIANT_FIELD_TITLE,
                                              idVariant );

        idLabList.push_back( idLab );
    }

    return idLabList;
}


QPair < ID_USER_LAB_LIST,
        ID_VARIANT_LIST > TeacherReqLabList::doIdUserLabIdVariantPairOfList( const OurDataBase &db,
                                                                             OurQueryInfo &queryInfo,
                                                                             quint32 idStudent ) {

    UniversalTable userLabTable( db );

    // ПАРА списков по id_user_lab
    // и id_varian_list
    QPair < ID_USER_LAB_LIST,
            ID_VARIANT_LIST > pairOfList =  userLabTable.getPairOfList( queryInfo,
                                                                        TABLE_NAME_FOR_USER_LAB,
                                                                        ID_USER_LAB_FIELD_TITLE,
                                                                        ID_VARIANT_FIELD_TITLE,
                                                                        STUDENT_ID_FIELD_TITLE,
                                                                        idStudent
                                                                      );

    return pairOfList;
}


QList < ID_GROOP > TeacherReqLabList::doTaskGroupList( const OurDataBase &db,
                                                       OurQueryInfo &queryInfo,
                                                       TeacherRespDisciplineTask *pRespDisciplineTask,
                                                       QList < ID_LAB > idLabList ) {

    QList < TaskGroup > taskGroupList;

    QSet < int > idGroupSet;
    for ( int i = 0;
          i < idLabList.size();
          i++ ) {

        int idLab = idLabList.at( i );
        UniversalTable labGroopTable( db );


        // олучаем пару связку из БД - id_lab_goop и id_groop
        QList < QPair < ID_LAB_GROOP,
                        ID_GROOP >
              > pairList = labGroopTable.getPairIdList( queryInfo,
                                                        TABLE_NAME_FOR_TEACHER_REQ_LAB_GROOP_LIST,
                                                        ID_LAB_GROUP_FIELD_TITLE,
                                                        ID_GROUP_FIELD_TITLE,
                                                        ID_LAB_FIELD_TITLE,
                                                        idLab
                                                      );

        foreach( auto pair,
                 pairList ) {
            TaskGroup taskGroup;
            taskGroup.m_IdLabGroup = pair.first;
            taskGroup.m_IdTask = idLab;
            taskGroup.m_IdGroup = pair.second;
            taskGroupList.append( taskGroup );

            idGroupSet << pair.second;
        }

    }

    pRespDisciplineTask -> addTaskGroupList( taskGroupList );

    return idGroupSet.toList();
}
