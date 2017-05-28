#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

#include "stm32_f20x_f21x_port.h"
#include "stm32_f20x_f21x_port_struct.h"
#include "stm32_f20x_f21x_port_struct_class_pin.h"

/*
 * В данном файле содержатся только исполняемые в реальном времени контроллером функции.
 */
// Устанавливаем бит.
void pin::set() const {
	*U32_TO_P(p_odr) = set_msk;
}

// Сбрасываем бит.
void pin::reset() const {
	*U32_TO_P(p_odr) = reset_msk;
}

// Инавертируем бит.
void pin::invert() const {
	if (*U32_TO_P_CONST(p_bb_odr_read)) {			// Если был 1, то выставляем 0.
		*U32_TO_P(p_odr) = reset_msk;
	} else {
		*U32_TO_P(p_odr) = set_msk;
	}
}

// Считываем текущее состояние на выводе.
int pin::read() const {
	return *U32_TO_P_CONST(p_bb_idr_read);
}

// Переинициализируем вывод выбранной конфигурацией.
answer_pin_reinit pin::reinit (uint32_t number_config) const{
	if (number_config >= count) return ANSWER_PIN_REINIT_CFG_NUMBER_ERROR;		// Защита от попытки инициализации вывода несуществующей конфигурацией.
	if (*U32_TO_P_CONST(p_bb_key_looking)										// Если порт, к кторому относится вывод был заблокирован.
			&& *U32_TO_P_CONST(p_bb_looking_bit))								// И сам вывод так же был заблокирован.
		return ANSWER_PIN_REINIT_LOCKED;										// Выходим с ошибкой.

	port_registers_struct *port = (port_registers_struct *)p_port;
	// Если дошли до сюда, то вывод можно переинициализировать.
	port->mode		&= ~(0b11 << cfg[number_config].pin_name * 2);						// Переводим вывод в режим "входа" (чтобы не было неготивных последствий от переключений).
	port->otype	&= ~(1 << cfg[number_config].pin_name);								// Далее все как в constexpr функциях, инициализирующие маски портов.
	port->otype	|= cfg[number_config].output_config << cfg[number_config].pin_name;
	port->ospeede	&= ~(0b11 << cfg[number_config].pin_name * 2);
	port->ospeede	|= cfg[number_config].speed << cfg[number_config].pin_name * 2;
	port->pupd		&= ~(0b11 << cfg[number_config].pin_name * 2);
	port->pupd		|= cfg[number_config].pull << cfg[number_config].pin_name * 2;
	if (cfg[number_config].pin_name < PORT_PIN_8) {
		port->afl &= ~(0b1111 << cfg[number_config].pin_name * 4);
		port->afl |= cfg[number_config].locked << cfg[number_config].pin_name * 4;
	} else {
		port->afh &= ~(0b1111 << (cfg[number_config].pin_name - 8) * 4);
		port->afh |= cfg[number_config].locked << (cfg[number_config].pin_name - 8) * 4;
	}
	port->mode |= cfg[number_config].mode << cfg[number_config].pin_name * 2;	// Выставляем тот режим, который указан в конфигурации.

	return ANSWER_PIN_REINIT_CFG_NUMBER_ERROR;
}

#endif
