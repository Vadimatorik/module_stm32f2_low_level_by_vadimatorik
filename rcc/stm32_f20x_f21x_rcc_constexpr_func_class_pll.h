#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

#include "stm32_f20x_f21x_rcc_struct.h"
#include "stm32_f20x_f21x_rcc_struct_class_pll.h"

/*
 * Метод возвращвет числовое значение делителя из enum class-а EC_RCC_AHB_DIV.
 */
constexpr uint16_t ahb_dev_ec_to_uint16_t_value( EC_RCC_AHB_DIV AHB ) {
    uint16_t value_result = 1;      // 1, чтобы не ругался компилятор. Структура была проверена ранее и параметр там точно верный.
    switch( AHB ) {
    case EC_RCC_AHB_DIV::DIV_1:     value_result = 1;   break;
    case EC_RCC_AHB_DIV::DIV_2:     value_result = 2;   break;
    case EC_RCC_AHB_DIV::DIV_4:     value_result = 4;   break;
    case EC_RCC_AHB_DIV::DIV_8:     value_result = 8;   break;
    case EC_RCC_AHB_DIV::DIV_16:    value_result = 16;  break;
    case EC_RCC_AHB_DIV::DIV_64:    value_result = 64;  break;
    case EC_RCC_AHB_DIV::DIV_128:   value_result = 128; break;
    case EC_RCC_AHB_DIV::DIV_256:   value_result = 256; break;
    case EC_RCC_AHB_DIV::DIV_512:   value_result = 512; break;
    }
    return value_result;
}

/*
 * Метод возвращвет числовое значение делителя из enum class-а EC_RCC_APB1_DIV.
 */
constexpr uint8_t apb1_dev_ec_to_uint8_t_value( EC_RCC_APB1_DIV APB1 ) {
    uint8_t value_result = 1;
    switch( APB1 ) {
    case EC_RCC_APB1_DIV::DIV_1:     value_result = 1;   break;
    case EC_RCC_APB1_DIV::DIV_2:     value_result = 2;   break;
    case EC_RCC_APB1_DIV::DIV_4:     value_result = 4;   break;
    case EC_RCC_APB1_DIV::DIV_8:     value_result = 8;   break;
    case EC_RCC_APB1_DIV::DIV_16:    value_result = 16;  break;
    }
    return value_result;
}

/*
 * Метод возвращвет числовое значение делителя из enum class-а EC_RCC_APB2_DIV.
 */
constexpr uint8_t apb2_dev_ec_to_uint8_t_value( EC_RCC_APB2_DIV APB2 ) {
    uint8_t value_result = 1;
    switch( APB2 ) {
    case EC_RCC_APB2_DIV::DIV_1:     value_result = 1;   break;
    case EC_RCC_APB2_DIV::DIV_2:     value_result = 2;   break;
    case EC_RCC_APB2_DIV::DIV_4:     value_result = 4;   break;
    case EC_RCC_APB2_DIV::DIV_8:     value_result = 8;   break;
    case EC_RCC_APB2_DIV::DIV_16:    value_result = 16;  break;
    }
    return value_result;
}

/**********************************************************************
 * Область constexpr конструкторов.
 **********************************************************************/
template < EC_RCC_PLL_SOURCE S, uint8_t M, uint16_t N, EC_RCC_PLL_P P, uint8_t Q, EC_RCC_AHB_DIV AHB, EC_RCC_APB1_DIV APB1, EC_RCC_APB2_DIV APB2 >
constexpr pll_cfg< S, M, N, P, Q, AHB, APB1, APB2 >::pll_cfg() : pll_cfg_struct( {
    .pllcfg_reg_msk = pllcfg_reg_msk_get(),
    .dev_bus_msk    = dev_bus_msk_get()
} ) {
    /*
     * Проверяем, не выходят ли коэффициенты за пределы.
     */
    static_assert( ( M >= 2 ) || ( M <= 63 ), "Invalid parameter M! 2 <=  M <= 63!" );
    static_assert( ( N >= 192 ) || ( N <= 432 ), "Invalid parameter N! 192 <= N <= 432!" );
    static_assert( ( P >= EC_RCC_PLL_P::DIV_2) || ( P <= EC_RCC_PLL_P::DIV_8 ), "Invalid parameter P! P may be DIV_2, DIV_4, DIV_6, DIV_8!" );
    static_assert( ( Q >= 2) || ( Q <= 15 ), "Invalid parameter Q! 2 <= Q <= 15" );

    /*
     * Проверяем, не выходит ли полученная частота за пределы.
     */
    // Далее получаем входную частоту, на основе которой будем проверять, проходят ли делители.
    const uint32_t clock = ( S == EC_RCC_PLL_SOURCE::HSI ) ? 16000000 : HSE_VALUE;

    static_assert( ( clock / M >= 1000000 ) || ( clock / M <= 2000000 ), "The coefficient M in the pll_cfg structure is incorrect!" );
    const uint32_t clock_after_m = clock / M;

    static_assert( ( clock_after_m * N  >= 192000000 ) || ( clock_after_m * N  <= 432000000 ), "The coefficient N in the pll_cfg structure is incorrect!" );
    const uint32_t clock_after_n = clock_after_m * N;

    const uint8_t dev_p = static_cast< uint8_t >( pow( 2, static_cast< uint8_t >( P ) + 1 ) );
    static_assert( clock_after_n / dev_p <= 120000000, "The coefficient P in the pll_cfg structure is incorrect!" );
    const uint32_t clock_after_p = clock_after_n / dev_p;

    static_assert( clock_after_n / Q <= 48000000, "The coefficient Q in the pll_cfg structure is incorrect!" );

    /*
     * Проверяем делители шин.
     */
    const uint16_t dev_ahb = ahb_dev_ec_to_uint16_t_value( AHB );
    static_assert( clock_after_p / dev_ahb <= 120000000, "The coefficient AHB in the pll_cfg structure is incorrect!" );            // На AHB <= 120 МГц.
    const uint32_t clock_ahb = clock_after_p / dev_ahb;

    const uint16_t dev_apb1 = apb1_dev_ec_to_uint8_t_value( APB1 );
    static_assert( clock_ahb / dev_apb1 <= 30000000, "The coefficient APB1 in the pll_cfg structure is incorrect!" );               // На APB1 <= 30 МГц.

    const uint16_t dev_apb2 = apb2_dev_ec_to_uint8_t_value( APB2 );
    static_assert( clock_ahb / dev_apb2 <= 60000000, "The coefficient APB2 in the pll_cfg structure is incorrect!" );               // На APB2 <= 60 МГц.
};

/**********************************************************************
 * Область constexpr функций.
 **********************************************************************/
template < EC_RCC_PLL_SOURCE S, uint8_t M, uint16_t N, EC_RCC_PLL_P P, uint8_t Q, EC_RCC_AHB_DIV AHB, EC_RCC_APB1_DIV APB1, EC_RCC_APB2_DIV APB2 >
constexpr uint32_t pll_cfg< S, M, N, P, Q, AHB, APB1, APB2 >::pllcfg_reg_msk_get( void ) {
    uint32_t pllcfg_reg_msk = 0;

    pllcfg_reg_msk  |= static_cast< uint8_t >( S )    << static_cast< uint8_t >( EC_PLLCFG_REG_BIT_FIELD_POSITION::S );
    pllcfg_reg_msk  |= static_cast< uint8_t >( M )    << static_cast< uint8_t >( EC_PLLCFG_REG_BIT_FIELD_POSITION::M );
    pllcfg_reg_msk  |= static_cast< uint8_t >( P )    << static_cast< uint8_t >( EC_PLLCFG_REG_BIT_FIELD_POSITION::P );
    pllcfg_reg_msk  |= static_cast< uint8_t >( Q )    << static_cast< uint8_t >( EC_PLLCFG_REG_BIT_FIELD_POSITION::Q );
    pllcfg_reg_msk  |= static_cast< uint16_t >( N )   << static_cast< uint16_t >( EC_PLLCFG_REG_BIT_FIELD_POSITION::N );

    return pllcfg_reg_msk;
}

/*
 * Метод возвращает маску для задания делителей на шине.
 */
template < EC_RCC_PLL_SOURCE S, uint8_t M, uint16_t N, EC_RCC_PLL_P P, uint8_t Q, EC_RCC_AHB_DIV AHB, EC_RCC_APB1_DIV APB1, EC_RCC_APB2_DIV APB2 >
constexpr uint32_t pll_cfg< S, M, N, P, Q, AHB, APB1, APB2 >::dev_bus_msk_get( void ) {
    uint32_t dev_bus_msk = 0;

    dev_bus_msk  |= static_cast< uint8_t >( AHB )   << static_cast< uint8_t >( EC_CFG_REG_BIT_FIELD_POS::HPRE );
    dev_bus_msk  |= static_cast< uint8_t >( APB1 )  << static_cast< uint8_t >( EC_CFG_REG_BIT_FIELD_POS::PPRE1 );
    dev_bus_msk  |= static_cast< uint8_t >( APB2 )  << static_cast< uint8_t >( EC_CFG_REG_BIT_FIELD_POS::PPRE2 );

    return dev_bus_msk;
}

#endif

