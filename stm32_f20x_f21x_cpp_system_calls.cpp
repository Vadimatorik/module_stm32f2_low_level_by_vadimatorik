/**********************************************************************
 * Функции, необходимые для поддержания работы бибилиотеки libc.a.
 **********************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

#undef errno
extern int errno;

extern uint32_t __bss_end__;    // Конечный адрес BSS области.
                                // (По этому адресу записывать уже не нужно (проверяется по <)).

extern "C" {

/*
 * Метод вызывается при завершении программы
 * ( вызывается перезагрузка чипа ).
 * Вызвать ее могут exit, abort.
 */
void _exit ( void ) {
    // Вставить аппаратный сброс!
    while( true ) {}
}

/*
 * Убиваем процесс ( заглушка ).
 */
int _kill ( int pid, int sig ) {
    (void)pid; (void)sig;
    errno = EINVAL;
    return -1;
}

/*
 * Закрываем файл ( заглушка ).
 */
int _close ( void ) {
    return -1;
}

/*
 * Если имеется системный терминал, выводить в него данные.
 */
int _write ( char* buffer, uint32_t count ) {
    (void)buffer; (void)count;
    // Дописать поддержку терминала!
    return count;
}

/*
 * Если имеется системный терминал, то считать из него данные.
 */
int _read ( char* ptr, int len ) {
    (void)ptr; (void)len;
    // Реализовать считывание!
    return 0;
}

/*
 * Возвращаем тип "файла"
 * ( нашего терминала, если испольуется ).
 */
int _fstat( struct stat *st ) {
    st->st_mode = S_IFCHR;                      // Символно-ореинтированный "файл".
    return 0;
}

/*
 * Установка позиции в файле.
 * У нас используется ( если разрешен )
 * терминал.
 * Не используется ( заглушка ).
 */
int _lseek( void ) {
    return 0;
}

/*
 * Используется для уточнения, является ли
 * файл терминалом.
 */
int _isatty ( int file ) {
    (void)file;
    return 1;
}

/*
 * Возвращает ID процесса.
 * Не используется ( заглушка ).
 */
int _getpid ( void ) {
    return 1;
}

/*
 * Передача управления новому процессу.
 * Процессов нет -> возвращаем ошибку.
 */
int _execve ( char *name, char **argv, char **env )
{
    (void)name; (void)argv; (void)env;
    errno = ENOMEM;
    return -1;
}

/*
 * fork - создание нового процесса.
 * Мы их не поддерживаем.
 */
int _fork ( void ) {
    errno = EAGAIN;
    return -1;
}

/*
 * times - временная информация о процессе
 * ( сколько тиков: системных, процессорных и т.д. )
 * ( Заглушка ).
 */

clock_t _times( struct tms *buf ) {
    (void)buf;
    return -1;
}

/*
 * Удаляем имя файла ( Загулшка ).
 */
int _unlink( char *name ) {
    (void)name;
    errno = ENOENT;
    return -1;
}

/*
 * Ожидание дочерних процессов.
 * ( Заглушка ).
 */
int _wait( int *status ) {
    (void)status;
    errno = ECHILD;
    return -1;
}

const char HEAP_AND_STACK_COLLISION[] = "Heap and stack collision\n";

/*
 * Проверяем, что наши данные ( которые malloc и прочие могут
 * попробовать запросить ) не наложатся на стек.
 */
void* _sbrk ( intptr_t incr ) {
    uint32_t stack_ptr;                                                 // Адресс, на котором сейчас находится указатель стека
                                                                        // ( ячейка, на которую указывает указатель не пуста,
                                                                        // в ней последнее сохраненное слово ).
    asm volatile ( "MRS %0, msp\n" : "=r" ( stack_ptr ) );

    uint32_t static heap_end = ( uint32_t )&__bss_end__;                // Указатель на первый байт после области .bss.

    if ( heap_end + incr >= stack_ptr ) {
        _write( ( char* )HEAP_AND_STACK_COLLISION, sizeof(HEAP_AND_STACK_COLLISION) );
        abort();
    }

    heap_end += incr;
    return ( caddr_t )stack_ptr;
}

}

