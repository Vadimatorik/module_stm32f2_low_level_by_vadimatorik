#include "wdt.h"
#include "rcc.h"

//**********************************************************************
// Доступные пользователю функции.
//**********************************************************************
void wdt::init ( void ) const {
    *((uint32_t *) 0xE0042008)  = 0x1DFF;				// Если процессор находится в состоянии halt, watchdog будет стоять и не мешать отладке.

    IWDG->K = 0xCCCC;
    IWDG->K = 0x5555;
    IWDG->P = 0x6;
    IWDG->RL = 32 * this->cfg->startup_time_ms / 256;

    while( IWDG->S );

    IWDG->K = 0xAAAA;                                   // Перезагружаем WDT.

    USER_OS_STATIC_TASK_CREATE( this->task, "wdt_th", F2_WDT_TASK_STACK_SIZE, ( void* )this, this->cfg->task_prio, this->task_stack, &this->task_struct );
}

void wdt::reset ( void ) const {
    IWDG->K = 0x5555;									// Ключ, разрешающий запись.
    IWDG->RL = 32 * 10 * this->cfg->run_time_ms / 256;
    IWDG->K = 0xAAAA;									// Ключ, перезагружающий таймер.
}

void wdt::reset_service	( void ) const {
    IWDG->K = 0x5555;									// Ключ, разрешающий запись.
    IWDG->RL = 32 * 10 * this->cfg->service_time_ms / 256;
    IWDG->K = 0xAAAA;									// Ключ, перезагружающий таймер.
}

//**********************************************************************
// Потоки.
//**********************************************************************
void wdt::task ( void* p_obj ) {
    wdt* obj	=	(wdt *)p_obj;
    USER_OS_TICK_TYPE last_wake_time;
    const USER_OS_TICK_TYPE time_out = 10;
    last_wake_time = USER_OS_TASK_GET_TICK_COUNT();
    while ( true ) {
        configASSERT( !obj->reboot );					// Если задана перезагрузка - виснем!
        obj->reset();
        USER_OS_TASK_DELAY_UNTIL( &last_wake_time, time_out );
    }
}

