#ifndef PROCESSRESULT_H
#define PROCESSRESULT_H

enum ProcessResult {

    ERROR_NONE = 0, //Нет ошибки
    ERROR_START = -1, //Ошибка старта процесса
    ERROR_WRITE_DATA = -2, //Ошибка записи данных в процесс
    ERROR_WRITE_TIMEOUT = -3, //Ошибка ВРЕМЕНИ записи данных в процесс
    ERROR_READ_DATA = -4, // Ошибка считывания данных с процесса
    ERROR_READ_TIMEOUT = -5, // Ошибка ВРЕМЕНИ считывания данных с процесса
    ERROR_FINISH = -6, // Ошибка завершения процесса
    ERROR_FINISH_TIMEOUT = -7, //Ошибка ВРЕМЕНИ завершения процесса
    ERROR_TOTAL_TIMEOUT = -8, // Таймаут процесса
    ERROR_TEST = -9 // Ошибка тестирования - на выходе получили не ожидаемые данные.
};

#endif // PROCESSRESULT_H
