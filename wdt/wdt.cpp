#include "wdt.h"

//**********************************************************************
// Доступные пользователю функции.
//**********************************************************************
void wdt::init ( void ) const {
    volatile uint32_t sr;

    *((uint32_t *) 0xE0042008)  = 0x1DFF;				// Если процессор находится в состоянии halt, watchdog будет стоять и не мешать отладке.

    IWDG->KR = 0xCCCC;									// Запускаем сторожевой таймер, таймер стартует с значением по умолчанию 0xFFF.

    IWDG->KR = 0x5555;									// Ключ, разрешающий запись.
    while ( IWDG->SR & ( IWDG_SR_PVU | IWDG_SR_RVU ) );	// Ждем, чтобы операция загрузки значения завершилась,
                                                        // прескалер был готов к обновлению.
    IWDG->PR = 0x6;										// Деление частоты watchdog (40кгц) на 256
    while ( true ) {
        sr = IWDG->SR;
        if (!(sr&IWDG_SR_PVU)) break;
    }
    IWDG->RLR = 40 * this->cfg->startup_time / 256;
    USER_OS_STATIC_TASK_CREATE( wdt::task, "wdt_thread", F2_WDT_TASK_STACK_SIZE, ( void* )this, this->cfg->task_prio, this->task_stack, &this->task_struct );
}

void wdt::reset ( void ) const {
    IWDG->KR = 0x5555;									// Rлюч, разрешающий запись.
    IWDG->RLR = 40 * this->cfg->run_time_ms / 256;
    IWDG->KR = 0xAAAA;									// Ключ, перезагружающий таймер.
}

void wdt::reset_service	( void ) const {
    IWDG->KR = 0x5555;									// Ключ, разрешающий запись.
    IWDG->RLR = 400UL *  this->cfg->service_time_ms / 256;
    IWDG->KR = 0xAAAA;									// Ключ, перезагружающий таймер.
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

