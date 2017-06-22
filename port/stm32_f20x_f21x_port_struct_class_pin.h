#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

/**********************************************************************
 * Область enum class-ов.
 **********************************************************************/

/*
 * Перечень выводов каждого порта.
 */
enum class EC_PORT_PIN_NAME {
    PIN_0   = 0,
    PIN_1   = 1,
    PIN_2   = 2,
    PIN_3   = 3,
    PIN_4   = 4,
    PIN_5   = 5,
    PIN_6   = 6,
    PIN_7   = 7,
    PIN_8   = 8,
    PIN_9   = 9,
    PIN_10  = 10,
    PIN_11  = 11,
    PIN_12  = 12,
    PIN_13  = 13,
    PIN_14  = 14,
    PIN_15  = 15
};

/*
 * Режим вывода.
 */
enum class EC_PIN_MODE {
    INPUT   = 0,    // Вход.
    OUTPUT  = 1,    // Выход.
    AF      = 2,    // Альтернативная функция.
    ANALOG  = 3     // Аналоговый режим.
};

/*
 * Режим выхода.
 */
enum class EC_PIN_OUTPUT_CFG {
    NO_USE      = 0,    // Вывод не используется как вывод.
    PUSH_PULL   = 0,    // "Тянуть-толкать".
    OPEN_DRAIN  = 1     // "Открытый сток".
};

/*
 * Скорость выхода.
 */
enum class EC_PIN_SPEED {
    LOW         = 0,    // Низкая.
    MEDIUM      = 1,    // Средняя.
    FAST        = 2,    // Быстрая.
    HIGH        = 3     // Очень быстрая
};

/*
 * Выбор подтяжки
 */
enum class EC_PIN_PULL {
    NO_USE  = 0,    // Без подтяжки.
    UP      = 1,    // Подтяжка к питанию.
    DOWN    = 2     // Подтяжка к земле.
};

/*
 * Выбираем альтернативную функцию, если используется.
 */
enum class EC_PIN_AF {
    AF_0        = 0,
    NO_USE      = AF_0,
    SYS         = AF_0,

    AF_1        = 1,
    TIM1        = AF_1,
    TIM2        = AF_1,

    AF_2        = 2,
    TIM3        = AF_2,
    TIM4        = AF_2,
    TIM5        = AF_2,

    AF_3        = 3,
    TIM8        = AF_3,
    TIM9        = AF_3,
    TIM10       = AF_3,
    TIM11       = AF_3,

    AF_4        = 4,
    I2C1        = AF_4,
    I2C2        = AF_4,
    I2C3        = AF_4,

    AF_5        = 5,
    SPI1        = AF_5,
    SPI2        = AF_5,
    I2S2        = AF_5,


    AF_6        = 6,
    SPI3        = AF_6,
    I2S3        = AF_6,

    AF_7        = 7,
    USART1      = AF_7,
    USART2      = AF_7,
    USART3      = AF_7,

    AF_8        = 8,
    UART4       = AF_8,
    UART5       = AF_8,
    USART6      = AF_8,

    AF_9        = 9,
    CAN1        = AF_9,
    CAN2        = AF_9,
    TIM12       = AF_9,
    TIM13       = AF_9,
    TIM14       = AF_9,

    AF_10       = 10,
    OTG_FS      = AF_10,

    AF_11       = 11,
    ETH         = AF_11,

    AF_12       = 12,
    FSMC        = AF_12,
    SDIO        = AF_12,

    AF_13       = 13,
    DCMI        = AF_13,

    AF_14       = 14,

    AF_15       = 15,
    EVENTOUT    = AF_15
};

/*
 * Разрешено ли блокировать конфигурацию вывода методами set_locked_key_port и
 * set_locked_keys_all_port объекту класса global_port.
 * Важно! Блокировка применяется только один раз объектом global_port. Во время последующей
 * работы заблокировать иные выводы или же отключить блокировку текущих - невозможно.
 * Единственный способ снять блокировку - перезагрузка чипа.
 */
enum class EC_LOCKED {
    NOT_LOCKED  = 0,    // Не блокировать вывод.
    LOCKED      = 1     // Заблокировать вывод.
};

/*
 * Состояние на выходе после инициализации
 * (в случае, если вывод настроен как выход).
 */
enum class EC_PIN_STATE_AFTER_INIT {
    NO_USE  = 0,
    RESET   = 0,
    SET     = 1
};

/*
 * Возвращаемое значение функции переинициализации порта.
 */
enum class EC_ANSWER_PIN_REINIT {
    OK                  = 0,    // Вывод был успешно переинициализирован.
    LOCKED              = 1,    // Конфигурация вывода была заблокирована.
    CFG_NUMBER_ERROR    = 2     // Вы попытались инициализировать вывод несуществующей конфигурацией.
};

/**********************************************************************
 * Область упакованных структур.
 **********************************************************************/

/*
 * Перечень регистров физического порта ввода-вывода.
 */
struct __attribute__( ( packed ) ) port_registers_struct {
    volatile uint32_t   mode;       // Регистр выбора режима работы выводов.
    volatile uint32_t   otype;      // Регистр выбора режима выхода
                                    // ( в случае, если вывод настроен как выход ).
    volatile uint32_t   ospeede;    // Регистр выбора скорости выводов.
    volatile uint32_t   pupd;       // Регистр включения подтяжки выводов.
    volatile uint32_t   id;         // Регистр с текущими данными на входе вывода.
    volatile uint32_t   od;         // Регистр с выставленными пользователем на выход данными
                                    // ( в случае, если вывод настроен как выход ).
    volatile uint32_t   bsr;        // Регистр быстрой установки состояния выводов
                                    // ( когда вывод настроен как выход ).
    volatile uint32_t   lck;        // Регистр блокировки настроек.
    volatile uint32_t   afl;        // Младший регистр настройки альтернативных функций выводов.
    volatile uint32_t   afh;        // Старший регистр настройки альтернативных функций выводов.
};

/*
 * Структура конфигурации вывода.
 */
struct __attribute__( ( packed ) ) pin_config_t {
    EC_PORT_NAME                port;               // Имя порта ( пример: EC_PORT_NAME::A ).
    EC_PORT_PIN_NAME            pin_name;           // Номер вывода ( пример: EC_PORT_PIN_NAME::PIN_0 ).
    EC_PIN_MODE                 mode;               // Режим вывода ( пример: EC_PIN_MODE::OUTPUT ).
    EC_PIN_OUTPUT_CFG           output_config;      // Режим выхода ( пример: EC_PIN_OUTPUT_CFG::NOT_USE ).
    EC_PIN_SPEED                speed;              // Скорость вывода ( пример: EC_PIN_SPEED::MEDIUM ).
    EC_PIN_PULL                 pull;               // Подтяжка вывода ( пример: EC_PIN_PULL::NO ).
    EC_PIN_AF                   af;                 // Альтернативная функция вывода ( пример: EC_PIN_AF::NOT_USE ).
    EC_LOCKED                   locked;             // Заблокировать ли настройку данного
                                                    // вывода во время инициализации global_port объекта ( пример EC_LOCKED::NOT_LOCKED ).
    EC_PIN_STATE_AFTER_INIT     state_after_init;   // Состояние на выходе после инициализации
                                                    // ( в случае, если вывод настроен как выход ).
                                                    // (пример EC_PIN_STATE_AFTER_INIT::NO_USE).
};

/**********************************************************************
 * Область template оболочек.
 **********************************************************************/
template < EC_PORT_NAME              PORT,
           EC_PORT_PIN_NAME          PIN_NAME,
           EC_PIN_MODE               MODE,
           EC_PIN_OUTPUT_CFG         OUTPUT_CONFIG,
           EC_PIN_SPEED              SPEED,
           EC_PIN_PULL               PULL,
           EC_PIN_AF                 AF,
           EC_LOCKED                 LOCKED,
           EC_PIN_STATE_AFTER_INIT   STATE_AFTER_INIT >
class pin_config_check_param : public pin_config_t {
public:
    constexpr pin_config_check_param(): pin_config_t( {
        .port               = PORT,
        .pin_name           = PIN_NAME,
        .mode               = MODE,
        .output_config      = OUTPUT_CONFIG,
        .speed              = SPEED,
        .pull               = PULL,
        .af                 = AF,
        .locked             = LOCKED,
        .state_after_init   = STATE_AFTER_INIT
    } ) {
/*
 * Проверяем введенные пользователем данные в структуру инициализации.
 */
#if defined(STM32F205RB)|defined(STM32F205RC)|defined(STM32F205RE) \
    |defined(STM32F205RF)|defined(STM32F205RG)
            static_assert( PORT >= EC_PORT_NAME::A && PORT <= EC_PORT_NAME::H, "Invalid port name. The port name must be A..H." );
#endif
            static_assert( PIN_NAME >= EC_PORT_PIN_NAME::PIN_0 && PIN_NAME <= EC_PORT_PIN_NAME::PIN_15, "Invalid output name. An output with this name does not exist in any port. The output can have a name PIN_0..PIN_15." );
            static_assert( MODE >= EC_PIN_MODE::INPUT && MODE <= EC_PIN_MODE::ANALOG, "The selected mode does not exist. The output can be set to mode: INPUT, OUTPUT, AF or ANALOG." );
            static_assert( OUTPUT_CONFIG == EC_PIN_OUTPUT_CFG::PUSH_PULL || OUTPUT_CONFIG == EC_PIN_OUTPUT_CFG::OPEN_DRAIN, "A non-existent output mode is selected. The output can be in the mode: PUSH_PULL, OPEN_DRAIN." );
            static_assert( SPEED >= EC_PIN_SPEED::LOW && SPEED <= EC_PIN_SPEED::HIGH, "A non-existent mode of port speed is selected. Possible modes: LOW, MEDIUM, FAST or HIGH." );
            static_assert( PULL >= EC_PIN_PULL::NO_USE && PULL <= EC_PIN_PULL::DOWN, "A non-existent brace mode is selected. The options are: NO_USE, UP or DOWN." );
            static_assert( AF >= EC_PIN_AF::AF_0 && AF <= EC_PIN_AF::AF_15, "A non-existent mode of the alternative port function is selected." );
            static_assert( LOCKED == EC_LOCKED::NOT_LOCKED || LOCKED == EC_LOCKED::LOCKED, "Invalid port lock mode selected." );
            static_assert( STATE_AFTER_INIT == EC_PIN_STATE_AFTER_INIT::NO_USE || STATE_AFTER_INIT == EC_PIN_STATE_AFTER_INIT::SET, "The wrong state of the output is selected. The status can be: NO_USE, UP or DOWN." );
    };
};

template < EC_PORT_NAME              PORT,
           EC_PORT_PIN_NAME          PIN_NAME >
class pin_config_adc_check_param : public pin_config_check_param< PORT, PIN_NAME,
                                                                  EC_PIN_MODE::INPUT,
                                                                  EC_PIN_OUTPUT_CFG::NO_USE,
                                                                  EC_PIN_SPEED::LOW,
                                                                  EC_PIN_PULL::UP,
                                                                  EC_PIN_AF::NO_USE,
                                                                  EC_LOCKED::LOCKED,
                                                                  EC_PIN_STATE_AFTER_INIT::NO_USE > {
public:
    constexpr pin_config_adc_check_param() {};
};

#endif
