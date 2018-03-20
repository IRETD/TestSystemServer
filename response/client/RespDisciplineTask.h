#ifndef RESPLAB_H
#define RESPLAB_H

#include <response/client/ResponseClient.h>
#include <data/lab/Discipline.h>
#include <data/lab/StudentTask.h>
#include <TypeDefinitions/BaseTypeDefinitions.h>

enum TypeData {

    DISCIPLINE = 1,
    LAB = 2
};

typedef StudentTask Lab;

// Запись Task в поток различаются между преподом и
// студентом (idUserLab у препода не пишется!!!!!)
/// ПОТЭТОМУ НЕОБХОДИМО РАЗЛИЧАТЬ Task между преподом и
/// студентом
class RespDisciplineTask : public ResponseClient {

protected:
    QList < Discipline > m_DisciplineList;
    QList < Lab > m_LabList;

    void writeDisciplinesInStream();
    void writeLabsInStream();

public:
    RespDisciplineTask( ResponseReciever responseReciever );

    void addDiscipline( const Discipline &discipline );
    void addLab( const Lab &task );
    void addLab( QList < Lab > &taskList );
    void addIdUserLabList( QList < ID_USER_LAB > idUserLabList );

    void writeInStreamBuffer();
};

#endif // RESPLAB_H
