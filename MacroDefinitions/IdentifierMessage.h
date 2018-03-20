#ifndef IDENTIFIERMESSAGE_H
#define IDENTIFIERMESSAGE_H

enum class IdentifierMessage {

    AUTHORIZATION = 1,
    DISCIPLINE,
    TASK,
    DISCIPLINE_TASK,
    HISTORY,
    CODE,
    ANALYZE,

    //завершить текущий сеанс
    LEAVE_AUTHORIZATION,

    //RespMessage - ответ от сервера в виде сообщения
    MESSAGE

};

#endif // IDENTIFIERMESSAGE_H
