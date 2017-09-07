#include "wdt.h"

//**********************************************************************
// Доступные пользователю функции.
//**********************************************************************
void wdt::init ( void ) const {
    volatile uint32_t sr;

    *((uint32_t *) 0xE0042008)  = 0x1DFF;				// Если процессор находится в состоянии halt, watchdog будет стоять и не мешать отладке.

    IWDG->K = 0xCCCC;									// Запускаем сторожевой таймер, таймер стартует с значением по умолчанию 0xFFF.

    IWDG->K = 0x5555;									// Ключ, разрешающий запись.
    while ( IWDG->S & ( M_EC_TO_U32( EC_WDT_S_MSK::PVU ) |
                        M_EC_TO_U32( EC_WDT_S_MSK::RVU ) ) );	// Ждем, чтобы операция загрузки значения завершилась,
                                                        // прескалер был готов к обновлению.
    IWDG->P = 0x6;										// Деление частоты watchdog (40кгц) на 256
    while ( true ) {
        sr = IWDG->S;
        if ( ! ( sr & M_EC_TO_U32( EC_WDT_S_MSK::RVU ) ) )  break;
    }
    IWDG->RL = 40 * this->cfg->startup_time_ms / 256;
    USER_OS_STATIC_TASK_CREATE( this->task, "wdt_th", F2_WDT_TASK_STACK_SIZE, ( void* )this, this->cfg->task_prio, this->task_stack, &this->task_struct );
}

void wdt::reset ( void ) const {
    IWDG->K = 0x5555;									// Rлюч, разрешающий запись.
    IWDG->RL = 40 * this->cfg->run_time_ms / 256;
    IWDG->K = 0xAAAA;									// Ключ, перезагружающий таймер.
}

void wdt::reset_service	( void ) const {
    IWDG->K = 0x5555;									// Ключ, разрешающий запись.
    IWDG->RL = 400UL *  this->cfg->service_time_ms / 256;
    IWDG->K = 0xAAAA;									// Ключ, перезагружающий таймер.
}

//**********************************************************************
// Потоки.
//**********************************************************************
void wdt::task ( void* p_obj ) {
    wdt* obj	=	(wdt *)p_obj;
    USER_OS_TICK_TYPE last_wake_time;
    const USER_OS_TICK_TYPE time_out = 100;
    last_wake_time = USER_OS_TASK_GET_TICK_COUNT();
    while ( true ) {
        configASSERT( !obj->reboot );					// Если задана перезагрузка - виснем!
        obj->reset();
        USER_OS_TASK_DELAY_UNTIL( &last_wake_time, time_out );
    }
}

