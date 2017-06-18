#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

#include "stm32_f20x_f21x_port.h"

/*
 * Метод производит переинициализацию вывода
 * выбранной структурой.
 */
EC_ANSWER_PIN_REINIT many_configurations_pin::reinit ( uint8_t number_config ) const{
    if (number_config >= cfg_count) return EC_ANSWER_PIN_REINIT::CFG_NUMBER_ERROR;      // Защита от попытки инициализации вывода несуществующей конфигурацией.
    if (*M_U32_TO_P_CONST(p_bb_key_looking)                                             // Если порт, к кторому относится вывод был заблокирован.
	        && *M_U32_TO_P_CONST(p_bb_looking_bit))                                     // И сам вывод так же был заблокирован.
	    return EC_ANSWER_PIN_REINIT::LOCKED;                                            // Выходим с ошибкой.

    port_registers_struct *port = (port_registers_struct *)p_port;
    // Если дошли до сюда, то вывод можно переинициализировать.
    port->mode      &= ~(0b11 << M_EC_TO_U8(cfg[number_config].pin_name) * 2);          // Переводим вывод в режим "входа"
                                                                                        // (чтобы не было неготивных последствий от переключений).
    port->otype     &= ~(1 << M_EC_TO_U8(cfg[number_config].pin_name));                 // Далее все как в constexpr функциях, инициализирующие маски портов.
    port->otype     |= M_EC_TO_U8(cfg[number_config].output_config) <<
                       M_EC_TO_U8(cfg[number_config].pin_name);
    port->ospeede   &= ~(0b11 << M_EC_TO_U8(cfg[number_config].pin_name) * 2);
    port->ospeede   |= M_EC_TO_U8(cfg[number_config].speed) <<
                       M_EC_TO_U8(cfg[number_config].pin_name) * 2;
    port->pupd      &= ~(0b11 << M_EC_TO_U8(cfg[number_config].pin_name) * 2);
    port->pupd      |= M_EC_TO_U8(cfg[number_config].pull) << M_EC_TO_U8(cfg[number_config].pin_name) * 2;

    if ( M_EC_TO_U8(cfg[number_config].pin_name) < M_EC_TO_U8(EC_PORT_PIN_NAME::PIN_8) ) {
        port->afl   &= ~(0b1111 << M_EC_TO_U8(cfg[number_config].pin_name) * 4);
        port->afl   |= M_EC_TO_U8(cfg[number_config].locked) << (M_EC_TO_U8(cfg[number_config].pin_name) * 4);
    } else {
        port->afh   &= ~(0b1111 << (M_EC_TO_U8(cfg[number_config].pin_name) - 8) * 4);
        port->afh   |= M_EC_TO_U8(cfg[number_config].locked) <<
                       (M_EC_TO_U8(cfg[number_config].pin_name) - 8) * 4;
    }
    port->mode |= M_EC_TO_U8(cfg[number_config].mode) <<
                  M_EC_TO_U8(cfg[number_config].pin_name) * 2;  // Выставляем тот режим, который указан в конфигурации.

    return EC_ANSWER_PIN_REINIT::OK;
}

#endif
