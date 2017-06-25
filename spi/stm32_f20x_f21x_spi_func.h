#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_SPI

#include "stm32_f20x_f21x_spi.h"


/**********************************************************************
 * Область constexpr конструкторов.
 **********************************************************************/
template < EC_SPI_CFG_MODE MODE, EC_SPI_CFG_ONE_LINE_MODE LINE_MODE, EC_SPI_CFG_DATA_FRAME FRAME, EC_SPI_CFG_RECEIVE_MODE R_MODE, EC_SPI_CFG_CS CS, EC_SPI_CFG_CS_MODE CS_M, EC_SPI_CFG_BAUD_RATE_DEV BR_DEV >
constexpr spi_cfg< MODE, LINE_MODE, FRAME, R_MODE, CS, CS_M, BR_DEV >::spi_cfg() : spi_cfg_struct( {
    .s1_msk = c1_reg_msk_get(),
    .s2_msk = с2_msk_get(),
} ) {
    /*
     * Проверяем диапазон напряжений питания микроконтроллера.
     */
   // static_assert( ( VOLTAGE_MV <= 3600 ) && ( VOLTAGE_MV >= 1650 ), "Wrong voltage value. The voltage should range from 1650 mV to 3600 mV." );

    /*
     * Источник тактового сигнала.
     */
   // static_assert( ( S == EC_RCC_PLL_SOURCE::HSE ) || ( S == EC_RCC_PLL_SOURCE::HSI ), "Wrong source selected ( Param S )! Source may be HSE or HSI!" );


    //static_assert( ( M >= 2 ) || ( M <= 63 ), "Invalid parameter M! 2 <=  M <= 63!" );
};

template < EC_SPI_CFG_MODE MODE, EC_SPI_CFG_ONE_LINE_MODE LINE_MODE, EC_SPI_CFG_DATA_FRAME FRAME, EC_SPI_CFG_RECEIVE_MODE R_MODE, EC_SPI_CFG_CS CS, EC_SPI_CFG_CS_MODE CS_M, EC_SPI_CFG_BAUD_RATE_DEV BR_DEV >
constexpr uint32_t spi_cfg< MODE, LINE_MODE, FRAME, R_MODE, CS, CS_M, BR_DEV >::c1_reg_msk_get ( void ) {
    return 0;
}

template < EC_SPI_CFG_MODE MODE, EC_SPI_CFG_ONE_LINE_MODE LINE_MODE, EC_SPI_CFG_DATA_FRAME FRAME, EC_SPI_CFG_RECEIVE_MODE R_MODE, EC_SPI_CFG_CS CS, EC_SPI_CFG_CS_MODE CS_M, EC_SPI_CFG_BAUD_RATE_DEV BR_DEV >
constexpr uint32_t spi_cfg< MODE, LINE_MODE, FRAME, R_MODE, CS, CS_M, BR_DEV >::с2_msk_get ( void ) {
    return 0;
}


#endif
