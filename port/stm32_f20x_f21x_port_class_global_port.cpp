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
E_ANSWER_GP global_port::reinit_all_ports() const {
	E_ANSWER_GP answer = E_ANSWER_GP::SUCCESS;		// Флаг того, что во время переинициализации была обнаружен порт со включенной блокировкой (или же инициализация прошла удачно).
	for (uint32_t loop_port = 0; loop_port < STM32_F2_PORT_COUNT; loop_port++) {
		if (get_state_locked_key_port((EC_PORT_NAME)loop_port) == E_PORT_LOCKED_KEY::SET) {
			answer = E_ANSWER_GP::LOOK;
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

E_ANSWER_GP	global_port::reinit_port(EC_PORT_NAME port) const {
// В случае, если пользователь посчитал, что при обнаружении заблокированного порта не следует пытаться
// переинициализировать незаблокированные выводы, проверяем наличие блокировки. И в случае, если она есть -
// - выходим.
#if defined(NO_REINIT_PORT_AFTER_LOOKING)
	if (get_state_locked_key_port(port) == port_locked_kay_set) const {
		return E_ANSWER_GP::LOOK;
	};
#endif
	write_image_port_in_registrs((uint32_t)port);		// Записываем образ в регистры (с учётом предосторожностей переключения).
	return E_ANSWER_GP::SUCCESS;
}

// Возвращаем состояние ключа.
E_PORT_LOCKED_KEY global_port::get_state_locked_key_port(EC_PORT_NAME port) const {
	if (*M_U32_TO_P_CONST(gb_msk_struct.port[M_EC_TO_U8(port)].p_look_key)) {
		return E_PORT_LOCKED_KEY::SET;
	} else {
		return E_PORT_LOCKED_KEY::RESET;
	}
}

// Производим попытку заблокировать порт.
E_ANSWER_PORT_SET_LOCK	global_port::set_locked_key_port(EC_PORT_NAME port) const {
	if (get_state_locked_key_port(port) == E_PORT_LOCKED_KEY::SET) {		// Если порт уже заблокирован.
		return E_ANSWER_PORT_SET_LOCK::ALREADY;
	}
	port_registers_struct *p = (port_registers_struct *)gb_msk_struct.port[(uint32_t)port].p_port;
	// Специальная последовательность для блокировки порта.
	p->lck = gb_msk_struct.port[M_EC_TO_U8(port)].lck | (1<<16);
	p->lck = gb_msk_struct.port[M_EC_TO_U8(port)].lck;
	p->lck = gb_msk_struct.port[M_EC_TO_U8(port)].lck | (1<<16);
	volatile uint32_t buffer = p->lck;			// Порт должен заблокироваться после этого действия.
	(void)buffer;
	if (get_state_locked_key_port(port) == E_PORT_LOCKED_KEY::SET) {		// Проверяем.
		return E_ANSWER_PORT_SET_LOCK::OK;
	} else {
		return E_ANSWER_PORT_SET_LOCK::ERROR;
	}
}

// Пытаемся заблокировать все порты.
E_ANSWER_PORT_SET_LOCK	global_port::set_locked_keys_all_port() const {
	E_ANSWER_PORT_SET_LOCK answer = E_ANSWER_PORT_SET_LOCK::OK;			// Возвратим OK или error, если хоть в одном из портов будет ошибка.
	for (uint32_t loop_port; loop_port < STM32_F2_PORT_COUNT; loop_port++) {
		if (set_locked_key_port((EC_PORT_NAME)loop_port) == E_ANSWER_PORT_SET_LOCK::ERROR) {
			answer == E_ANSWER_PORT_SET_LOCK::ERROR;
		};
	}
	return answer;
}

#endif
