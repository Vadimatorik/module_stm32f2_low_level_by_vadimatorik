#pragma once

#include "f2_api_conf.h"

#ifdef MODULE_WDT

#include "wdt_struct.h"

struct wdt_cfg {
    uint8_t             task_prio;              // Приоритет задачи, сбрасывающий wdt.
    uint32_t            run_time_ms;            // Время перезагрузки по сторожевому таймеру.
                                                // при номинальном режиме работы системы.
    uint32_t            startup_time_ms;        // Время перезагрузки по сторожевому таймеру при запуске системы.
    uint32_t            service_time_ms;        // Время перезагрузки по сторожевому таймеру
                                                // во время сервисных операций (например, стирание и перезапись flash).
};

#define F2_WDT_TASK_STACK_SIZE      64

class wdt {
public:
    wdt( const wdt_cfg* const cfg ) : cfg(cfg) {}
            void    init            ( void ) const;
            void    reset           ( void ) const;
            void    reset_service   ( void ) const;

private:
    const wdt_cfg* const cfg;

    static  void    task    ( void* p_obj );

    mutable USER_OS_STATIC_STACK_TYPE           task_stack[ F2_WDT_TASK_STACK_SIZE ] = { 0 };
    mutable USER_OS_STATIC_TASK_STRUCT_TYPE     task_struct;

    uint8_t reboot;
};

#endif
