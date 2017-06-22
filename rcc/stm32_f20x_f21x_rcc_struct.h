#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

#include <cmath>

/**********************************************************************
 * Область enum class-ов.
 **********************************************************************/

/*
 *  Доступные источники тактового сигнала для PLL.
 */
enum class EC_RCC_PLL_SOURCE {
    HSI  = 0,
    HSE  = 1,
};

/*
 * P делитель у PLL.
 */
enum class EC_RCC_PLL_P {
    DIV_2  = 0,
    DIV_4  = 1,
    DIV_6  = 2,
    DIV_8  = 3,
};

/**********************************************************************
 * Область упакованных структур.
 **********************************************************************/

/*
 * Регистры физического модуля RCC.
 * res_x - зарезервированные области памяти RCC модуля.
 */
struct __attribute__((packed)) rcc_registers_struct {
    volatile uint32_t   c;
    volatile uint32_t   pll_cfg;
    volatile uint32_t   cfg;
    volatile uint32_t   ci;
    volatile uint32_t   ahb_1_rst;
    volatile uint32_t   ahb_2_rst;
    volatile uint32_t   ahb_3_rst;
    volatile uint32_t   res_0;
    volatile uint32_t   apb_1_rst;
    volatile uint32_t   apb_2_rst;
    volatile uint32_t   res_1;
    volatile uint32_t   res_2;
    volatile uint32_t   ahb_1_en;
    volatile uint32_t   ahb_2_en;
    volatile uint32_t   ahb_3_en;
    volatile uint32_t   res_3;
    volatile uint32_t   apb_1_en;
    volatile uint32_t   apb_2_en;
    volatile uint32_t   res_4;
    volatile uint32_t   res_5;
    volatile uint32_t   ahb_1_lp_en;
    volatile uint32_t   ahb_2_lp_en;
    volatile uint32_t   ahb_3_lp_en;
    volatile uint32_t   res_6;
    volatile uint32_t   apb_1_lp_en;
    volatile uint32_t   apb_2_lp_en;
    volatile uint32_t   res_7;
    volatile uint32_t   res_8;
    volatile uint32_t   bdc;
    volatile uint32_t   cs;
    volatile uint32_t   res_9;
    volatile uint32_t   res_10;
    volatile uint32_t   sscg;
    volatile uint32_t   pll_i2s_cfg;
};

/*
 * Описание одного режима работы PLL.
 */
struct __attribute__((packed)) pll_cfg {
    EC_RCC_PLL_SOURCE       s;  // Источник тактового сигнала PLL (основного и audio).
    uint8_t                 m;  // Входная частота в PLL должна быть разделена
                                // этим делителем до 1-2 МГц.
                                // m должно находится в диапазоне 2..63 включая границы.
    uint16_t                n;  // Этот множитель умножает частоту, полученную
                                // делителем выше (1-2 МГц).
                                // Выходная частота после этого множителя
                                // должна быть в диапазоне 192..432 МГц включая границы.
                                // n должен принимать значение в диапазоне 192..432,
                                // включая границы.
    EC_RCC_PLL_P            p;  // Этот делитель делит полученную предыдущим множителем
                                // частоту (192..432 МГц) в частоту системной шины.
                                // Выходная частота не должна превышать 120 МГц.
                                // p должен принимать значения из EC_RCC_PLL_P.
    uint8_t                 q;  // Этот делитель делит полученную множетелем (192..432 МГц)
                                // для обеспечения USB OTG, SDIO, RNG.
                                // На выходе после этого делителя частота должна быть менее 48 МГц.
};

/**********************************************************************
 * Область структур.
 **********************************************************************/

/*
 * Структура инициализации объекта класса RCC.
 */
struct rcc_cfg {
    const pll_cfg*          const pll;          // Режимы основного PLL.
    uint8_t                 pll_count;          // Количество режимов основного PLL.
};

/**********************************************************************
 * Область template оболочек.
 **********************************************************************/
template < EC_RCC_PLL_SOURCE    S,
           uint8_t              M,
           uint16_t             N,
           EC_RCC_PLL_P         P,
           uint8_t              Q >
class pll_cfg_check_param : public pll_cfg {
public:
    constexpr pll_cfg_check_param(): pll_cfg( {
        .s = S,
        .m = M,
        .n = N,
        .p = P,
        .q = Q,
    } ) {
            static_assert( ( M >= 2 ) || ( M <= 63 ), "Invalid parameter M! 2 <=  M <= 63!" );
            static_assert( ( N >= 192 ) || ( N <= 432 ), "Invalid parameter N! 192 <= N <= 432!" );
            static_assert( ( P >= EC_RCC_PLL_P::DIV_2) || ( P <= EC_RCC_PLL_P::DIV_8 ), "Invalid parameter P! P may be DIV_2, DIV_4, DIV_6, DIV_8!" );
            static_assert( ( Q >= 2) || ( Q <= 15 ), "Invalid parameter Q! 2 <= Q <= 15" );

            // Далее получаем входную частоту, на основе которой будем проверять, проходят ли делители.
            const uint32_t clock = ( S == EC_RCC_PLL_SOURCE::HSI )?16000000:HSE_VALUE;

            static_assert( ((clock / M) >= 1000000) || ((clock / M) <= 2000000), "The coefficient M in the pll_cfg structure is incorrect!" );
            const uint32_t clock_after_m = clock / M;

            static_assert( ((clock_after_m * N) >= 192000000) || ((clock_after_m * N) <= 432000000), "The coefficient N in the pll_cfg structure is incorrect!" );
            const uint32_t clock_after_n = clock_after_m * N;

            const uint8_t dev_p = static_cast<uint8_t>(pow(2, static_cast<uint8_t>(P) + 1));
            static_assert( clock_after_n / dev_p <= 120000000, "The coefficient P in the pll_cfg structure is incorrect!" );

            static_assert( clock_after_n / Q <= 48000000, "The coefficient Q in the pll_cfg structure is incorrect!" );
    };
};

#endif
