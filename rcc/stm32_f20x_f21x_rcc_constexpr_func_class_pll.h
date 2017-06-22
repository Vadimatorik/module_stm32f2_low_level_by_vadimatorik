#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

#include "stm32_f20x_f21x_rcc_struct.h"
//#include "stm32_f20x_f21x_rcc_struct_class_pin.h"

/**********************************************************************
 * Область constexpr конструкторов.
 **********************************************************************/
template < EC_RCC_PLL_SOURCE S, uint8_t M, uint16_t N, EC_RCC_PLL_P P, uint8_t Q >
constexpr pll_cfg< S, M, N, P, Q >::pll_cfg() {
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

#endif
