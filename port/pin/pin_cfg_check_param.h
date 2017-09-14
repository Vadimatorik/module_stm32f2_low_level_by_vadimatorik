#pragma once

#include "pin_struct.h"

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
//
// Проверяем введенные пользователем данные в структуру инициализации.
//
#if defined(STM32F205RB)|defined(STM32F205RC)|defined(STM32F205RE) \
    |defined(STM32F205RF)|defined(STM32F205RG)
            static_assert( PORT >= EC_PORT_NAME::A &&
                    PORT <= EC_PORT_NAME::H,
                    "Invalid port name. The port name must be A..H." );
#endif

            static_assert( PIN_NAME >= EC_PORT_PIN_NAME::PIN_0 &&
                    PIN_NAME <= EC_PORT_PIN_NAME::PIN_15,
                    "Invalid output name. An output with this name does not"
                    "exist in any port. The output can have a name PIN_0..PIN_15." );

            static_assert( MODE >= EC_PIN_MODE::INPUT &&
                    MODE <= EC_PIN_MODE::ANALOG,
                    "The selected mode does not exist. "
                    "The output can be set to mode: INPUT, OUTPUT, AF or ANALOG." );

            static_assert( OUTPUT_CONFIG == EC_PIN_OUTPUT_CFG::PUSH_PULL ||
                    OUTPUT_CONFIG == EC_PIN_OUTPUT_CFG::OPEN_DRAIN,
                    "A non-existent output mode is selected. "
                    "The output can be in the mode: PUSH_PULL, OPEN_DRAIN." );

            static_assert( SPEED >= EC_PIN_SPEED::LOW &&
                    SPEED <= EC_PIN_SPEED::HIGH,
                    "A non-existent mode of port speed is selected. "
                    "Possible modes: LOW, MEDIUM, FAST or HIGH." );

            static_assert( PULL >= EC_PIN_PULL::NO_USE &&
                    PULL <= EC_PIN_PULL::DOWN,
                    "A non-existent brace mode is selected."
                    "The options are: NO_USE, UP or DOWN." );

            static_assert( AF >= EC_PIN_AF::AF_0 &&
                    AF <= EC_PIN_AF::AF_15,
                    "A non-existent mode of the alternative port function is selected." );

            static_assert( LOCKED == EC_LOCKED::NOT_LOCKED ||
                    LOCKED == EC_LOCKED::LOCKED,
                    "Invalid port lock mode selected." );

            static_assert( STATE_AFTER_INIT == EC_PIN_STATE_AFTER_INIT::NO_USE ||
                    STATE_AFTER_INIT == EC_PIN_STATE_AFTER_INIT::SET,
                    "The wrong state of the output is selected."
                    "The status can be: NO_USE, UP or DOWN." );
    }
};

template < EC_PORT_NAME              PORT,
           EC_PORT_PIN_NAME          PIN_NAME >
class pin_config_adc_check_param : public pin_config_check_param< PORT, PIN_NAME,
                                                                  EC_PIN_MODE::ANALOG,
                                                                  EC_PIN_OUTPUT_CFG::NO_USE,
                                                                  EC_PIN_SPEED::HIGH,
                                                                  EC_PIN_PULL::NO_USE,
                                                                  EC_PIN_AF::NO_USE,
                                                                  EC_LOCKED::LOCKED,
                                                                  EC_PIN_STATE_AFTER_INIT::NO_USE > {
public:
    constexpr pin_config_adc_check_param() {}
};
