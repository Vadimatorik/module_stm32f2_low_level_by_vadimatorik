#ifndef STM32F2_API_PORT_STM32_F20X_F21X_PORT_STRUCT_CLASS_GLOBAL_PORT_H_
#define STM32F2_API_PORT_STM32_F20X_F21X_PORT_STRUCT_CLASS_GLOBAL_PORT_H_

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

/*
 * Структура содержит в себе маски портов всех имеющихся регистров.
 * STM32_F2_PORT_COUNT - этот define автоматически определяется при
 * выборе конкретного контроллера в stm32_f20x_f21x_conf.h
 */
struct __attribute__((packed)) global_port_msk_reg_struct {
	port_registers_flash_copy_struct	port[STM32_F2_PORT_COUNT];
};

enum answer_pin_reinit {						// Возвращаемые значения функции пере инициализации порта
	ANSWER_PIN_REINIT_OK				= 0,	// Вывод был успешно пере инициализирован.
	ANSWER_PIN_REINIT_LOCKED			= 1,	// Конфигурация вывода была заблокирована.
	ANSWER_PIN_REINIT_CFG_NUMBER_ERROR	= 2		// Вы попытались инициализировать вывод несуществующей конфигурацией.
};

/*
 * Ответы от функций reinit_all, reinit_port объекта global_port.
 */
enum answer_global_port {
	GLOBAL_PORT_REINIT_SUCCESS			= 0,	// Переинициализация была успешной.
	GLOBAL_PORT_REINIT_LOOK				= 1		// Порт заблокирован, переинициализация некоторых
												// (или всех) выводов невозможна.
	// В случае reinit_all может быть, что выводы одного или нескольких портов не были переинициализированы.
	// В случае обнаружения блокировки порта - производится попытка пере инициализации (на случай, если
	// требуется пере инициализировать те выводы, которые заблокированы не были).
	// Данное поведение можно изменить раскомментировав define NO_REINIT_PORT_AFTER_LOOKING в файле
	// stm32_f20x_f21x_conf.h.
};

// Состояние ключа блокировки порта.
enum port_locked_key {
	PORT_LOCKED_KAY_SET					= 1,
	PORT_LOCKED_KAY_RESET				= 0
};

// Возвращаемые значения функции блокировки порта/портов.
enum answer_port_set_lock {
	ANSWER_PORT_LOCK_OK			= 0,			// Порт был успешно заблокирован.
	ANSWER_PORT_LOCK_ALREADY	= 1,			// Порт был уже заблокирован до нас.
	ANSWER_PORT_LOCK_ERROR		= 2				// После попытки заблокировать порт - порт не был заблокирован.
};

// Готовые шаблоны.
/*
 * Данный макрос следует использовать вместо ручного заполнения
 * структуры конфигурации вывода (pin_config_t), когда вывод
 * используется как вход ADC и не меняет своей функции на протяжении
 * всего времени жизни программы.
 *
 * Пример использования.
 * До:
 * const constexpr pin_config_t ayplayer_pin_cfg = {
		.port				= PORT_A,
		.pin_name			= PORT_PIN_0,
		.mode				= PIN_ANALOG_MODE,
		.output_config		= PIN_OUTPUT_NOT_USE,
		.speed				= PIN_LOW_SPEED,
		.pull				= PIN_NO_PULL,
		.af					= PIN_AF_NOT_USE,
		.locked				= PIN_CONFIG_LOCKED,
		.state_after_init	= PIN_STATE_NO_USE
	};
	После:
	const constexpr pin_config_t ayplayer_pin_cfg = MACRO_PIN_CFG_ADC(PORT_A, PORT_PIN_0);
 */

#define MACRO_PIN_CFG_ADC(PORT,PIN)	{				\
	.port				= PORT,						\
	.pin_name			= PIN,						\
	.mode				= PIN_ANALOG_MODE,			\
	.output_config		= PIN_OUTPUT_NOT_USE,		\
	.speed				= PIN_LOW_SPEED,			\
	.pull				= PIN_NO_PULL,				\
	.af					= PIN_AF_NOT_USE,			\
	.locked				= PIN_CONFIG_LOCKED,		\
	.state_after_init	= PIN_STATE_NO_USE			\
}

#endif
#endif
