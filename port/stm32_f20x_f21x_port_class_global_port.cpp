#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

#include "stm32_f20x_f21x_port.h"
#include "stm32_f20x_f21x_port_struct.h"
#include "stm32_f20x_f21x_port_struct_class_global_port.h"

// Служебная функция записи образа регистров порта.
void global_port::write_image_port_in_registrs(uint32_t number) const {
	port_registers_struct *port = (port_registers_struct *)gb_msk_struct.port[number].p_port;
	port->mode		= gb_msk_struct.port[number].mode_res;	// Переключаем сначала порт на вход, чтобы ничего не натворить.
															// С учетом особенностей порта.
	port->otype		= gb_msk_struct.port[number].otype;
	port->afl		= gb_msk_struct.port[number].afl;
	port->afh		= gb_msk_struct.port[number].afh;
	port->od		= gb_msk_struct.port[number].od;
	port->pupd		= gb_msk_struct.port[number].pupd;
	port->ospeede	= gb_msk_struct.port[number].speed;
	port->mode		= gb_msk_struct.port[number].mode;
}


/*
 * Переинициализируем все порты ввода-вывода.
 */
answer_global_port global_port::reinit_all_ports() const {
	answer_global_port answer = GLOBAL_PORT_REINIT_SUCCESS;		// Флаг того, что во время переинициализации была обнаружен порт со включенной блокировкой (или же инициализация прошла удачно).
	for (uint32_t loop_port = 0; loop_port < STM32_F2_PORT_COUNT; loop_port++) {
		if (get_state_locked_key_port((enum_port_name)loop_port) == PORT_LOCKED_KAY_SET) {
			answer = GLOBAL_PORT_REINIT_LOOK;
// В случае, если пользователь посчитал, что при обнаружении заблокированного порта не следует пытаться
// переинициализировать незаблокированные выводы, пропускаем дальнейшую попытку переинициализации.
#if defined(NO_REINIT_PORT_AFTER_LOOKING)
			continue;
#endif
		};
		write_image_port_in_registrs(loop_port);		// Записываем образ в регистры (с учётом предосторожностей переключения).
	}
	return answer;
}

answer_global_port	global_port::reinit_port(enum_port_name port) const {
// В случае, если пользователь посчитал, что при обнаружении заблокированного порта не следует пытаться
// переинициализировать незаблокированные выводы, проверяем наличие блокировки. И в случае, если она есть -
// - выходим.
#if defined(NO_REINIT_PORT_AFTER_LOOKING)
	if (get_state_locked_key_port(port) == port_locked_kay_set) const {
		return GLOBAL_PORT_REINIT_LOOK;
	};
#endif
	write_image_port_in_registrs((uint32_t)port);		// Записываем образ в регистры (с учётом предосторожностей переключения).
	return GLOBAL_PORT_REINIT_SUCCESS;
}

// Возвращаем состояние ключа.
port_locked_key global_port::get_state_locked_key_port(enum_port_name port) const {
	if (*U32_TO_P_CONST(gb_msk_struct.port[port].p_look_key)) {
		return PORT_LOCKED_KAY_SET;
	} else {
		return PORT_LOCKED_KAY_RESET;
	}
}

// Производим попытку заблокировать порт.
answer_port_set_lock	global_port::set_locked_key_port(enum_port_name port) const {
	if (get_state_locked_key_port(port) == PORT_LOCKED_KAY_SET) {		// Если порт уже заблокирован.
		return ANSWER_PORT_LOCK_ALREADY;
	}
	port_registers_struct *p = (port_registers_struct *)gb_msk_struct.port[(uint32_t)port].p_port;
	// Специальная последовательность для блокировки порта.
	p->lck = gb_msk_struct.port[port].lck | (1<<16);
	p->lck = gb_msk_struct.port[port].lck;
	p->lck = gb_msk_struct.port[port].lck | (1<<16);
	volatile uint32_t buffer = p->lck;			// Порт должен заблокироваться после этого действия.
	(void)buffer;
	if (get_state_locked_key_port(port) == PORT_LOCKED_KAY_SET) {		// Проверяем.
		return ANSWER_PORT_LOCK_OK;
	} else {
		return ANSWER_PORT_LOCK_ERROR;
	}
}

// Пытаемся заблокировать все порты.
answer_port_set_lock	global_port::set_locked_keys_all_port() const {
	answer_port_set_lock answer = ANSWER_PORT_LOCK_OK;			// Возвратим OK или error, если хоть в одном из портов будет ошибка.
	for (uint32_t loop_port; loop_port < STM32_F2_PORT_COUNT; loop_port++) {
		if (set_locked_key_port((enum_port_name)loop_port) == ANSWER_PORT_LOCK_ERROR) {
			answer == ANSWER_PORT_LOCK_ERROR;
		};
	}
	return answer;
}

#endif
