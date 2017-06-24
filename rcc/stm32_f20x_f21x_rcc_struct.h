#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

#include <cmath>
#include "stm32_f20x_f21x_rcc_struct_class_pll.h"

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
 * Позиции битовых полей внутрирегистра pllcfg модуля RCC.
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


enum class EC_ANSWER_PLL_STATUS {
    PLL_OFF = 0,
    PLL_ON  = 1
};

enum class EC_ANSWER_PLL_READY_FLAG {
    PLL_UNLOCKED = 0,
    PLL_LOCKED  = 1
};

enum class EC_ANSWER_OSCILLATOR_STATUS {
    OFF = 0,
    ON  = 1
};

enum class EC_ANSWER_OSCILLATOR_STATE {
    NOT_READY = 0,
    READY  = 1
};

enum class  EC_ANSWER_pll_cfg_update {

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

#define RCC             (( rcc_registers_struct* )(0x40023800))

/**********************************************************************
 * Область структур.
 **********************************************************************/

/*
 * Структура инициализации объекта класса RCC.
 */
struct rcc_cfg {
    const pll_cfg_struct*           const main_pll_cfg;         // Режимы основного PLL.
    const uint8_t                   pll_count;                  // Количество режимов основного PLL.
};

#endif
