#ifndef STM32F2_API_PORT_STM32_F20X_F21X_PORT_STRUCT_CLASS_PIN_H_
#define STM32F2_API_PORT_STM32_F20X_F21X_PORT_STRUCT_CLASS_PIN_H_

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

/*
 * Перечень выводов каждого порта.
 */
enum enum_port_pin_name {
	PORT_PIN_0	= 0,	PORT_PIN_1	= 1,	PORT_PIN_2	= 2,	PORT_PIN_3	= 3,
	PORT_PIN_4	= 4,	PORT_PIN_5	= 5,	PORT_PIN_6	= 6,	PORT_PIN_7	= 7,
	PORT_PIN_8	= 8,	PORT_PIN_9	= 9,	PORT_PIN_10	= 10,	PORT_PIN_11	= 11,
	PORT_PIN_12	= 12,	PORT_PIN_13	= 13,	PORT_PIN_14	= 14,	PORT_PIN_15	= 15
};

/*
 * Предназначены для класса описания конфигурации одного вывода.
 */
enum enum_pin_mode {						// Режим вывода:
	PIN_INPUT_MODE					= 0,	// Вход.
	PIN_OUTPUT_MODE					= 1, 	// Выход.
	PIN_ALTERNATE_FUNCTION_MODE		= 2, 	// Альтернативная функция.
	PIN_ANALOG_MODE					= 3		// Аналоговый режим.
};

enum enum_pin_output_config	{				// Режим выхода:
	PIN_OUTPUT_NOT_USE				= 0,	// Вывод не используется как вывод.
	PIN_OUTPUT_PUSH_PULL_CONFIG		= 0,	// "Тянуть-толкать".
	PIN_OUTPUT_OPEN_DRAIN_CONFIG	= 1		// "Открытый сток".
};

enum enum_pin_speed {						// Скорость выхода:
	PIN_LOW_SPEED					= 0,	// Низкая.
	PIN_MEDIUM_SPEED				= 1,	// Средняя.
	PIN_FAST_SPEED					= 2,	// Быстрая.
	PIN_HIGH_SPEED					= 3		// Очень быстрая
};

enum enum_pin_pull {						// Выбор подтяжки:
	PIN_NO_PULL						= 0,	// Без подтяжки.
	PIN_PULL_UP						= 1,	// Подтяжка к питанию.
	PIN_PULL_DOWN					= 2		// Подтяжка к земле.
};

enum enum_pin_alternate_function {	// Выбираем альтернативную функцию, если используется.
	PIN_AF_NOT_USE = 0,				// Альтернативная функция не используется.
	PIN_AF_0	= 0,	PIN_AF_1	= 1,	PIN_AF_2	= 2,	PIN_AF_3	= 3,
	PIN_AF_4	= 4,	PIN_AF_5	= 5,	PIN_AF_6	= 6,	PIN_AF_7	= 7,
	PIN_AF_8	= 8,	PIN_AF_9	= 9,	PIN_AF_10	= 10,	PIN_AF_11	= 11,
	PIN_AF_12	= 12,	PIN_AF_13	= 13,	PIN_AF_14	= 14,	PIN_AF_15	= 15
};

/*
 * Заблокировать настройку вывода после начальной инициализации.
 * Важно! Блокировка применяется только один раз объектом global_port. Во время последующей
 * работы заблокировать иные выводы или же отключить блокировку текущих - невозможно.
 * Единственный способ снять блокировку - перезагрузка чипа.
 */
enum pin_locked {
	PIN_CONFIG_NOT_LOCKED			= 0,	// Не блокировать вывод.
	PIN_CONFIG_LOCKED				= 1		// Заблокировать вывод.
};

enum pin_state_after_init {			// Состояние на выходе после инициализации
									// (в случае, если вывод настроен как выход).
	PIN_STATE_NO_USE				= 0,
	PIN_STATE_AFTER_INIT_RESET		= 0,
	PIN_STATE_AFTER_INIT_SET		= 1
};

/*
 * Структура настройки вывода.
 */
struct __attribute__((packed)) pin_config_t {
	enum_port_name				port;					// Имя порта (пример: port_a).
	enum_port_pin_name			pin_name;				// Номер вывода (пример: port_pin_1).
	enum_pin_mode				mode;					// Режим вывода (пример: pin_output_mode).
	enum_pin_output_config		output_config;			// Режим выхода (пример: pin_output_push_pull_config).
	enum_pin_speed				speed;					// Скорость вывода (пример: pin_low_speed).
	enum_pin_pull				pull;					// Подтяжка вывода (пример: pin_no_pull).
	enum_pin_alternate_function	af;						// Альтернативная функция вывода (пример: pin_af_not_use).
	pin_locked					locked;					// Заблокировать ли настройку данного вывода во время инициализации global_port объекта.
	pin_state_after_init		state_after_init;		// Состояние на выходе после инициализации (в случае, если вывод настроен как выход).
};

#endif
#endif
