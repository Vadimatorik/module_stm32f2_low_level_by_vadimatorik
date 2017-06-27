/**********************************************************************
 * Функции, необходимые для поддержания работы бибилиотеки libc.a.
 **********************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
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
    return 1;
}

/*
 * Возвращает ID процесса.
 * Не используется ( заглушка ).
 */
int _getpid ( void ) {
    return 1;
}

const char HEAP_AND_STACK_COLLISION[] = "Heap and stack collision\n";

/*
 * Проверяем, что наши данные ( которые malloc и прочие могут
 * попробовать запросить ) не наложатся на стек.
 */
caddr_t _sbrk ( int incr ) {
    register uint32_t stack_ptr;                                        // Адресс, на котором сейчас находится указатель стека
                                                                        // ( ячейка, на которую указывает указатель пуста ).
    asm volatile ( "MRS %0, msp\n" : "=r" ( stack_ptr ) );

    uint32_t heap_end = ( uint32_t )&__bss_end__;                       // Указатель на первый байт после области .bss.

    if ( heap_end + incr >= stack_ptr ) {
        _write( ( char* )HEAP_AND_STACK_COLLISION, sizeof(HEAP_AND_STACK_COLLISION) );
        return NULL;
    }

    return ( caddr_t )stack_ptr;
}

}

