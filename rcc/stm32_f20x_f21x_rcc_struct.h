#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

#include <cmath>
#include "stm32_f20x_f21x_rcc_struct_class_pll.h"
#include "stm32_f20x_f21x_port.h"

/**********************************************************************
 * Область упакованных структур.
 **********************************************************************/

/*
 * Перечень регистров физического порта ввода-вывода.
 */
struct pll_cfg_struct {
    const uint32_t              pllcfg_reg_msk;         // Маска конфигурации PLL целиком.
    const uint32_t              dev_bus_msk;            // Маска регистра RCCCFG (только части с делителями частоты шин).
    const uint32_t              flash_acr_msk;          // Маска всего регистра flash_acr (предсказатель + задержки обращения к Flash).
    const bool                  src;                    // true = HSE, false = HSI
};

/**********************************************************************
 * Область enum class-ов.
 **********************************************************************/

/*
 * Позиции битовых полей внутрирегистра pllcfg модуля RCC.
 */
enum class EC_PLLCFG_REG_BIT_FIELD_POSITION {
    M   = 0,            // PLLM     [5:0].
    N   = 6,            // PLLN     [14:6].
    P   = 16,           // PLLP     [17:16].
    S   = 22,           // PLLSRC
    Q   = 24            // PLLQ     [27:24].
};

/*
 * Позиции битовых полей внутри регистра pllcfg модуля RCC.
 */
enum class EC_C_REG_BIT_FIELD_POS {
    HSION       = 0,
    HSIRDY      = 1,
    HSITRIM     = 3,        // [7:3].
    HSICAL      = 8,        // [15:8].
    HSEON       = 16,
    HSERDY      = 17,
    HSEBYP      = 18,
    CSSON       = 19,
    PLLON       = 24,
    PLLRDY      = 25,
    PLLI2SON    = 26,
    PLLI2SRDY   = 27
};

/*
 * Маски бит регистра pllcfg модуля RCC.
 */
enum class EC_C_REG_BIT_MSK {
    HSION       = 1 << M_EC_TO_U8(EC_C_REG_BIT_FIELD_POS::HSION),
    HSIRDY      = 1 << M_EC_TO_U8(EC_C_REG_BIT_FIELD_POS::HSIRDY),
    HSEON       = 1 << M_EC_TO_U8(EC_C_REG_BIT_FIELD_POS::HSEON),
    HSERDY      = 1 << M_EC_TO_U8(EC_C_REG_BIT_FIELD_POS::HSERDY),
    HSEBYP      = 1 << M_EC_TO_U8(EC_C_REG_BIT_FIELD_POS::HSEBYP),
    CSSON       = 1 << M_EC_TO_U8(EC_C_REG_BIT_FIELD_POS::CSSON),
    PLLON       = 1 << M_EC_TO_U8(EC_C_REG_BIT_FIELD_POS::PLLON),
    PLLRDY      = 1 << M_EC_TO_U8(EC_C_REG_BIT_FIELD_POS::PLLRDY),
    PLLI2SON    = 1 << M_EC_TO_U8(EC_C_REG_BIT_FIELD_POS::PLLI2SON),
    PLLI2SRDY   = 1 << M_EC_TO_U8(EC_C_REG_BIT_FIELD_POS::PLLI2SRDY)
};

/*
 * Позиции битовых полей внутрирегистра pllcfg модуля RCC.
 */
enum class EC_CFG_REG_BIT_FIELD_POS {
    SW          = 0,        // [0:1].
    SWS         = 2,        // [3:2].
    HPRE        = 4,        // [7:4].
    PPRE1       = 10,       // [12:10].
    PPRE2       = 13,       // [15:13].
    RTCPRE      = 16,       // [20:16].
    MCO1        = 21,       // [22:21].
    I2SSRC      = 23,
    MCO1PRE     = 24,       // [26:24].
    MCO2PRE     = 27,       // [29:27].
    MCO2        = 30,       // [31:30].
};

enum class EC_CFG_REG_BIT_MSK {
    SW          = 0b11      << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::SW),
    SWS         = 0b11      << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::SWS),
    HPRE        = 0b1111    << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::HPRE),
    PPRE1       = 0b111     << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::PPRE1),
    PPRE2       = 0b111     << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::PPRE2),
    RTCPRE      = 0b11111   << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::RTCPRE),
    I2SSRC      = 1         << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::I2SSRC),
    MCO1PRE     = 0b111     << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::MCO1PRE),
    MCO2PRE     = 0b111     << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::MCO2PRE),
    MCO2        = 0b11      << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::MCO2),
};

/*
 * APB2EN.
 */
enum class EC_APB2_EN_REG_BIT_FIELD_POS {
    TIM1        = 0,
    TIM8        = 1,
    USART1      = 4,
    USART6      = 5,
    ADC1        = 8,
    ADC2        = 9,
    ADC3        = 10,
    SDIO        = 11,
    SPI1        = 12,
    SYSCFG      = 14,
    TIM9        = 16,
    TIM10       = 17,
    TIM11       = 18
};

enum class EC_APB2_EN_REG_BIT_MSK {
    TIM1        = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::TIM1),
    TIM8        = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::TIM8),
    USART1      = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::USART1),
    USART6      = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::USART6),
    ADC1        = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::ADC1),
    ADC2        = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::ADC2),
    ADC3        = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::ADC3),
    SDIO        = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::SDIO),
    SPI1        = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::SPI1),
    SYSCFG      = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::SYSCFG),
    TIM9        = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::TIM9),
    TIM10       = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::TIM10),
    TIM11       = 1 << M_EC_TO_U8(EC_APB2_EN_REG_BIT_FIELD_POS::TIM11)
};

/*
 * APB2EN.
 */
enum class EC_APB1_EN_REG_BIT_FIELD_POS {
    TIM2        = 0,
    TIM3        = 1,
    TIM4        = 2,
    TIM5        = 3,
    TIM6        = 4,
    TIM7        = 5,
    TIM12       = 6,
    TIM13       = 7,
    TIM14       = 8,
    WWDG        = 11,
    SPI2        = 14,
    SPI3        = 15,
    USART2      = 17,
    USART3      = 18,
    UART4       = 19,
    UART5       = 20,
    I2C1        = 21,
    I2C2        = 22,
    I2C3        = 23,
    CAN1        = 25,
    CAN2        = 26,
    PWR         = 28,
    DAC         = 29,
};

enum class EC_APB1_EN_REG_BIT_MSK {
    TIM2        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::TIM2),
    TIM3        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::TIM3),
    TIM4        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::TIM4),
    TIM5        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::TIM5),
    TIM6        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::TIM6),
    TIM7        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::TIM7),
    TIM12       = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::TIM12),
    TIM13       = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::TIM13),
    TIM14       = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::TIM14),
    WWDG        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::WWDG),
    SPI2        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::SPI2),
    SPI3        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::SPI3),
    USART2      = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::USART2),
    USART3      = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::USART3),
    UART4       = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::UART4),
    UART5       = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::UART5),
    I2C1        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::I2C1),
    I2C2        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::I2C2),
    I2C3        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::I2C3),
    CAN1        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::CAN1),
    CAN2        = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::CAN2),
    PWR         = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::PWR),
    DAC         = 1 << M_EC_TO_U8(EC_APB1_EN_REG_BIT_FIELD_POS::DAC),
};


enum class EC_ANSWER_CLOCK_UPDATE {
    SUCCESS                     = 0,
    STRUCT_NUMBER_IS_WRONG      = 1
};

enum class EC_CFG_REG_BIT_FIELD_SW_MSK {
    HSI = 0b00,
    HSE = 0b01,
    PLL = 0b10
};

enum class EC_ANSWER_PLL_STATUS {
    PLL_OFF = 0,
    PLL_ON  = 1
};

enum class EC_ANSWER_PLL_READY_FLAG {
    PLL_UNLOCKED    = 0,
    LOCKED          = 1
};

enum class EC_ANSWER_OSCILLATOR_STATUS {
    OFF = 0,
    ON  = 1
};

enum class EC_ANSWER_OSCILLATOR_STATE {
    NOT_READY = 0,
    READY  = 1
};

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

/*
 * Делитель SYSCLK для шины AHB.
 */
enum class EC_RCC_AHB_DIV {
    DIV_1   = 0,
    DIV_2   = 0b1000,
    DIV_4   = 0b1001,
    DIV_8   = 0b1010,
    DIV_16  = 0b1011,
    DIV_64  = 0b1100,
    DIV_128 = 0b1101,
    DIV_256 = 0b1110,
    DIV_512 = 0b1111,
};

/*
 * Делитель частоты с AHB для шины APB1.
 */
enum class EC_RCC_APB1_DIV {
    DIV_1   = 0,
    DIV_2   = 0b100,
    DIV_4   = 0b101,
    DIV_8   = 0b110,
    DIV_16  = 0b111,
};

/*
 * Делитель частоты с AHB для шины APB2.
 */
enum class EC_RCC_APB2_DIV {
    DIV_1   = 0,
    DIV_2   = 0b100,
    DIV_4   = 0b101,
    DIV_8   = 0b110,
    DIV_16  = 0b111,
};

/*
 * От чего сейчас тактируется ядро?
 */
enum class EC_ANSWER_RCC_SWS_STATUS {
    HSI = M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_SW_MSK::HSI) << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::SWS),
    HSE = M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_SW_MSK::HSE) << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::SWS),
    PLL = M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_SW_MSK::PLL) << M_EC_TO_U8(EC_CFG_REG_BIT_FIELD_POS::SWS)
};


/*
 * Позиции битовых полей внутрирегистра pllcfg модуля RCC.
 */
enum class EC_FLASH_AC_REG_BIT_FIELD_POS {
    LATENCY     = 0,        // [2:0].
    PRFTEN      = 8,
    ICEN        = 9,
    DCEN        = 10,
    ICRST       = 11,
    DCRST       = 12
};

enum class EC_FLASH_AC_REG_BIT_MSK {
    LATENCY = 0b111 << M_EC_TO_U8(EC_FLASH_AC_REG_BIT_FIELD_POS::LATENCY),
    PRFTEN  = 1     << M_EC_TO_U8(EC_FLASH_AC_REG_BIT_FIELD_POS::PRFTEN),
    ICEN    = 1     << M_EC_TO_U8(EC_FLASH_AC_REG_BIT_FIELD_POS::ICEN),
    DCEN    = 1     << M_EC_TO_U8(EC_FLASH_AC_REG_BIT_FIELD_POS::DCEN),
    ICRST   = 1     << M_EC_TO_U8(EC_FLASH_AC_REG_BIT_FIELD_POS::ICRST),
    DCRST   = 1     << M_EC_TO_U8(EC_FLASH_AC_REG_BIT_FIELD_POS::DCRST),
};

/*
 * Позиции битовых полей внутри регистра AHB1EN модуля RCC.
 */
enum class EC_AHB1EN_REG_BIT_FIELD_POS {
    GPIOA         = 0,
    GPIOB         = 1,
    GPIOC         = 2,
    GPIOD         = 3,
    GPIOE         = 4,
    GPIOF         = 5,
    GPIOG         = 6,
    GPIOH         = 7,
    GPIOI         = 8,
    CRC           = 12,
    BKPSRAM       = 18,
    DMA1          = 21,
    DMA2          = 22,
    ETHMAC        = 25,
    ETHMACTX      = 26,
    ETHMAXRX      = 27,
    ETHMACPTP     = 28,
    OTGHS         = 29,
    OTGHSULPI     = 30
};

enum class EC_AHB1EN_REG_BIT_MSK {
    GPIOA         = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::GPIOA),
    GPIOB         = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::GPIOB),
    GPIOC         = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::GPIOC),
    GPIOD         = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::GPIOD),
    GPIOE         = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::GPIOE),
    GPIOF         = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::GPIOF),
    GPIOG         = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::GPIOG),
    GPIOH         = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::GPIOH),
    GPIOI         = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::GPIOI),
    CRC           = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::CRC),
    BKPSRAM       = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::BKPSRAM),
    DMA1          = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::DMA1),
    DMA2          = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::DMA2),
    ETHMAC        = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::ETHMAC),
    ETHMACTX      = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::ETHMACTX),
    ETHMAXRX      = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::ETHMAXRX),
    ETHMACPTP     = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::ETHMACPTP),
    OTGHS         = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::OTGHS),
    OTGHSULPI     = 1   << M_EC_TO_U8(EC_AHB1EN_REG_BIT_FIELD_POS::OTGHSULPI)
};


/**********************************************************************
 * Область упакованных структур.
 **********************************************************************/

/*
 * Регистры физического модуля RCC.
 * res_x - зарезервированные области памяти RCC модуля.
 */
struct __attribute__((packed)) rcc_registers_struct {
    volatile uint32_t   C;
    volatile uint32_t   PLLCFG;
    volatile uint32_t   CFG;
    volatile uint32_t   CI;
    volatile uint32_t   AHB_1_RST;
    volatile uint32_t   AHB_2_RST;
    volatile uint32_t   AHB_3_RST;
    volatile uint32_t   RES_0;
    volatile uint32_t   APB_1_RST;
    volatile uint32_t   APB_2_RST;
    volatile uint32_t   RES_1;
    volatile uint32_t   RES_2;
    volatile uint32_t   AHB_1_EN;
    volatile uint32_t   AHB_2_EN;
    volatile uint32_t   AHB_3_EN;
    volatile uint32_t   RES_3;
    volatile uint32_t   APB_1_EN;
    volatile uint32_t   APB_2_EN;
    volatile uint32_t   RES_4;
    volatile uint32_t   RES_5;
    volatile uint32_t   AHB_1_LP_EN;
    volatile uint32_t   AHB_2_LP_EN;
    volatile uint32_t   AHB_3_LP_EN;
    volatile uint32_t   RES_6;
    volatile uint32_t   APB_1_LP_EN;
    volatile uint32_t   APB_2_LP_EN;
    volatile uint32_t   RES_7;
    volatile uint32_t   RES_8;
    volatile uint32_t   BDC;
    volatile uint32_t   CS;
    volatile uint32_t   RES_9;
    volatile uint32_t   RES_10;
    volatile uint32_t   SSCG;
    volatile uint32_t   PLLI2SCFG;
};

#define RCC         ( ( rcc_registers_struct* ) ( 0x40023800 ) )

/*
 * Регистры физического модуля FLASH.
 */
struct __attribute__( ( packed ) ) flash_registers_struct {
    volatile uint32_t   ACR;
    volatile uint32_t   KEYR;
    volatile uint32_t   OPTKEYR;
    volatile uint32_t   SR;
    volatile uint32_t   CR;
    volatile uint32_t   OPTCR;
};

#define FLASH         ( ( flash_registers_struct* ) ( 0x40023C00 ) )

/**********************************************************************
 * Область структур.
 **********************************************************************/

/*
 * Структура инициализации объекта класса RCC.
 */
struct rcc_cfg {
    const pll_cfg_struct*           const main_pll_cfg;         // Режимы основного PLL.
    const uint8_t                   pll_count;                  // Количество режимов основного PLL.
    const global_port*              const gb;                   // Для включения тактирования.
};

#endif
