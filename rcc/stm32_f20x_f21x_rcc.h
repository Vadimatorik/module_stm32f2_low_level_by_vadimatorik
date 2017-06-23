#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

#include "stm32_f20x_f21x_rcc_struct.h"

#include "stm32_f20x_f21x_rcc_struct_class_pll.h"
/**********************************************************************
 * Область template оболочек.
 **********************************************************************/
template < EC_RCC_PLL_SOURCE    S,                 // Источник тактового сигнала PLL (основного и audio).
           uint8_t              M,                 // Входная частота в PLL должна быть разделена
                                                   // этим делителем до 1-2 МГц.
                                                   // m должно находится в диапазоне 2..63 включая границы.
           uint16_t             N,                 // Этот множитель умножает частоту, полученную
                                                   // делителем выше (1-2 МГц).
                                                   // Выходная частота после этого множителя
                                                   // должна быть в диапазоне 192..432 МГц включая границы.
                                                   // n должен принимать значение в диапазоне 192..432,
                                                   // включая границы.
           EC_RCC_PLL_P         P,                 // Этот делитель делит полученную предыдущим множителем
                                                   // частоту (192..432 МГц) в частоту системной шины.
                                                   // Выходная частота не должна превышать 120 МГц.
                                                   // p должен принимать значения из EC_RCC_PLL_P.
           uint8_t              Q >                // Этот делитель делит полученную множетелем (192..432 МГц)
                                                   // для обеспечения USB OTG, SDIO, RNG.
                                                   // На выходе после этого делителя частота должна быть менее 48 МГц.
class pll_cfg : public pll_cfg_struct {
public:
    constexpr pll_cfg();

private:
    constexpr uint32_t    pllcfg_reg_msk_get         ( void );

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
     * Действия производятся без каких-либо проверок.
     */

    void    pll_main_on                     ( void ) const;
    void    pll_main_off                    ( void ) const;

    void    pll_i2s_on                      ( void ) const;
    void    pll_i2s_off                     ( void ) const;

    void    hse_clock_on                    ( void ) const;
    void    hse_clock_off                   ( void ) const;

    void    hsi_clock_on                    ( void ) const;
    void    hsi_clock_off                   ( void ) const;

    EC_ANSWER_PLL_STATUS            pll_i2s_status_get              ( void ) const;
    EC_ANSWER_PLL_STATUS            pll_main_status_get             ( void ) const;
    EC_ANSWER_PLL_READY_FLAG        pll_main_clock_ready_flag_get   ( void ) const;
    EC_ANSWER_PLL_READY_FLAG        pll_i2s_clock_ready_flag_get    ( void ) const;
    EC_ANSWER_OSCILLATOR_STATUS     hse_clock_status_get            ( void ) const;
    EC_ANSWER_OSCILLATOR_STATUS     hsi_clock_status_get            ( void ) const;
    EC_ANSWER_OSCILLATOR_STATE      hse_clock_ready_flag_get        ( void ) const;
    EC_ANSWER_OSCILLATOR_STATE      hsi_clock_ready_flag_get        ( void ) const;

    /*
     * Отключает PLL, обновляет значение, включает PLL
     */
    int     pll_cfg_update  ( uint8_t number_cfg );
private:
    const rcc_cfg*  const cfg;
};

#include "stm32_f20x_f21x_rcc_func.h"

#endif
