#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_SPI

/**********************************************************************
 * Область enum class-ов.
 **********************************************************************/
/*
 * Позиции битовых полей внутри регистра C1 модуля SPI.
 */
enum class EC_C1_REG_BIT_FIELD_POS {
    CPHA        = 0,
    CPOL        = 1,
    MSTR        = 2,
    BR          = 3,    // [5:3]
    SPE         = 6,
    LSBFIRST    = 7,
    SSI         = 8,
    SSM         = 9,
    RXONLY      = 10,
    DFF         = 11,
    CRCNEXT     = 12,
    CRCEN       = 13,
    BIDIOE      = 14,
    BIDIMODE    = 15
};

/*
 * Маски бит регистра pllcfg модуля RCC.
 */
enum class EC_C1_REG_BIT_MSK {
    CPHA        = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::CPHA),
    CPOL        = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::CPOL),
    MSTR        = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::MSTR),
    BR          = 0B111 << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::BR),
    SPE         = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::SPE),
    LSBFIRST    = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::LSBFIRST),
    SSI         = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::SSI),
    SSM         = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::SSM),
    RXONLY      = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::RXONLY),
    DFF         = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::DFF),
    CRCNEXT     = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::CRCNEXT),
    CRCEN       = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::CRCEN),
    BIDIOE      = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::BIDIOE),
    BIDIMODE    = 1     << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::BIDIMODE)
};

enum class EC_SPI_CFG_BAUD_RATE_DEV {
    DEV_2       = 0,
    DEV_4       = 1,
    DEV_8       = 2,
    DEV_16      = 3,
    DEV_32      = 4,
    DEV_64      = 5,
    DEV_128     = 6,
    DEV_256     = 7
};


/*
 * Позиции битовых полей внутри регистра C2 модуля SPI.
 */
enum class EC_C2_REG_BIT_FIELD_POS {
    RXDMAEN     = 0,
    TXDMAEN     = 1,
    SSOE        = 2,
    FRF         = 4,
    ERRIE       = 5,
    RXNEIE      = 6,
    TXEIE       = 7
};

enum class EC_C2_REG_BIT_MSK {
    RXDMAEN     = 1  << M_EC_TO_U8(EC_C2_REG_BIT_FIELD_POS::RXDMAEN),
    TXDMAEN     = 1  << M_EC_TO_U8(EC_C2_REG_BIT_FIELD_POS::TXDMAEN),
    SSOE        = 1  << M_EC_TO_U8(EC_C2_REG_BIT_FIELD_POS::SSOE),
    FRF         = 1  << M_EC_TO_U8(EC_C2_REG_BIT_FIELD_POS::FRF),
    ERRIE       = 1  << M_EC_TO_U8(EC_C2_REG_BIT_FIELD_POS::ERRIE),
    RXNEIE      = 1  << M_EC_TO_U8(EC_C2_REG_BIT_FIELD_POS::RXNEIE),
    TXEIE       = 1  << M_EC_TO_U8(EC_C2_REG_BIT_FIELD_POS::TXEIE)
};

/*
 * Мастер/ведомый.
 */
enum class EC_SPI_CFG_MODE {
    MASTER  = M_EC_TO_U32(EC_C1_REG_BIT_MSK::MSTR),
    SLAVE   = 0
};

/*
 * Полярность тактового сигнала (
 * какое состояние у CLK, когда передача
 * не идет).
 */
enum class EC_SPI_CFG_CLK_POLARITY {
    IDLE_0  = 0,
    IDLE_1  = M_EC_TO_U32(EC_C1_REG_BIT_MSK::CPOL)
};


/*
 * Фаза.
 */
enum class EC_SPI_CFG_CLK_PHASE {
    FIRST   = 0,
    SECOND  = M_EC_TO_U32(EC_C1_REG_BIT_MSK::CPHA)
};

/*
 * Делитель частоты с AHB для шины APB1.
 */
enum class EC_SPI_CFG_NUMBER_LINE {
    LINE_1  = M_EC_TO_U32(EC_C1_REG_BIT_MSK::BIDIMODE),
    LINE_2  = 0
};

/*
 * Разрешение прерывания по опусташению буффера отправки.
 */
enum class EC_SPI_CFG_INTERRUPT_TX {
    ON  = M_EC_TO_U32(EC_C2_REG_BIT_MSK::TXEIE),
    OFF = 0
};

/*
 * Вызов прерывания когда буффер по входу не пустой.
 */
enum class EC_SPI_CFG_INTERRUPT_RX {
    ON  = M_EC_TO_U32(EC_C2_REG_BIT_MSK::RXNEIE),
    OFF = 0
};

/*
 * При возникновении ошибки.
 */
enum class EC_SPI_CFG_INTERRUPT_ERROR {
    ON  = M_EC_TO_U32(EC_C2_REG_BIT_MSK::ERRIE),
    OFF = 0
};

/*
 * При возникновении ошибки.
 */
enum class EC_SPI_CFG_FRAME_FORMAT {
    MOTOROLA    = 0,
    TI          = M_EC_TO_U32(EC_C2_REG_BIT_MSK::FRF)
};

/*
 * SS выход
 */
enum class EC_SPI_CFG_SS {
    DISABLED   = 0,
    ENABLED    = M_EC_TO_U32(EC_C2_REG_BIT_MSK::SSOE)
};

/*
 * Буффер DMA TX.
 */
enum class EC_SPI_CFG_DMA_TX_BUF {
    DISABLED   = 0,
    ENABLED    = M_EC_TO_U32(EC_C2_REG_BIT_MSK::TXDMAEN)
};

/*
 * Буффер DMA RX.
 */
enum class EC_SPI_CFG_DMA_RX_BUF {
    DISABLED   = 0,
    ENABLED    = M_EC_TO_U32(EC_C2_REG_BIT_MSK::RXDMAEN)
};




/*
 * Режим для работы в режиме одной линии.
 */
enum class EC_SPI_CFG_ONE_LINE_MODE {
    USE_2_LINE      = -1,
    RECEIVE_ONLY    = 0,
    TRANSMIT_ONLY   = M_EC_TO_U32(EC_C1_REG_BIT_MSK::BIDIOE)
};

/*
 * Размер кадра посылки.
 */
enum class EC_SPI_CFG_DATA_FRAME {
    FRAME_8_BIT     = 0,
    FRAME_16_BIT    = M_EC_TO_U32(EC_C1_REG_BIT_MSK::DFF)
};

/*
 * Полный дуплекс или только прием.
 */
enum class EC_SPI_CFG_RECEIVE_MODE {
    FULL_DUPLEX     = 0,
    RECEIVE_ONLY    = M_EC_TO_U32(EC_C1_REG_BIT_MSK::RXONLY)
};

/*
 * Программное отслеживание CS в режиме ведомого.
 */
enum class EC_SPI_CFG_SSM {
    SSM_OFF  = 0,
    SSM_ON   = M_EC_TO_U32(EC_C1_REG_BIT_MSK::SSM)
};

/*
 * Использовать ли аппаратный CS или нет?
 */
enum class EC_SPI_CFG_SSM_MODE {
    NO_USE       = -1,
    CS_IGNORED_0 = 0,
    CS_IGNORED_1 = M_EC_TO_U32(EC_C1_REG_BIT_MSK::SSI)
};

enum class EC_SPI_NAME {
    SPI1 = 0x40013000,
    SPI2 = 0x40003800,
    SPI3 = 0x40003C00
};


/**********************************************************************
 * Область упакованных структур.
 **********************************************************************/

/*
 * Регистры физического модуля RCC.
 * res_x - зарезервированные области памяти RCC модуля.
 */
struct __attribute__((packed)) spi_registers_struct {
    volatile uint32_t   C1;
    volatile uint32_t   C2;
    volatile uint32_t   S;
    volatile uint32_t   D;
    volatile uint32_t   CRCP;
    volatile uint32_t   RXCRC;
    volatile uint32_t   TXCRC;
    volatile uint32_t   I2SCFG;
    volatile uint32_t   I2SPR;
};

/**********************************************************************
 * Область структур.
 **********************************************************************/

/*
 * Структура конфигурации SPI.
 */
struct spi_cfg_struct {
    volatile uint32_t           c1_msk;
    volatile uint32_t           c2_msk;
};

#endif
