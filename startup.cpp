#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "f2_api_conf.h"

/*
 * В данном файле находится таблица векторов-прерываний (указатель на вершину стека + массив
 * указателей на функции), а так же функции-заглушеки (while(1) {}; циклы) для неиспользуемых
 * прерываний (на каждый вектор прерывания своя заглушка, для более удобной фиксации причины
 * остановки программы).
 * */

/*
 * Данные значения (указатели на области памяти контроллера) берутся из section.ld файла.
 */
extern uint32_t _sidata;        // Начальный адрес содержимого .data области во flash
                                // (то, что будет скопировано в RAM).
extern uint32_t _sdata;         // Начальный адрес .data области в RAM
                                // (то, что будет скопировано с области по указателю _sidata (из flash в ram).
extern uint32_t _edata;         // Конечный адрес .data области в RAM (проверяется операцией <, т.к. байт,
                                // адрес которого записан в эту переменную, копировать не нужно. Только то,
                                // что до него).

extern uint32_t __bss_start__;  // Начальный и адрес BSS области
                                // (будет заполнено 0-ми. Стирать нужно уже с этого адреса).
extern uint32_t __bss_end__;    // Конечный адрес BSS области.
                                // (По этому адресу записывать уже не нужно (проверяется по <)).
extern uint32_t _stack;         // Вершина стека (конец RAM).

extern void (*__preinit_array_start[])(void) __attribute__((weak));
extern void (*__preinit_array_end[])(void) __attribute__((weak));
extern void (*__init_array_start[])(void) __attribute__((weak));
extern void (*__init_array_end[])(void) __attribute__((weak));
extern void (*__fini_array_start[])(void) __attribute__((weak));
extern void (*__fini_array_end[])(void) __attribute__((weak));

/*
 * У каждого handler-а есть свое тело.
 * В случае, если пользователь не объявил его у себя в коде - используется тело-заглушка
 * на основе слабой ссылки (дополнительная надежность и удобство при отладке).
 */
void __attribute__( ( weak ) ) nmi_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) hard_fault_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) mem_manage_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) bus_fault_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) usage_fault_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) sv_call_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) debug_monitor_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) pend_sv_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) sys_tick_handler( void ) { while( true ); }

void __attribute__( ( weak ) ) wwdg_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) pvd_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tamp_stamp_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) rtc_wkup_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) flash_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) rcc_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) exti_0_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) exti_1_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) exti_2_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) exti_3_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) exti_4_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma1_stream0_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma1_stream1_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma1_stream2_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma1_stream3_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma1_stream4_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma1_stream5_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma1_stream6_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) adc_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) can1_tx_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) can1_rx0_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) can1_rx1_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) can1_sce_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) exti_9_5_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim1_brk_and_tim9_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim1_up_and_tim10_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim1_trg_com_and_tim11_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim1_capture_compare_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim2_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim3_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim4_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) i2c1_ev_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) i2c1_er_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) i2c2_ev_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) i2c2_er_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) spi1_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) spi2_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) usart1_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) usart2_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) usart3_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) exti_15_10_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) rtc_alarm_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) otg_fs_wkup_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim8_brk_and_tim12_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim8_up_and_tim13_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim8_trg_com_and_tim14_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim8_cc_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma1_stream7_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) fsmc_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) sdio_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim5_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) spi3_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) uart4_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) uart5_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim6_and_dac_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) tim7_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma2_stream0_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma2_stream1_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma2_stream2_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma2_stream3_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma2_stream4_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) eth_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) eth_wkup_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) can2_tx_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) can2_rx0_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) can2_rx1_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) can2_sce_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) otg_fs_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma2_stream5_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma2_stream6_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dma2_stream7_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) usart6_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) i2c3_ev_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) i2c3_er_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) otg_hs_ep1_out_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) otg_hs_ep1_in_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) otg_hs_wkup_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) otg_hs_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) dcmi_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) cryp_handler( void ) { while( true ); }
void __attribute__( ( weak ) ) hash_and_rng_handler( void ) { while( true ); }

// Выполнение программы начинается с данного метода.
void reset_handler ( void );

/*
 * Вершина стека (указатель на последний байт RAM) + таблица указателей на функции-обработчики.
 * В случае, если пользователь не использует собственные функции для какого-либо из векторов прерываний,
 * используются заглушки по-умолчанию (описаны выше).
 */
__attribute__( (used, section( ".irq_table" ) ) )
const void *interrupt_vectors[] =
{
    M_ISR_TO_CONST_P_VOID(&_stack),
    M_ISR_TO_CONST_P_VOID(reset_handler),
    M_ISR_TO_CONST_P_VOID(nmi_handler),
    M_ISR_TO_CONST_P_VOID(hard_fault_handler),
    M_ISR_TO_CONST_P_VOID(mem_manage_handler),
    M_ISR_TO_CONST_P_VOID(bus_fault_handler),
    M_ISR_TO_CONST_P_VOID(usage_fault_handler),
    M_ISR_TO_CONST_P_VOID(0),
    M_ISR_TO_CONST_P_VOID(0),
    M_ISR_TO_CONST_P_VOID(0),
    M_ISR_TO_CONST_P_VOID(0),
    M_ISR_TO_CONST_P_VOID(sv_call_handler),
    M_ISR_TO_CONST_P_VOID(debug_monitor_handler),
    M_ISR_TO_CONST_P_VOID(0),
    M_ISR_TO_CONST_P_VOID(pend_sv_handler),
    M_ISR_TO_CONST_P_VOID(sys_tick_handler),
  
    // Прерывания от периферии.
    M_ISR_TO_CONST_P_VOID(wwdg_handler),
    M_ISR_TO_CONST_P_VOID(pvd_handler),
    M_ISR_TO_CONST_P_VOID(tamp_stamp_handler),
    M_ISR_TO_CONST_P_VOID(rtc_wkup_handler),
    M_ISR_TO_CONST_P_VOID(flash_handler),
    M_ISR_TO_CONST_P_VOID(rcc_handler),
    M_ISR_TO_CONST_P_VOID(exti_0_handler),
    M_ISR_TO_CONST_P_VOID(exti_1_handler),
    M_ISR_TO_CONST_P_VOID(exti_2_handler),
    M_ISR_TO_CONST_P_VOID(exti_3_handler),
    M_ISR_TO_CONST_P_VOID(exti_4_handler),
    M_ISR_TO_CONST_P_VOID(dma1_stream0_handler),
    M_ISR_TO_CONST_P_VOID(dma1_stream1_handler),
    M_ISR_TO_CONST_P_VOID(dma1_stream2_handler),
    M_ISR_TO_CONST_P_VOID(dma1_stream3_handler),
    M_ISR_TO_CONST_P_VOID(dma1_stream4_handler),
    M_ISR_TO_CONST_P_VOID(dma1_stream5_handler),
    M_ISR_TO_CONST_P_VOID(dma1_stream6_handler),
    M_ISR_TO_CONST_P_VOID(adc_handler),
    M_ISR_TO_CONST_P_VOID(can1_tx_handler),
    M_ISR_TO_CONST_P_VOID(can1_rx0_handler),
    M_ISR_TO_CONST_P_VOID(can1_rx1_handler),
    M_ISR_TO_CONST_P_VOID(can1_sce_handler),
    M_ISR_TO_CONST_P_VOID(exti_9_5_handler),
    M_ISR_TO_CONST_P_VOID(tim1_brk_and_tim9_handler),
    M_ISR_TO_CONST_P_VOID(tim1_up_and_tim10_handler),
    M_ISR_TO_CONST_P_VOID(tim1_trg_com_and_tim11_handler),
    M_ISR_TO_CONST_P_VOID(tim1_capture_compare_handler),
    M_ISR_TO_CONST_P_VOID(tim2_handler),
    M_ISR_TO_CONST_P_VOID(tim3_handler),
    M_ISR_TO_CONST_P_VOID(tim4_handler),
    M_ISR_TO_CONST_P_VOID(i2c1_ev_handler),
    M_ISR_TO_CONST_P_VOID(i2c1_er_handler),
    M_ISR_TO_CONST_P_VOID(i2c2_ev_handler),
    M_ISR_TO_CONST_P_VOID(i2c2_er_handler),
    M_ISR_TO_CONST_P_VOID(spi1_handler),
    M_ISR_TO_CONST_P_VOID(spi2_handler),
    M_ISR_TO_CONST_P_VOID(usart1_handler),
    M_ISR_TO_CONST_P_VOID(usart2_handler),
    M_ISR_TO_CONST_P_VOID(usart3_handler),
    M_ISR_TO_CONST_P_VOID(exti_15_10_handler),
    M_ISR_TO_CONST_P_VOID(rtc_alarm_handler),
    M_ISR_TO_CONST_P_VOID(otg_fs_wkup_handler),
    M_ISR_TO_CONST_P_VOID(tim8_brk_and_tim12_handler),
    M_ISR_TO_CONST_P_VOID(tim8_up_and_tim13_handler),
    M_ISR_TO_CONST_P_VOID(tim8_trg_com_and_tim14_handler),
    M_ISR_TO_CONST_P_VOID(tim8_cc_handler),
    M_ISR_TO_CONST_P_VOID(dma1_stream7_handler),
    M_ISR_TO_CONST_P_VOID(fsmc_handler),
    M_ISR_TO_CONST_P_VOID(sdio_handler),
    M_ISR_TO_CONST_P_VOID(tim5_handler),
    M_ISR_TO_CONST_P_VOID(spi3_handler),
    M_ISR_TO_CONST_P_VOID(uart4_handler),
    M_ISR_TO_CONST_P_VOID(uart5_handler),
    M_ISR_TO_CONST_P_VOID(tim6_and_dac_handler),
    M_ISR_TO_CONST_P_VOID(tim7_handler),
    M_ISR_TO_CONST_P_VOID(dma2_stream0_handler),
    M_ISR_TO_CONST_P_VOID(dma2_stream1_handler),
    M_ISR_TO_CONST_P_VOID(dma2_stream2_handler),
    M_ISR_TO_CONST_P_VOID(dma2_stream3_handler),
    M_ISR_TO_CONST_P_VOID(dma2_stream4_handler),
    M_ISR_TO_CONST_P_VOID(eth_handler),
    M_ISR_TO_CONST_P_VOID(eth_wkup_handler),
    M_ISR_TO_CONST_P_VOID(can2_tx_handler),
    M_ISR_TO_CONST_P_VOID(can2_rx0_handler),
    M_ISR_TO_CONST_P_VOID(can2_rx1_handler),
    M_ISR_TO_CONST_P_VOID(can2_sce_handler),
    M_ISR_TO_CONST_P_VOID(otg_fs_handler),
    M_ISR_TO_CONST_P_VOID(dma2_stream5_handler),
    M_ISR_TO_CONST_P_VOID(dma2_stream6_handler),
    M_ISR_TO_CONST_P_VOID(dma2_stream7_handler),
    M_ISR_TO_CONST_P_VOID(usart6_handler),
    M_ISR_TO_CONST_P_VOID(i2c3_ev_handler),
    M_ISR_TO_CONST_P_VOID(i2c3_er_handler),
    M_ISR_TO_CONST_P_VOID(otg_hs_ep1_out_handler),
    M_ISR_TO_CONST_P_VOID(otg_hs_ep1_in_handler),
    M_ISR_TO_CONST_P_VOID(otg_hs_wkup_handler),
    M_ISR_TO_CONST_P_VOID(otg_hs_handler),
    M_ISR_TO_CONST_P_VOID(dcmi_handler),
    M_ISR_TO_CONST_P_VOID(cryp_handler),
    M_ISR_TO_CONST_P_VOID(hash_and_rng_handler)
};

/*
 * Функции, необходимые для начальной инициализации контроллера.
 */

/* Заполняем 0-ми bss в RAM. */
inline void __attribute__( ( always_inline ) ) __initialize_data ( uint32_t* from, uint32_t* section_begin, uint32_t* section_end ) {
    uint32_t *p = section_begin;
    while ((uint32_t)p < (uint32_t)section_end) {
        *p++ = *from++;
    }
}

/* Копируем область ".data" из flash в ram. */
inline void __attribute__( ( always_inline ) ) __initialize_bss ( uint32_t* section_begin, uint32_t* section_end ) {
    uint32_t* p = section_begin;
    while ( p < section_end ) {
        *p++ = 0;
    }
}

/*
 * Производим все необходимые инициализации для C++.
 */
inline void __attribute__( ( always_inline ) ) __libc_init_array ( void ) {
    size_t count;
    size_t i;

    count = __preinit_array_end - __preinit_array_start;
    for(i = 0; i < count; i++)
        __preinit_array_start[i]();

    count = __init_array_end - __init_array_start;
    for(i = 0; i < count; i++)
        __init_array_start[i]();
}

/*
 * С этого метода начинается выполнение программы.
 * В нем производится инициализация RAM,
 * после чего управление передается программе пользователя.
 */

extern int main ( void );                                   // Функция main должна быть объявлена в коде пользователя.

void reset_handler ( void ) {
    __initialize_data( &_sidata, &_sdata, &_edata );        // Копируем начальные значения изменяемых данных в ram.
    __initialize_bss( &__bss_start__, &__bss_end__ );       // Заполняем bss область нулями.
    __libc_init_array();                                    // Я не знаю точно, как назвать это...
    main();
}

#ifdef __cplusplus
}
#endif

