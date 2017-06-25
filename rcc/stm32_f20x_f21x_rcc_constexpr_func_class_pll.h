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
template < EC_RCC_PLL_SOURCE S, uint8_t M, uint16_t N, EC_RCC_PLL_P P, uint8_t Q, EC_RCC_AHB_DIV AHB, EC_RCC_APB1_DIV APB1, EC_RCC_APB2_DIV APB2, uint32_t VOLTAGE_MV >
constexpr pll_cfg< S, M, N, P, Q, AHB, APB1, APB2, VOLTAGE_MV >::pll_cfg() : pll_cfg_struct( {
    .pllcfg_reg_msk = this->pllcfg_reg_msk_get(),
    .dev_bus_msk    = this->dev_bus_msk_get(),
    .flash_acr_msk  = this->flash_acr_msk_get(),
    .src            = ( S == EC_RCC_PLL_SOURCE::HSE ) ? true : false
} ) {
    /*
     * Проверяем диапазон напряжений питания микроконтроллера.
     */
    static_assert( ( VOLTAGE_MV <= 3600 ) && ( VOLTAGE_MV >= 1650 ), "Wrong voltage value. The voltage should range from 1650 mV to 3600 mV." );

    /*
     * Источник тактового сигнала.
     */
    static_assert( ( S == EC_RCC_PLL_SOURCE::HSE ) || ( S == EC_RCC_PLL_SOURCE::HSI ), "Wrong source selected ( Param S )! Source may be HSE or HSI!" );

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
template < EC_RCC_PLL_SOURCE S, uint8_t M, uint16_t N, EC_RCC_PLL_P P, uint8_t Q, EC_RCC_AHB_DIV AHB, EC_RCC_APB1_DIV APB1, EC_RCC_APB2_DIV APB2, uint32_t VOLTAGE_MV >
constexpr uint32_t pll_cfg< S, M, N, P, Q, AHB, APB1, APB2, VOLTAGE_MV >::pllcfg_reg_msk_get( void ) {
    uint32_t msk = 0;

    msk  |= M_EC_TO_U8(S) << M_EC_TO_U8(EC_PLLCFG_REG_BIT_FIELD_POSITION::S);
    msk  |= M_EC_TO_U8(M) << M_EC_TO_U8(EC_PLLCFG_REG_BIT_FIELD_POSITION::M);
    msk  |= M_EC_TO_U8(P) << M_EC_TO_U8(EC_PLLCFG_REG_BIT_FIELD_POSITION::P);
    msk  |= M_EC_TO_U8(Q) << M_EC_TO_U8(EC_PLLCFG_REG_BIT_FIELD_POSITION::Q);
    msk  |= M_EC_TO_U8(N) << M_EC_TO_U8(EC_PLLCFG_REG_BIT_FIELD_POSITION::N);

    return msk;
}

/*
 * Метод возвращает маску для задания делителей на шине.
 */
template < EC_RCC_PLL_SOURCE S, uint8_t M, uint16_t N, EC_RCC_PLL_P P, uint8_t Q, EC_RCC_AHB_DIV AHB, EC_RCC_APB1_DIV APB1, EC_RCC_APB2_DIV APB2, uint32_t VOLTAGE_MV >
constexpr uint32_t pll_cfg< S, M, N, P, Q, AHB, APB1, APB2, VOLTAGE_MV >::dev_bus_msk_get( void ) {
    uint32_t msk = 0;

    msk  |= M_EC_TO_U8(AHB)  << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::HPRE);
    msk  |= M_EC_TO_U8(APB1) << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::PPRE1);
    msk  |= M_EC_TO_U8(APB2) << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::PPRE2);

    return msk;
}

/*
 * Достаем частоту тактирования SYSCLK.
 */
template < EC_RCC_PLL_SOURCE S, uint8_t M, uint16_t N, EC_RCC_PLL_P P, uint8_t Q, EC_RCC_AHB_DIV AHB, EC_RCC_APB1_DIV APB1, EC_RCC_APB2_DIV APB2, uint32_t VOLTAGE_MV >
constexpr uint32_t pll_cfg< S, M, N, P, Q, AHB, APB1, APB2, VOLTAGE_MV >::hclk_get( void ) {
    const uint32_t clock = ( S == EC_RCC_PLL_SOURCE::HSI ) ? 16000000 : HSE_VALUE;
    const uint8_t dev_p = M_EC_TO_U8( pow( 2, M_EC_TO_U8(P) + 1 ) );
    const uint32_t hclk = clock * ( N / M ) / dev_p;
    return hclk;
}

/*
 * Метод возвращает маску для задания задержки считывания данных из
 * flash + включения предсказателя.
 */
template < EC_RCC_PLL_SOURCE S, uint8_t M, uint16_t N, EC_RCC_PLL_P P, uint8_t Q, EC_RCC_AHB_DIV AHB, EC_RCC_APB1_DIV APB1, EC_RCC_APB2_DIV APB2, uint32_t VOLTAGE_MV >
constexpr uint32_t pll_cfg< S, M, N, P, Q, AHB, APB1, APB2, VOLTAGE_MV >::flash_acr_msk_get ( void ) {
    uint8_t wait = 0;
    const uint32_t hclk = this->hclk_get();
    uint32_t msk = 0;
    /*
     * Подбираем задержку относительно напряжения питания.
     */
    if ( ( VOLTAGE_MV >= 1650 ) && ( VOLTAGE_MV < 2100 ) ) {
        if ( ( hclk > 0 ) && ( hclk <= 16000000 ) )                wait = 0;
        if ( ( hclk > 16000000 )    && ( hclk <= 32000000 ) )      wait = 1;
        if ( ( hclk > 32000000 )    && ( hclk <= 48000000 ) )      wait = 2;
        if ( ( hclk > 48000000 )    && ( hclk <= 64000000 ) )      wait = 3;
        if ( ( hclk > 64000000 )    && ( hclk <= 80000000 ) )      wait = 4;
        if ( ( hclk > 80000000 )    && ( hclk <= 96000000 ) )      wait = 5;
        if ( ( hclk > 96000000 )    && ( hclk <= 112000000 ) )     wait = 6;
        if ( ( hclk > 112000000 )   && ( hclk <= 120000000 ) )     wait = 7;
    }

    if ( ( VOLTAGE_MV >= 2100 ) && ( VOLTAGE_MV < 2400 ) ) {
        if ( ( hclk > 0 )           && ( hclk <= 18000000 ) )      wait = 0;
        if ( ( hclk > 18000000 )    && ( hclk <= 36000000 ) )      wait = 1;
        if ( ( hclk > 36000000 )    && ( hclk <= 54000000 ) )      wait = 2;
        if ( ( hclk > 54000000 )    && ( hclk <= 72000000 ) )      wait = 3;
        if ( ( hclk > 72000000 )    && ( hclk <= 90000000 ) )      wait = 4;
        if ( ( hclk > 90000000 )    && ( hclk <= 108000000 ) )     wait = 5;
        if ( ( hclk > 108000000 )   && ( hclk <= 120000000 ) )     wait = 6;
    }

    if ( ( VOLTAGE_MV >= 2400 ) && ( VOLTAGE_MV < 2700 ) ) {
        if ( ( hclk > 0 )           && ( hclk <= 24000000 ) )      wait = 0;
        if ( ( hclk > 24000000 )    && ( hclk <= 48000000 ) )      wait = 1;
        if ( ( hclk > 48000000 )    && ( hclk <= 72000000 ) )      wait = 2;
        if ( ( hclk > 72000000 )    && ( hclk <= 96000000 ) )      wait = 3;
        if ( ( hclk > 96000000 )    && ( hclk <= 120000000 ) )     wait = 4;
    }

    if ( ( VOLTAGE_MV >= 2700 ) && ( VOLTAGE_MV < 3600 ) ) {
        if ( ( hclk > 0 )           && ( hclk <= 30000000 ) )      wait = 0;
        if ( ( hclk > 30000000 )    && ( hclk <= 60000000 ) )      wait = 1;
        if ( ( hclk > 60000000 )    && ( hclk <= 90000000 ) )      wait = 2;
        if ( ( hclk > 90000000 )    && ( hclk <= 120000000 ) )     wait = 3;
    }

    msk  |= wait << M_EC_TO_U8(EC_FLASH_AC_REG_BIT_FIELD_POS::LATENCY);   // Задержка Flash.
    msk  |= M_EC_TO_U32(EC_FLASH_AC_REG_BIT_MSK::PRFTEN) |                // Предсказатель.
            M_EC_TO_U32(EC_FLASH_AC_REG_BIT_MSK::ICEN) |                  // Кэш.
            M_EC_TO_U32(EC_FLASH_AC_REG_BIT_MSK::DCEN);

    return msk;
}


template < EC_RCC_AHB_DIV   AHB, EC_RCC_APB1_DIV    APB1, EC_RCC_APB2_DIV   APB2 >
constexpr src_dev_cfg< AHB, APB1, APB2 >::src_dev_cfg ( void ) : src_dev_cfg_struct( {
        .dev_msk = this->dev_msk_get()
}) {

}

template < EC_RCC_AHB_DIV   AHB, EC_RCC_APB1_DIV    APB1, EC_RCC_APB2_DIV   APB2 >
constexpr uint32_t src_dev_cfg< AHB, APB1, APB2 >::dev_msk_get ( void ) {
    uint32_t msk = 0;

    msk  |= M_EC_TO_U8(AHB)  << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::HPRE);
    msk  |= M_EC_TO_U8(APB1) << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::PPRE1);
    msk  |= M_EC_TO_U8(APB2) << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::PPRE2);

    return msk;
}

#endif
