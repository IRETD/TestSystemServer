#ifndef TEACHERREQLABLIST_H
#define TEACHERREQLABLIST_H

#include <request/client/ReqLabList.h>
#include <TypeDefinitions/BaseTypeDefinitions.h>

typedef QList < ID_USER_LAB > ID_USER_LAB_LIST;
typedef QList < ID_VARIANT > ID_VARIANT_LIST ;
typedef QList < ID_LAB > ID_LAB_LIST;

class TeacherRespDisciplineTask;
#include <response/teacher/TeacherRespDisciplineTask.h>
#include <../../TestTeacher/Data/Group/Group.h>

class TeacherReqLabList : public ReqLabList {

    //получаем список групп
    //Для препода
    QList < Group > doGroupList( const OurDataBase &db,
                                 OurQueryInfo &queryInfo,
                                 TeacherRespDisciplineTask *pRespDisciplineTask,
                                 QList < ID_GROOP > idGroupList );

    // Возвращает список id для выбранных лабораторных по дисциплине
    QList < ID_LAB > doLabListByIdDiscipline( const OurDataBase &db,
                                              OurQueryInfo &queryInfo,
                                              TeacherRespDisciplineTask *pRespDisciplineTask,
                                              QList < ID_DISCIPLINE > idDisciplineList );

    void doStudentsHistory ( const OurDataBase &db,
                             OurQueryInfo &queryInfo,
                             TeacherRespDisciplineTask *pRespDisciplineTask,
                             QList < ID_STUDENT > idStudentsList ,
                             ID_GROOP idGroup);

    QList < Student > doStudentList( const OurDataBase &db,
                                     OurQueryInfo &queryInfo,
                                     quint32 idGroup,
                                     QList < ID_STUDENT > idStudentList );

    QList < ID_LAB > doIdLabListByIdVariant( const OurDataBase &db,
                                             OurQueryInfo &queryInfo,
                                             QList < ID_VARIANT > idVariantList );

    QPair < ID_USER_LAB_LIST,
            ID_VARIANT_LIST > doIdUserLabIdVariantPairOfList( const OurDataBase &db,
                                                              OurQueryInfo &queryInfo,
                                                              quint32 idStudent );

    /// возвращает список id групп которые попали в выборку
     QList < ID_GROOP > doTaskGroupList( const OurDataBase &db,
                                         OurQueryInfo &queryInfo,
                                         TeacherRespDisciplineTask *pRespDisciplineTask,
                                         QList < ID_LAB > idLabList );

public:
    TeacherReqLabList();

    ResponseClient *doRequest( const OurDataBase &db,
                               OurQueryInfo &queryInfo );
};

#endif // TEACHERREQLABLIST_H
