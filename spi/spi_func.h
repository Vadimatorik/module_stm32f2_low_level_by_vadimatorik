#pragma once

#include "f2_api_conf.h"
#ifdef MODULE_SPI

#include "mk_hardware_interfaces_spi.h"
#include "spi_struct.h"

//**********************************************************************
// Генерация масок регистров SPI.
//**********************************************************************
#define SPI_CFG_TEMPLATE_HEADING            SPI::CFG::MODE             MODE,           \
                                            SPI::CFG::CLK_POLARITY     POLAR,          \
                                            SPI::CFG::CLK_PHASE        PHASE,          \
                                            SPI::CFG::NUMBER_LINE      NUM_LINE,       \
                                            SPI::CFG::ONE_LINE_MODE    ONE_LINE_MODE,  \
                                            SPI::CFG::DATA_FRAME       FRAME,          \
                                            SPI::CFG::RECEIVE_MODE     R_MODE,         \
                                            SPI::CFG::FRAME_FORMAT     FORMAT,         \
                                            SPI::CFG::BAUDRATE_DEV     BR_DEV,         \
                                            SPI::CFG::INTERRUPT_TX     I_TX,           \
                                            SPI::CFG::INTERRUPT_RX     I_RX,           \
                                            SPI::CFG::INTERRUPT_ERROR  I_ER,           \
                                            SPI::CFG::DMA_TX_BUF       DMATX,          \
                                            SPI::CFG::DMA_RX_BUF       DMARX,          \
                                            SPI::CFG::CS               CS,             \
                                            SPI::CFG::SSM              SSM,            \
                                            SPI::CFG::SSM_MODE         SSM_MODE

#define SPI_CFG_TEMPLATE_PARAM              MODE, POLAR, PHASE, NUM_LINE,               \
                                            ONE_LINE_MODE, FRAME, R_MODE, FORMAT,       \
                                            BR_DEV, I_TX, I_RX, I_ER,                   \
                                            DMATX, DMARX, CS, SSM, SSM_MODE

template < SPI_CFG_TEMPLATE_HEADING >
constexpr spi_cfg< SPI_CFG_TEMPLATE_PARAM >::spi_cfg() : SPI::CFG::STRUCT( {
    .c1_msk = this->c1_reg_msk_get(),
    .c2_msk = this->c2_reg_msk_get()
} ) {
        // Параметры ниже указываются при любых режимах.
        static_assert( ( MODE == SPI::CFG::MODE::MASTER ) ||
                       ( MODE == SPI::CFG::MODE::SLAVE ),
                "Invalid template parameter!The MODE can be MASTER or SLAVE!" );

        static_assert( ( POLAR == SPI::CFG::CLK_POLARITY::IDLE_0 ) ||
                       ( POLAR == SPI::CFG::CLK_POLARITY::IDLE_1 ),
                "Invalid template parameter!The POLAR can be IDLE_0 or IDLE_1!" );

        static_assert( ( PHASE == SPI::CFG::CLK_PHASE::FIRST ) ||
                       ( PHASE == SPI::CFG::CLK_PHASE::SECOND ),
                "Invalid template parameter!The PHASE can be FIRST or SECOND!" );

        static_assert( ( NUM_LINE == SPI::CFG::NUMBER_LINE::LINE_1 ) ||
                       ( NUM_LINE == SPI::CFG::NUMBER_LINE::LINE_2 ),
                "Invalid template parameter!The MODE can be LINE_1 or LINE_2!" );

        static_assert( ( FRAME == SPI::CFG::DATA_FRAME::FRAME_16_BIT ) ||
                       ( FRAME == SPI::CFG::DATA_FRAME::FRAME_8_BIT ),
                "Invalid template parameter!The FRAME can be FRAME_8_BIT or FRAME_16_BIT!" );

        static_assert( ( R_MODE == SPI::CFG::RECEIVE_MODE::FULL_DUPLEX ) ||
                       ( R_MODE == SPI::CFG::RECEIVE_MODE::RECEIVE_ONLY ),
                "Invalid template parameter!The R_MODE can be FULL_DUPLEX or RECEIVE_ONLY!" );

        static_assert( ( FORMAT == SPI::CFG::FRAME_FORMAT::MOTOROLA ) ||
                       ( FORMAT == SPI::CFG::FRAME_FORMAT::TI ),
                "Invalid template parameter!The FORMAT can be MOTOROLA or TI!" );

        static_assert( ( BR_DEV <= SPI::CFG::BAUDRATE_DEV::DEV_256 ) &&
                       ( BR_DEV >= SPI::CFG::BAUDRATE_DEV::DEV_2 ),
                "Invalid template parameter!The BR_DEV can be from DEV_2 to DEV_256!" );

        static_assert( ( I_TX == SPI::CFG::INTERRUPT_TX::ON ) ||
                       ( I_TX == SPI::CFG::INTERRUPT_TX::OFF ),
                "Invalid template parameter!The I_TX can be ON or OFF!" );

        static_assert( ( I_RX == SPI::CFG::INTERRUPT_RX::ON ) ||
                       ( I_RX == SPI::CFG::INTERRUPT_RX::OFF ),
                "Invalid template parameter!The I_RX can be ON or OFF!" );

        static_assert( ( I_ER == SPI::CFG::INTERRUPT_ERROR::ON ) ||
                       ( I_ER == SPI::CFG::INTERRUPT_ERROR::OFF ),
                "Invalid template parameter!The I_ER can be ON or OFF!" );

        static_assert( ( DMATX == SPI::CFG::DMA_TX_BUF::DISABLED ) ||
                       ( DMATX == SPI::CFG::DMA_TX_BUF::ENABLED ),
                "Invalid template parameter!The DMATX can be DISABLED or ENABLED!" );

        static_assert( ( DMARX == SPI::CFG::DMA_RX_BUF::DISABLED ) ||
                       ( DMARX == SPI::CFG::DMA_RX_BUF::ENABLED ),
                "Invalid template parameter!The DMARX can be ON or OFF!" );

        static_assert( ( CS == SPI::CFG::CS::DISABLED ) ||
                       ( CS == SPI::CFG::CS::ENABLED ),
                "Invalid template parameter!The CS can be DISABLED or ENABLED!" );

        // В случае, если используется только одна линия.
        static_assert( !( ( NUM_LINE == SPI::CFG::NUMBER_LINE::LINE_1 ) &&
                          ( ( ONE_LINE_MODE == SPI::CFG::ONE_LINE_MODE::RECEIVE_ONLY ) ||
                            ( ONE_LINE_MODE == SPI::CFG::ONE_LINE_MODE::TRANSMIT_ONLY ) ) ),
                "Invalid template parameter!"
                "NUM_LINE is selected as LINE_1"
                "The ONE_LINE_MODE can be RECEIVE_ONLY or TRANSMIT_ONLY!" );

            static_assert( ( NUM_LINE != SPI::CFG::NUMBER_LINE::LINE_1 ) &&
                           ( ONE_LINE_MODE == SPI::CFG::ONE_LINE_MODE::USE_2_LINE ),
                "Invalid template parameter!"
                "NUM_LINE is selected as LINE_2"
                "The ONE_LINE_MODE can be USE_2_LINE!" );

        // Если SPI сконфигурирован как мастер.
        static_assert( !( ( MODE == SPI::CFG::MODE::SLAVE )  &&
                          ( SSM == SPI::CFG::SSM::SSM_ON ) &&
                          ( SSM_MODE != SPI::CFG::SSM_MODE::NO_USE ) ),
                "Invalid template parameter!"                   // Если выбран режим отслеживания во время
                "SSM is selected as SSM_ON"                     // slave режима, то нужно укзаать, какой именно.
                "The SSM_MODE not can be NO_USE!" );
 }

template < SPI_CFG_TEMPLATE_HEADING >
constexpr uint32_t spi_cfg< SPI_CFG_TEMPLATE_PARAM >::c1_reg_msk_get ( void ) {
    uint32_t msk = 0;

    msk     |= M_EC_TO_U32(MODE) | M_EC_TO_U32(POLAR) | M_EC_TO_U32(PHASE) |
               M_EC_TO_U32(NUM_LINE) | M_EC_TO_U32(FRAME) | M_EC_TO_U32(R_MODE) |
               M_EC_TO_U32(BR_DEV) << M_EC_TO_U8(SPI::C1_R_BF_POS::BR);

    if ( MODE == SPI::CFG::MODE::SLAVE ) {
        msk     |= M_EC_TO_U32(SSM) | M_EC_TO_U32(SSM_MODE);
    }

    return msk;
}

template < SPI_CFG_TEMPLATE_HEADING >
constexpr uint32_t spi_cfg< SPI_CFG_TEMPLATE_PARAM >::c2_reg_msk_get ( void ) {
    uint32_t msk = 0;
    msk     |= M_EC_TO_U32(FORMAT) | M_EC_TO_U32(I_TX) | M_EC_TO_U32(I_RX) |
               M_EC_TO_U32(I_ER) | M_EC_TO_U32(DMATX) | M_EC_TO_U32(DMARX);

    if ( MODE == SPI::CFG::MODE::MASTER ) {
        msk |= M_EC_TO_U32(CS);
    }

    return msk;
}

//**********************************************************************
// Конфигурация SPI в режиме мастера, посылки по 8 бит.
//**********************************************************************
#define SPI_MASTER_HARDWARE_OS_TEMPLATE_HEADING         SPI::CFG::NAME              SPIx,           \
                                                        SPI::CFG::CLK_POLARITY      POLAR,          \
                                                        SPI::CFG::CLK_PHASE         PHASE,          \
                                                        SPI::CFG::NUMBER_LINE       NUM_LINE,       \
                                                        SPI::CFG::ONE_LINE_MODE     ONE_LINE_MODE,  \
                                                        SPI::CFG::FRAME_FORMAT      FORMAT,         \
                                                        SPI::CFG::BAUDRATE_DEV      BR_DEV

#define SPI_MASTER_HARDWARE_OS_TEMPLATE_PARAM           SPIx, POLAR, PHASE, NUM_LINE,               \
                                                        ONE_LINE_MODE, FORMAT, BR_DEV

template < SPI_MASTER_HARDWARE_OS_TEMPLATE_HEADING >
constexpr spi_master_8bit_hardware_os< SPI_MASTER_HARDWARE_OS_TEMPLATE_PARAM >::spi_master_8bit_hardware_os ( const spi_master_8bit_hardware_os_cfg_t* const cfg ) : cfg( cfg )  {
    static_assert( ( SPIx == SPI::CFG::NAME::SPI1 ) ||
                   ( SPIx == SPI::CFG::NAME::SPI2 ) ||
                   ( SPIx == SPI::CFG::NAME::SPI3 ),
                   "Invalid template parameter!The SPIx can be SPI1, SPI2 or SPI3!" );
}

template < SPI_MASTER_HARDWARE_OS_TEMPLATE_HEADING >
void spi_master_8bit_hardware_os< SPI_MASTER_HARDWARE_OS_TEMPLATE_PARAM >::reinit ( void ) const {
    SPI::R_STRUCT* S = ( SPI::R_STRUCT* )M_EC_TO_U32(SPIx);
    S->C2   =   this->cfg_low.c2_msk;   // Если этого не сделать, то после запуска сразу же сбросится режим мастера в slave (если был мастер!).
    S->C1   =   this->cfg_low.c1_msk;   // Конфигурируем SPI.
}

template < SPI_MASTER_HARDWARE_OS_TEMPLATE_HEADING >
SPI::BASE_RESULT spi_master_8bit_hardware_os< SPI_MASTER_HARDWARE_OS_TEMPLATE_PARAM >::tx ( const uint8_t* const  p_array_tx, const uint16_t& length, const uint32_t& timeout_ms, const SPI::STEP_MODE step_mode ) const {
    ( void )timeout_ms; // Игнорим, т.к. все делаем на флагах.
    SPI::R_STRUCT*   S = ( SPI::R_STRUCT* )M_EC_TO_U32(SPIx);

    if ( length == 0 ) return SPI::BASE_RESULT::LENGTH_ERROR;

    USER_OS_TAKE_MUTEX( *this->cfg->mutex, portMAX_DELAY );

    if ( NUM_LINE == SPI::CFG::NUMBER_LINE::LINE_2 ) {
        uint8_t* p = ( uint8_t* )p_array_tx;
        volatile uint32_t buf_read;
        ( void )buf_read;

        while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::BSY ) ) != 0  );

        // Непрерывный конвейер не реализован из-за того, что при высоких скоростях
        // мы получаем наложение принятого байта! (этого никак не избежать, скорости не хватает).
        for ( uint16_t loop = 0; loop < length; loop++ ) {
            S->D = *p;
            p += (int8_t)step_mode;
            while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::TXE ) ) == 0  );
            while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::RXNE ) ) == 0  );
            buf_read = S->D;
        }
    }

    USER_OS_GIVE_MUTEX( *this->cfg->mutex );
    return SPI::BASE_RESULT::OK;
}

template < SPI_MASTER_HARDWARE_OS_TEMPLATE_HEADING >
SPI::BASE_RESULT spi_master_8bit_hardware_os< SPI_MASTER_HARDWARE_OS_TEMPLATE_PARAM >::tx ( const uint8_t* const  p_array_tx, uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms ) const {
    ( void )timeout_ms; // Игнорим, т.к. все делаем на флагах.
    SPI::R_STRUCT*   S = ( SPI::R_STRUCT* )M_EC_TO_U32(SPIx);

    if ( length == 0 ) return SPI::BASE_RESULT::LENGTH_ERROR;

    USER_OS_TAKE_MUTEX( *this->cfg->mutex, portMAX_DELAY );

    if ( NUM_LINE == SPI::CFG::NUMBER_LINE::LINE_2 ) {
        uint8_t* p_out = ( uint8_t* )p_array_tx;
        uint8_t* p_in = ( uint8_t* )p_array_rx;

        while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::BSY ) ) != 0  );
        for ( uint16_t loop = 0; loop < length; loop++ ) {
            S->D = *p_out;
            p_out++;
            while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::TXE ) ) == 0  );
            while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::RXNE ) ) == 0  );
            *p_in = S->D;
            p_in++;
        }
    }

    USER_OS_GIVE_MUTEX( *this->cfg->mutex );
    return SPI::BASE_RESULT::OK;
}

template < SPI_MASTER_HARDWARE_OS_TEMPLATE_HEADING >
SPI::BASE_RESULT spi_master_8bit_hardware_os< SPI_MASTER_HARDWARE_OS_TEMPLATE_PARAM >::tx_one_item ( const uint8_t p_item_tx, const uint16_t count, const uint32_t timeout_ms ) const {
    ( void )timeout_ms; // Игнорим, т.к. все делаем на флагах.
    SPI::R_STRUCT*   S = ( SPI::R_STRUCT* )M_EC_TO_U32(SPIx);

    if ( count == 0 ) return SPI::BASE_RESULT::LENGTH_ERROR;

    USER_OS_TAKE_MUTEX( *this->cfg->mutex, portMAX_DELAY );

    if ( NUM_LINE == SPI::CFG::NUMBER_LINE::LINE_2 ) {
        volatile uint32_t buf_read;
        ( void )buf_read;

        while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::BSY ) ) != 0  );

        for ( uint16_t loop = 0; loop < count; loop++ ) {
            S->D = p_item_tx;
            while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::TXE ) ) == 0  );
            while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::RXNE ) ) == 0  );
            buf_read = S->D;
        }
    }

    USER_OS_GIVE_MUTEX( *this->cfg->mutex );
    return SPI::BASE_RESULT::OK;
}

template < SPI_MASTER_HARDWARE_OS_TEMPLATE_HEADING >
SPI::BASE_RESULT spi_master_8bit_hardware_os< SPI_MASTER_HARDWARE_OS_TEMPLATE_PARAM >::rx ( uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms, const uint8_t& out_value ) const {
    ( void )timeout_ms; // Игнорим, т.к. все делаем на флагах.
    SPI::R_STRUCT*   S = ( SPI::R_STRUCT* )M_EC_TO_U32(SPIx);

    if ( length == 0 ) return SPI::BASE_RESULT::LENGTH_ERROR;

    USER_OS_TAKE_MUTEX( *this->cfg->mutex, portMAX_DELAY );

    if ( NUM_LINE == SPI::CFG::NUMBER_LINE::LINE_2 ) {
        uint8_t* p = ( uint8_t* )p_array_rx;

        while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::BSY ) ) != 0  );

        for ( uint16_t loop = 0; loop < length; loop++ ) {
            S->D = out_value;
            while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::TXE ) ) == 0  );
            while ( ( S->S & M_EC_TO_U32( SPI::S_R_BF_MSK::RXNE ) ) == 0  );
            *p = S->D;
            p++;
        }
    }

    USER_OS_GIVE_MUTEX( *this->cfg->mutex );
    return SPI::BASE_RESULT::OK;
}

template < SPI_MASTER_HARDWARE_OS_TEMPLATE_HEADING >
void spi_master_8bit_hardware_os< SPI_MASTER_HARDWARE_OS_TEMPLATE_PARAM >::on ( void ) const {
    SPI::R_STRUCT*   S = ( SPI::R_STRUCT* )M_EC_TO_U32( SPIx );
    S->C1 |= M_EC_TO_U32(SPI::C1_R_BF_MSK::SPE);
}

template < SPI_MASTER_HARDWARE_OS_TEMPLATE_HEADING >
void spi_master_8bit_hardware_os< SPI_MASTER_HARDWARE_OS_TEMPLATE_PARAM >::off ( void ) const {
    SPI::R_STRUCT*   S = ( SPI::R_STRUCT* )M_EC_TO_U32( SPIx );
    S->C1 &= ~M_EC_TO_U32(SPI::C1_R_BF_MSK::SPE);
}
#endif
