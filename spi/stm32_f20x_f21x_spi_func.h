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
    .s2_msk = c1_reg_msk_get()
} ) {
        static_assert( ( MODE == EC_SPI_CFG_MODE::LINE_1 ) || ( MODE == EC_SPI_CFG_MODE::LINE_2 ),
                "Invalid template parameter!The MODE can be LINE_1 or LINE_2!" );

        static_assert( ( LINE_MODE == EC_SPI_CFG_ONE_LINE_MODE::RECEIVE_ONLY ) ||
                       ( LINE_MODE == EC_SPI_CFG_ONE_LINE_MODE::TRANSMIT_ONLY ),
                "Invalid template parameter!The LINE_MODE can be RECEIVE_ONLY, TRANSMIT_ONLY or USE_2_LINE!" );

        static_assert( ( FRAME == EC_SPI_CFG_DATA_FRAME::FRAME_16_BIT ) ||
                       ( FRAME == EC_SPI_CFG_DATA_FRAME::FRAME_8_BIT ),
                "Invalid template parameter!The FRAME can be FRAME_8_BIT or FRAME_16_BIT!" );

        static_assert( ( R_MODE == EC_SPI_CFG_RECEIVE_MODE::FULL_DUPLEX ) ||
                       ( R_MODE == EC_SPI_CFG_RECEIVE_MODE::RECEIVE_ONLY ),
                "Invalid template parameter!The R_MODE can be FULL_DUPLEX or RECEIVE_ONLY!" );

        static_assert( ( CS == EC_SPI_CFG_CS::CS_OFF ) || ( CS == EC_SPI_CFG_CS::CS_ON ),
                "Invalid template parameter!The CS can be CS_OFF or CS_ON!" );

        if ( CS == EC_SPI_CFG_CS::CS_ON ) {                                                     // Если выбрали аппаратный CS, то обязательно задаем его режим.
            static_assert( ( CS_M != EC_SPI_CFG_CS_MODE::NO_USE ),
                    "CS is selected as CS_ON, CS_M can not be used!");
        }

        static_assert( ( CS_M == EC_SPI_CFG_CS_MODE::NO_USE ) || ( CS_M == EC_SPI_CFG_CS_MODE::CS_IGNORED_0 ) || ( CS_M == EC_SPI_CFG_CS_MODE::CS_IGNORED_1 ),
                "Invalid template parameter!The CS_M can be NO_USE, CS_IGNORED_0, CS_IGNORED_1!" );

        static_assert( ( BR_DEV <= EC_SPI_CFG_BAUD_RATE_DEV::DEV_256 ) && ( BR_DEV >= EC_SPI_CFG_BAUD_RATE_DEV::DEV_2 ),
                "Invalid template parameter!The BR_DEV can be from DEV_2 to DEV_256!" );
};

template < EC_SPI_CFG_MODE MODE, EC_SPI_CFG_ONE_LINE_MODE LINE_MODE, EC_SPI_CFG_DATA_FRAME FRAME, EC_SPI_CFG_RECEIVE_MODE R_MODE, EC_SPI_CFG_CS CS, EC_SPI_CFG_CS_MODE CS_M, EC_SPI_CFG_BAUD_RATE_DEV BR_DEV >
constexpr uint32_t spi_cfg< MODE, LINE_MODE, FRAME, R_MODE, CS, CS_M, BR_DEV >::c1_reg_msk_get ( void ) {
    uint32_t msk = 0;
    msk |= M_EC_TO_U32(MODE) | M_EC_TO_U32(LINE_MODE) | M_EC_TO_U32(FRAME) | M_EC_TO_U32(R_MODE) | M_EC_TO_U32(CS) | M_EC_TO_U32(BR_DEV);
    if ( CS != EC_SPI_CFG_CS::CS_OFF ) {
        msk |= M_EC_TO_U32(CS_M);
    }
}

template < EC_SPI_CFG_MODE MODE, EC_SPI_CFG_ONE_LINE_MODE LINE_MODE, EC_SPI_CFG_DATA_FRAME FRAME, EC_SPI_CFG_RECEIVE_MODE R_MODE, EC_SPI_CFG_CS CS, EC_SPI_CFG_CS_MODE CS_M, EC_SPI_CFG_BAUD_RATE_DEV BR_DEV >
constexpr uint32_t spi_cfg< MODE, LINE_MODE, FRAME, R_MODE, CS, CS_M, BR_DEV >::c2_reg_msk_get ( void ) {
    return 0;
}


#endif
