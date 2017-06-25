#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_SPI

#include "stm32_f20x_f21x_spi.h"


/**********************************************************************
 * Область constexpr конструкторов.
 **********************************************************************/

template < EC_SPI_CFG_MODE MODE, EC_SPI_CFG_CLK_POLARITY POLAR, EC_SPI_CFG_CLK_PHASE PHASE, EC_SPI_CFG_NUMBER_LINE NUM_LINE, EC_SPI_CFG_ONE_LINE_MODE ONE_LINE_MODE,
           EC_SPI_CFG_DATA_FRAME FRAME, EC_SPI_CFG_RECEIVE_MODE R_MODE, EC_SPI_CFG_FRAME_FORMAT FORMAT, EC_SPI_CFG_BAUD_RATE_DEV BR_DEV, EC_SPI_CFG_INTERRUPT_TX I_TX,
           EC_SPI_CFG_INTERRUPT_RX I_RX, EC_SPI_CFG_INTERRUPT_ERROR I_ER, EC_SPI_CFG_SS CS, EC_SPI_CFG_SSM SSM, EC_SPI_CFG_SSM_MODE SSM_MODE >
constexpr spi_cfg< MODE, POLAR, PHASE, NUM_LINE, ONE_LINE_MODE, FRAME, R_MODE, FORMAT,
                   BR_DEV, I_TX, I_RX, I_ER, CS, SSM, SSM_MODE >::spi_cfg() : spi_cfg_struct( {
    .s1_msk = c1_reg_msk_get(),
    .s2_msk = c1_reg_msk_get()
} ) {
        static_assert( ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_1 ) || ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_2 ),
                "Invalid template parameter!The MODE can be LINE_1 or LINE_2!" );

        static_assert( ( ONE_LINE_MODE == EC_SPI_CFG_ONE_LINE_MODE::RECEIVE_ONLY ) ||
                       ( ONE_LINE_MODE == EC_SPI_CFG_ONE_LINE_MODE::TRANSMIT_ONLY ),
                "Invalid template parameter!The LINE_MODE can be RECEIVE_ONLY, TRANSMIT_ONLY or USE_2_LINE!" );

        static_assert( ( FRAME == EC_SPI_CFG_DATA_FRAME::FRAME_16_BIT ) ||
                       ( FRAME == EC_SPI_CFG_DATA_FRAME::FRAME_8_BIT ),
                "Invalid template parameter!The FRAME can be FRAME_8_BIT or FRAME_16_BIT!" );

        static_assert( ( R_MODE == EC_SPI_CFG_RECEIVE_MODE::FULL_DUPLEX ) ||
                       ( R_MODE == EC_SPI_CFG_RECEIVE_MODE::RECEIVE_ONLY ),
                "Invalid template parameter!The R_MODE can be FULL_DUPLEX or RECEIVE_ONLY!" );

        static_assert( ( CS == EC_SPI_CFG_SSM::CS_OFF ) || ( CS == EC_SPI_CFG_SSM::CS_ON ),
                "Invalid template parameter!The CS can be CS_OFF or CS_ON!" );

        if ( CS == EC_SPI_CFG_SSM::CS_ON ) {                                                     // Если выбрали аппаратный CS, то обязательно задаем его режим.
            static_assert( ( CS_M != EC_SPI_CFG_SSM_MODE::NO_USE ),
                    "CS is selected as CS_ON, CS_M can not be used!");
        }

        static_assert( ( CS_M == EC_SPI_CFG_SSM_MODE::NO_USE ) || ( CS_M == EC_SPI_CFG_SSM_MODE::CS_IGNORED_0 ) || ( CS_M == EC_SPI_CFG_SSM_MODE::CS_IGNORED_1 ),
                "Invalid template parameter!The CS_M can be NO_USE, CS_IGNORED_0, CS_IGNORED_1!" );

        static_assert( ( BR_DEV <= EC_SPI_CFG_BAUD_RATE_DEV::DEV_256 ) && ( BR_DEV >= EC_SPI_CFG_BAUD_RATE_DEV::DEV_2 ),
                "Invalid template parameter!The BR_DEV can be from DEV_2 to DEV_256!" );
};

template < EC_SPI_CFG_MODE MODE, EC_SPI_CFG_CLK_POLARITY POLAR, EC_SPI_CFG_CLK_PHASE PHASE, EC_SPI_CFG_NUMBER_LINE NUM_LINE, EC_SPI_CFG_ONE_LINE_MODE ONE_LINE_MODE,
           EC_SPI_CFG_DATA_FRAME FRAME, EC_SPI_CFG_RECEIVE_MODE R_MODE, EC_SPI_CFG_FRAME_FORMAT FORMAT, EC_SPI_CFG_BAUD_RATE_DEV BR_DEV, EC_SPI_CFG_INTERRUPT_TX I_TX,
           EC_SPI_CFG_INTERRUPT_RX I_RX, EC_SPI_CFG_INTERRUPT_ERROR I_ER, EC_SPI_CFG_SS CS, EC_SPI_CFG_SSM SSM, EC_SPI_CFG_SSM_MODE SSM_MODE >
constexpr uint32_t spi_cfg< MODE, POLAR, PHASE, NUM_LINE, ONE_LINE_MODE, FRAME, R_MODE, FORMAT,
                            BR_DEV, I_TX, I_RX, I_ER, CS, SSM, SSM_MODE >::c1_reg_msk_get ( void ) {
    uint32_t msk = 0;
    msk |= M_EC_TO_U32(NUM_LINE) | M_EC_TO_U32(ONE_LINE_MODE) | M_EC_TO_U32(FRAME) | M_EC_TO_U32(R_MODE) | M_EC_TO_U32(CS) | M_EC_TO_U32(BR_DEV);
    if ( CS != EC_SPI_CFG_SSM::CS_OFF ) {
        msk |= M_EC_TO_U32(CS_M);
    }
}

template < EC_SPI_CFG_MODE MODE, EC_SPI_CFG_CLK_POLARITY POLAR, EC_SPI_CFG_CLK_PHASE PHASE, EC_SPI_CFG_NUMBER_LINE NUM_LINE, EC_SPI_CFG_ONE_LINE_MODE ONE_LINE_MODE,
           EC_SPI_CFG_DATA_FRAME FRAME, EC_SPI_CFG_RECEIVE_MODE R_MODE, EC_SPI_CFG_FRAME_FORMAT FORMAT, EC_SPI_CFG_BAUD_RATE_DEV BR_DEV, EC_SPI_CFG_INTERRUPT_TX I_TX,
           EC_SPI_CFG_INTERRUPT_RX I_RX, EC_SPI_CFG_INTERRUPT_ERROR I_ER, EC_SPI_CFG_SS CS, EC_SPI_CFG_SSM SSM, EC_SPI_CFG_SSM_MODE SSM_MODE >
constexpr uint32_t spi_cfg< MODE, POLAR, PHASE, NUM_LINE, ONE_LINE_MODE, FRAME, R_MODE, FORMAT,
                            BR_DEV, I_TX, I_RX, I_ER, CS, SSM, SSM_MODE >::c2_reg_msk_get ( void ) {
    return 0;
}


#endif
