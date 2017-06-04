#ifndef STM32F2_API_PORT_STM32_F20X_F21X_PORT_STRUCT_CLASS_PIN_H_
#define STM32F2_API_PORT_STM32_F20X_F21X_PORT_STRUCT_CLASS_PIN_H_

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

/**********************************************************************
 * Область упакованных структур.
 **********************************************************************/

/*
 * Перечень регистров физического порта ввода-вывода.
 */
struct __attribute__((packed)) port_registers_struct {
	volatile uint32_t	mode;		// Регистр выбора режима работы выводов.
	volatile uint32_t	otype;		// Регистр выбора режима выхода
									// ( в случае, если вывод настроен как выход ).
	volatile uint32_t	ospeede;	// Регистр выбора скорости выводов.
	volatile uint32_t	pupd;		// Регистр включения подтяжки выводов.
	volatile uint32_t	id;			// Регистр с текущими данными на входе вывода.
	volatile uint32_t	od;			// Регистр с выставленными пользователем на выход данными
									// ( в случае, если вывод настроен как выход ).
	volatile uint32_t	bsr;		// Регистр быстрой установки состояния выводов
									// ( когда вывод настроен как выход ).
	volatile uint32_t	lck;		// Регистр блокировки настроек.
	volatile uint32_t	afl;		// Младший регистр настройки альтернативных функций выводов.
	volatile uint32_t	afh;		// Старший регистр настройки альтернативных функций выводов.
};

/*
 * Перечень выводов каждого порта.
 */
enum class EC_PORT_PIN_NAME {
	PIN_0	= 0,	PIN_1	= 1,	PIN_2	= 2,	PIN_3	= 3,
	PIN_4	= 4,	PIN_5	= 5,	PIN_6	= 6,	PIN_7	= 7,
	PIN_8	= 8,	PIN_9	= 9,	PIN_10	= 10,	PIN_11	= 11,
	PIN_12	= 12,	PIN_13	= 13,	PIN_14	= 14,	PIN_15	= 15
};

/*
 * Предназначены для класса описания конфигурации одного вывода.
 */
enum class EC_PIN_MODE {			// Режим вывода:
	INPUT			= 0,			// Вход.
	OUTPUT			= 1, 			// Выход.
	AF				= 2, 			// Альтернативная функция.
	ANALOG			= 3				// Аналоговый режим.
};

enum class EC_PIN_OUTPUT_CFG {		// Режим выхода:
	NOT_USE			= 0,			// Вывод не используется как вывод.
	PUSH_PULL		= 0,			// "Тянуть-толкать".
	OPEN_DRAIN		= 1				// "Открытый сток".
};

enum class EC_PIN_SPEED {			// Скорость выхода:
	LOW				= 0,			// Низкая.
	MEDIUM			= 1,			// Средняя.
	FAST			= 2,			// Быстрая.
	HIGH			= 3				// Очень быстрая
};

enum class EC_PIN_PULL {			// Выбор подтяжки:
	NO				= 0,			// Без подтяжки.
	UP				= 1,			// Подтяжка к питанию.
	DOWN			= 2				// Подтяжка к земле.
};

enum class EC_PIN_AF {				// Выбираем альтернативную функцию, если используется.
	NOT_USE = 0,					// Альтернативная функция не используется.
	AF_0	= 0,	AF_1	= 1,	AF_2	= 2,	AF_3	= 3,
	AF_4	= 4,	AF_5	= 5,	AF_6	= 6,	AF_7	= 7,
	AF_8	= 8,	AF_9	= 9,	AF_10	= 10,	AF_11	= 11,
	AF_12	= 12,	AF_13	= 13,	AF_14	= 14,	AF_15	= 15
};

/*
 * Заблокировать настройку вывода после начальной инициализации.
 * Важно! Блокировка применяется только один раз объектом global_port. Во время последующей
 * работы заблокировать иные выводы или же отключить блокировку текущих - невозможно.
 * Единственный способ снять блокировку - перезагрузка чипа.
 */
enum class EC_LOCKED {
	NOT_LOCKED		= 0,			// Не блокировать вывод.
	LOCKED			= 1				// Заблокировать вывод.
};

enum class EC_PIN_STATE_AFTER_INIT {	// Состояние на выходе после инициализации
									// (в случае, если вывод настроен как выход).
	NO_USE				= 0,
	RESET				= 0,
	SET					= 1
};

enum class EC_ANSWER_PIN_REINIT {	// Возвращаемые значения функции пере инициализации порта
	OK					= 0,		// Вывод был успешно пере инициализирован.
	LOCKED				= 1,		// Конфигурация вывода была заблокирована.
	CFG_NUMBER_ERROR	= 2			// Вы попытались инициализировать вывод несуществующей конфигурацией.
};

/*
 * Структура настройки вывода.
 */
struct __attribute__((packed)) pin_config_t {
	EC_PORT_NAME				port;					// Имя порта (пример: port_a).
	EC_PORT_PIN_NAME			pin_name;				// Номер вывода (пример: port_pin_1).
	EC_PIN_MODE					mode;					// Режим вывода (пример: pin_output_mode).
	EC_PIN_OUTPUT_CFG			output_config;			// Режим выхода (пример: pin_output_push_pull_config).
	EC_PIN_SPEED				speed;					// Скорость вывода (пример: pin_low_speed).
	EC_PIN_PULL					pull;					// Подтяжка вывода (пример: pin_no_pull).
	EC_PIN_AF					af;						// Альтернативная функция вывода (пример: pin_af_not_use).
	EC_LOCKED					locked;					// Заблокировать ли настройку данного вывода во время инициализации global_port объекта.
	EC_PIN_STATE_AFTER_INIT		state_after_init;		// Состояние на выходе после инициализации (в случае, если вывод настроен как выход).
};

#define M_PIN_CFG_ADC(PORT,PIN)	{							\
	.port				= PORT,								\
	.pin_name			= PIN,								\
	.mode				= EC_PIN_MODE::ANALOG,				\
	.output_config		= EC_PIN_OUTPUT_CFG::NOT_USE,		\
	.speed				= EC_PIN_SPEED::LOW,				\
	.pull				= EC_PIN_PULL::NO,					\
	.af					= EC_PIN_AF::NOT_USE,				\
	.locked				= EC_LOCKED::LOCKED,				\
	.state_after_init	= EC_PIN_STATE_AFTER_INIT::NO_USE	\
}

#endif
#endif
