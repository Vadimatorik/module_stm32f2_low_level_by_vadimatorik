#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

#include "stm32_f20x_f21x_rcc_struct.h"

#include "stm32_f20x_f21x_rcc_struct_class_pll.h"

/**********************************************************************
 * Область template оболочек.
 **********************************************************************/
template < EC_RCC_PLL_SOURCE    S,                 // Источник тактового сигнала PLL (основного и audio).
           uint8_t              M,                 /*
                                                    * Входная частота в PLL должна быть разделена
                                                    * этим делителем до 1-2 МГц.
                                                    * m должно находится в диапазоне 2..63 включая границы.
                                                    */
           uint16_t             N,                 /*
                                                    * Этот множитель умножает частоту, полученную
                                                    * делителем выше (1-2 МГц).
                                                    * Выходная частота после этого множителя
                                                    * должна быть в диапазоне 192..432 МГц включая границы.
                                                    * n должен принимать значение в диапазоне 192..432,
                                                    * включая границы.
                                                    */
           EC_RCC_PLL_P         P,                 /*
                                                    * Этот делитель делит полученную предыдущим множителем
                                                    * частоту (192..432 МГц) в частоту системной шины.
                                                    * Выходная частота не должна превышать 120 МГц.
                                                    * p должен принимать значения из EC_RCC_PLL_P.
                                                    */
           uint8_t              Q,                 /*
                                                    * Этот делитель делит полученную множетелем (192..432 МГц)
                                                    * для обеспечения USB OTG, SDIO, RNG.
                                                    * На выходе после этого делителя частота должна быть менее 48 МГц.
                                                    */
           EC_RCC_AHB_DIV       AHB,               /*
                                                    * Этот делитель делит полученную коэффициентом P (до 120 МГц) частоту
                                                    * до частоты работы шины AHB. Максимум шины = 120.
                                                    */
           EC_RCC_APB1_DIV      APB1,              /*
                                                    * Этот делитель делит частоту шины AHB
                                                    * до частоты работы шины APB1. Максимум шины = 30 МГц.
                                                    */
           EC_RCC_APB2_DIV      APB2 >             /*
                                                    * Этот делитель делит частоту шины AHB
                                                    * до частоты работы шины APB2. Максимум шины = 60 МГц.
                                                    */
class pll_cfg : public pll_cfg_struct {
public:
    constexpr pll_cfg();

private:
    constexpr uint32_t  pllcfg_reg_msk_get              ( void );
    constexpr uint32_t  dev_bus_msk_get                 ( void );
};

#include "stm32_f20x_f21x_rcc_constexpr_func_class_pll.h"

/**********************************************************************
 * Область class-ов.
 **********************************************************************/

/*
 * По средствам объекта данного класса производятся все манипуляции
 * с частотами микркоконтроллера.
 */
class rcc {
public:
    constexpr rcc( const rcc_cfg* const cfg );

    /*
     * 1.  Включает HSE или HSI (в зависимости от того, от чего будет тактироваться PLL).
     * 2.  Дожидается стабилизации источника тактирования.
     * 3.  Переключает ядро на выбранный только что стабилизировавшийся источник.
     * 4.  Ждет, пока произойдет переключение.
     * 5.  Выставляет делители по-умолчанию для шин APB1, APB2, AHB
     *     ( т.к. тактирование идет либо от 16 МГц HSI или от <= 25 МГц HSE, деление не нужно).
     * 6.  Отключает PLL.
     * 7.  Выставляет заданную конфигурацию PLL.
     * 8.  Включает PLL.
     * 9.  Высталяет заданную конфигурацию делителей шин APB1, APB2, AHB.
     * 10. Дожидается стабилизации PLL.
     * 11. Переключает тактирование ядра на PLL.
     * 12. Ждет, пока ядро переключится.
     */
    int     pll_cfg_update  ( uint8_t number_cfg ) const;

private:

    /*
     * Действия производятся без каких-либо проверок.
     */

    static void    pll_main_on              ( void );                                         // Включет основной PLL (конфигурация должна быть заданна заранее).
    static void    pll_main_off             ( void );                                         // Отключает основной PLL (ядро должно тактироваться от другого источника).

    static void    pll_i2s_on               ( void );                                         // Включает I2S PLL (конфигурация должна быть заданна заранее).
    static void    pll_i2s_off              ( void );                                         // Отключает I2S PLL.

    static void    hse_clock_on             ( void );                                         // Включает внешний источник тактового сигнала.
    static void    hse_clock_off            ( void );                                         // Отключает внешний источник.

    static void    hsi_clock_on             ( void );                                         // Запускает внутренний источник тактового сигнала.
    static void    hsi_clock_off            ( void );                                         // Отключает внутренний источник тактового сигнала.

    static void    sw_hsi_set               ( void );                                         // Переключает ядро на HSI.
    static void    sw_hse_set               ( void );                                         // Переключает ядро на HSE.
    static void    sw_pll_set               ( void );                                         // Переключает ядро на PLL.

    static void    dev1_bus_set             ( void );                                         // Выставляет делители APB1, APB2, AHB в 1.
           void    dev_bus_set              ( uint8_t &number_cfg ) const;                    // Метод выставляет делители частоты на для шин, рассчитаные на этапе компиляции.

           void    pll_set_cfg              ( uint8_t &number_cfg ) const;                    // Метод выставляет выбранную конфигурацию без провекри в PLL (конфигурация должна существовать,
                                                                                              // PLL должен быть отключен).

    static EC_ANSWER_RCC_SWS_STATUS        sw_status_get                   ( void );          // Возвращает источние сообщение о том, от какого источника тактируется ядро.

    static EC_ANSWER_PLL_STATUS            pll_main_status_get             ( void );          // Проверят, включен ли основной PLL.
    static EC_ANSWER_PLL_STATUS            pll_i2s_status_get              ( void );          // Проверят, включен ли I2S PLL.

    static EC_ANSWER_PLL_READY_FLAG        pll_main_clock_ready_flag_get   ( void );          // Проверяет, стабилизировалась ли частота на основном PLL.
    static EC_ANSWER_PLL_READY_FLAG        pll_i2s_clock_ready_flag_get    ( void );          // Проверяет, стабилизировалась ли частота на I2S PLL.

    static EC_ANSWER_OSCILLATOR_STATUS     hse_clock_status_get            ( void );          // Проверяет, включен ли внешний источник тактового сигнала или нет.
    static EC_ANSWER_OSCILLATOR_STATUS     hsi_clock_status_get            ( void );          // Проверяет, включен ли внутренний источник тактового сигнала или нет.

    static EC_ANSWER_OSCILLATOR_STATE      hse_clock_ready_flag_get        ( void );          // Проверяет, готов ли внешний источник тактового сигнала стать источникм тактирования.
    static EC_ANSWER_OSCILLATOR_STATE      hsi_clock_ready_flag_get        ( void );          // Проверяет, готов ли внутренний источник тактирования сигнала стать источникм тактирования.

    const rcc_cfg*  const cfg;
};

#include "stm32_f20x_f21x_rcc_func.h"

#endif
