#pragma once

#include "f2_api_conf.h"

#ifdef MODULE_SPI

namespace SPI {

//**********************************************************************
// Область enum class-ов.
//**********************************************************************

//**********************************************************************
// Позиции битовых полей внутри регистра C1 модуля SPI.
//**********************************************************************
enum class C1_R_BF_POS {
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

//**********************************************************************
// Маски бит регистра pllcfg модуля RCC.
//**********************************************************************
enum class C1_R_BF_MSK {
    CPHA        = 1     << M_EC_TO_U8(C1_R_BF_POS::CPHA),
    CPOL        = 1     << M_EC_TO_U8(C1_R_BF_POS::CPOL),
    MSTR        = 1     << M_EC_TO_U8(C1_R_BF_POS::MSTR),
    BR          = 0B111 << M_EC_TO_U8(C1_R_BF_POS::BR),
    SPE         = 1     << M_EC_TO_U8(C1_R_BF_POS::SPE),
    LSBFIRST    = 1     << M_EC_TO_U8(C1_R_BF_POS::LSBFIRST),
    SSI         = 1     << M_EC_TO_U8(C1_R_BF_POS::SSI),
    SSM         = 1     << M_EC_TO_U8(C1_R_BF_POS::SSM),
    RXONLY      = 1     << M_EC_TO_U8(C1_R_BF_POS::RXONLY),
    DFF         = 1     << M_EC_TO_U8(C1_R_BF_POS::DFF),
    CRCNEXT     = 1     << M_EC_TO_U8(C1_R_BF_POS::CRCNEXT),
    CRCEN       = 1     << M_EC_TO_U8(C1_R_BF_POS::CRCEN),
    BIDIOE      = 1     << M_EC_TO_U8(C1_R_BF_POS::BIDIOE),
    BIDIMODE    = 1     << M_EC_TO_U8(C1_R_BF_POS::BIDIMODE)
};

//**********************************************************************
// Позиции битовых полей внутри регистра C2 модуля SPI.
//**********************************************************************
enum class C2_R_BF_POS {
    RXDMAEN     = 0,
    TXDMAEN     = 1,
    SSOE        = 2,
    FRF         = 4,
    ERRIE       = 5,
    RXNEIE      = 6,
    TXEIE       = 7
};

enum class C2_R_BF_MSK {
    RXDMAEN     = 1  << M_EC_TO_U8(C2_R_BF_POS::RXDMAEN),
    TXDMAEN     = 1  << M_EC_TO_U8(C2_R_BF_POS::TXDMAEN),
    SSOE        = 1  << M_EC_TO_U8(C2_R_BF_POS::SSOE),
    FRF         = 1  << M_EC_TO_U8(C2_R_BF_POS::FRF),
    ERRIE       = 1  << M_EC_TO_U8(C2_R_BF_POS::ERRIE),
    RXNEIE      = 1  << M_EC_TO_U8(C2_R_BF_POS::RXNEIE),
    TXEIE       = 1  << M_EC_TO_U8(C2_R_BF_POS::TXEIE)
};

enum class S_R_BF_POS {
    RXNE        = 0,
    TXE         = 1,
    CHSIDE      = 2,
    UDR         = 3,
    CRCERR      = 4,
    MODF        = 5,
    OVR         = 6,
    BSY         = 7,
    TIFRFE      = 8
};

enum class S_R_BF_MSK {
    RXNE        = 1  << M_EC_TO_U8(S_R_BF_POS::RXNE),
    TXE         = 1  << M_EC_TO_U8(S_R_BF_POS::TXE),
    CHSIDE      = 1  << M_EC_TO_U8(S_R_BF_POS::CHSIDE),
    UDR         = 1  << M_EC_TO_U8(S_R_BF_POS::UDR),
    CRCERR      = 1  << M_EC_TO_U8(S_R_BF_POS::CRCERR),
    MODF        = 1  << M_EC_TO_U8(S_R_BF_POS::MODF),
    OVR         = 1  << M_EC_TO_U8(S_R_BF_POS::OVR),
    BSY         = 1  << M_EC_TO_U8(S_R_BF_POS::BSY),
    TIFRFE      = 1  << M_EC_TO_U8(S_R_BF_POS::TIFRFE)
};

//**********************************************************************
// Мастер/ведомый.
//**********************************************************************
namespace CFG {

enum class MODE {
    MASTER  = M_EC_TO_U32(C1_R_BF_MSK::MSTR),
    SLAVE   = 0
};

enum class BAUDRATE_DEV {
    DEV_2       = 0,
    DEV_4       = 1,
    DEV_8       = 2,
    DEV_16      = 3,
    DEV_32      = 4,
    DEV_64      = 5,
    DEV_128     = 6,
    DEV_256     = 7
};

//**********************************************************************
// Полярность тактового сигнала (
// какое состояние у CLK, когда передача
// не идет).
//**********************************************************************
enum class CLK_POLARITY {
    IDLE_0  = 0,
    IDLE_1  = M_EC_TO_U32(C1_R_BF_MSK::CPOL)
};


//**********************************************************************
// Фаза.
//**********************************************************************
enum class CLK_PHASE {
    FIRST   = 0,
    SECOND  = M_EC_TO_U32(C1_R_BF_MSK::CPHA)
};

//**********************************************************************
// Делитель частоты с AHB для шины APB1.
//**********************************************************************
enum class NUMBER_LINE {
    LINE_1  = M_EC_TO_U32(C1_R_BF_MSK::BIDIMODE),
    LINE_2  = 0
};

//**********************************************************************
// Разрешение прерывания по опусташению буффера отправки.
//**********************************************************************

enum class INTERRUPT_TX {
    ON  = M_EC_TO_U32(C2_R_BF_MSK::TXEIE),
    OFF = 0
};

//**********************************************************************
// Вызов прерывания когда буффер по входу не пустой.
//**********************************************************************
enum class INTERRUPT_RX {
    ON  = M_EC_TO_U32(C2_R_BF_MSK::RXNEIE),
    OFF = 0
};

//**********************************************************************
// При возникновении ошибки.
//**********************************************************************
enum class INTERRUPT_ERROR {
    ON  = M_EC_TO_U32(C2_R_BF_MSK::ERRIE),
    OFF = 0
};

//**********************************************************************
// При возникновении ошибки.
//**********************************************************************
enum class FRAME_FORMAT {
    MOTOROLA    = 0,
    TI          = M_EC_TO_U32(C2_R_BF_MSK::FRF)
};

//**********************************************************************
// SS выход
//**********************************************************************
enum class CS {
    DISABLED   = 0,
    ENABLED    = M_EC_TO_U32(C2_R_BF_MSK::SSOE)
};

//**********************************************************************
// Буффер DMA TX.
//**********************************************************************
enum class DMA_TX_BUF {
    DISABLED   = 0,
    ENABLED    = M_EC_TO_U32(C2_R_BF_MSK::TXDMAEN)
};

//**********************************************************************
// Буффер DMA RX.
//**********************************************************************
enum class DMA_RX_BUF {
    DISABLED   = 0,
    ENABLED    = M_EC_TO_U32(C2_R_BF_MSK::RXDMAEN)
};




//**********************************************************************
// Режим для работы в режиме одной линии.
//**********************************************************************
enum class ONE_LINE_MODE {
    USE_2_LINE      = 0xFF,
    RECEIVE_ONLY    = 0,
    TRANSMIT_ONLY   = M_EC_TO_U32(C1_R_BF_MSK::BIDIOE)
};

//**********************************************************************
// Размер кадра посылки.
//**********************************************************************
enum class DATA_FRAME {
    FRAME_8_BIT     = 0,
    FRAME_16_BIT    = M_EC_TO_U32(C1_R_BF_MSK::DFF)
};

//**********************************************************************
// Полный дуплекс или только прием.
//**********************************************************************
enum class RECEIVE_MODE {
    FULL_DUPLEX     = 0,
    RECEIVE_ONLY    = M_EC_TO_U32(C1_R_BF_MSK::RXONLY)
};

//**********************************************************************
// Программное отслеживание CS в режиме ведомого.
//**********************************************************************
enum class SSM {
    SSM_OFF  = 0,
    SSM_ON   = M_EC_TO_U32(C1_R_BF_MSK::SSM)
};

//**********************************************************************
// Использовать ли аппаратный CS или нет?
//**********************************************************************
enum class SSM_MODE {
    NO_USE       = 0xFF,
    CS_IGNORED_0 = 0,
    CS_IGNORED_1 = M_EC_TO_U32(C1_R_BF_MSK::SSI)
};

enum class NAME {
    SPI1 = 0x40013000,
    SPI2 = 0x40003800,
    SPI3 = 0x40003C00
};


//**********************************************************************
// Структура конфигурации SPI.
//**********************************************************************
struct STRUCT {
    const uint32_t           c1_msk;
    const uint32_t           c2_msk;
};

}
//**********************************************************************
// Область упакованных структур.
//**********************************************************************

/*
// Регистры физического модуля RCC.
// res_x - зарезервированные области памяти RCC модуля.
 */
struct __attribute__((packed)) R_STRUCT {
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

//**********************************************************************
// Область структур.
//**********************************************************************


}
#endif
