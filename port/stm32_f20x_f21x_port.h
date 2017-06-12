#ifndef STM32F2_API_STM32_F20X_F21X_PORT_H_
#define STM32F2_API_STM32_F20X_F21X_PORT_H_

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

#include "stm32_f20x_f21x_port_struct.h"
#include "stm32_f20x_f21x_port_constexpr_func.h"

/*
 * В данном файле содержатся классы объектов для полноценной работы с портами ввода-вывода.
 * Краткое описание:
 * global_port	- данный объект позволяет работать со всеми имеющимися в контроллере портами ввода-вывода.
 *                В проекте должен быть один экземляр (объект) данного класса.
 *                Объект предоставляет следующие возможности:
 *                1. Переинициализации конкретных или всех портов (при условии, что те не были заблокированы).
 *                		О блокировки более подробно написано в описании global_port класса.
 *                2. Имеется возможность блокировки конкретных или всех портов.
 *                3. Получаение данных о текущем состоянии блокировки.
 * Примечание: Для инициализации объекта используются массив структур pin_config.
 * 1. В случае, если не была передана структура какого-либо вывода (структура, описывающая режим работы вывода),
 * то он настроен в состояние по умолчанию (за исключением некоторых выводов, предназначенных для отладки,
 * это "вход без подтяжки").
 * 2. На каждый вывод порта должна быть одна структура. В случае, если на один вывод будет передано несколько
 * структур - вывод будет переинициализирован именно по последней указанной (чей индекс в массиве старше).
 * 3. Объект не предполагает работу с конкретными выводами. Наименьшая единица, которой может упровлять объект -
 * - порт.
 * 4. Массив объектов pin_config (объявленных как constexpr const), не должен быть помещен во flash память
 * (линкер автоматически выкинет их из .elf или любого другого конечного файла прошивки). Т.к. объект использует
 * constexpr методы, которые анализируют все переданные в объект структуры и выдают на выходе готовые маски портов.
 * С помощью которых можно значительно ускорить процесс инициализации портов.
 */

/*
 * Класс для создания объекта линии ввода-вывода.
 * Прототип (объект) данного класса следует создавать в том случае, когда вывод точно будет использоваться
 * в ручном (управляется пользователем) режиме. Помимо этого разрешено использование и других конфигураций этой же
 * линии порта ввода-вывода, которые можно менять в процессе работы. Подробнее в примерах.
 */

#include "stm32_f20x_f21x_port_struct_class_pin.h"

class pin {
public:
	constexpr pin ( const pin_config_t* const pin_cfg_array,  uint8_t size = 1 );

	void	set		( void ) const;
	void	reset	( void ) const;
	void	set		( uint8_t state ) const;
	void	set		( bool state ) const;
	void	set		( int state ) const;
	void	invert	( void ) const;
	int		read	( void ) const;

	EC_ANSWER_PIN_REINIT	reinit	(uint8_t number_config) const;

private:
	constexpr uint32_t	set_msk_get				( const pin_config_t *const pin_cfg_array );
	constexpr uint32_t	reset_msk_get			( const pin_config_t *const pin_cfg_array );
	constexpr uint32_t	bb_p_idr_read_get		( const pin_config_t *const pin_cfg_array );
	constexpr uint32_t	p_odr_get				( const pin_config_t *const pin_cfg_array );
	constexpr uint32_t	odr_bit_read_bb_p_get	( const pin_config_t *const pin_cfg_array );
	constexpr uint32_t	bb_p_looking_bit_get	( const pin_config_t *const pin_cfg_array );

	const uint32_t	cfg_count;
	const uint32_t	p_odr;
	const uint32_t	p_port;
	const uint32_t	p_bb_odr_read;

	const uint32_t	odr_set_msk;
	const uint32_t	odr_reset_msk;
	const uint32_t	p_bb_idr_read;
	const uint32_t	p_bb_key_looking;
	const uint32_t	p_bb_looking_bit;

	const pin_config_t	*cfg;
};

#include "stm32_f20x_f21x_port_constexpr_func_class_pin.h"

/*
 * Класс глобального порта. Через него происходит управление выводами и сменой конфигурации.
 */

#include "stm32_f20x_f21x_port_struct_class_global_port.h"			// Структуры обоих классов.

class global_port {
public:
	constexpr	global_port	( const pin_config_t *const pin_cfg_array, const uint32_t pin_count );

	// Важно: в случае, если некоторые (или все) выводы порта/портов были заблокированы,
	// попытка переинициализации все равно производится.
	// Это нужно на случай, когда требуется переинициализировать некоторые (1 и более) выводов
	// не трогая другие.
	// Данное поведение можно сменить в stm32_f20x_f21x_conf.h, NO_REINIT_PORT_AFTER_LOOKING.
	E_ANSWER_GP		reinit_all_ports			( void ) const;					// Метод инициализирует в реальном времени все порты ввода-вывода контроллера,
																						// основываясь на переданном во время формирования объекта pin_config массива.
	E_ANSWER_GP				reinit_port					( EC_PORT_NAME port ) const;	// Переинициализирует конкретный порт.
	E_PORT_LOCKED_KEY		get_state_locked_key_port	( EC_PORT_NAME port ) const;	// Узнаем, заблокирован порт или нет.
	E_ANSWER_PORT_SET_LOCK	set_locked_key_port			( EC_PORT_NAME port ) const;	// Блокируем порт в соответствии с конфигурацией.
	E_ANSWER_PORT_SET_LOCK	set_locked_keys_all_port	( void ) const; 				// Блокируем все порты в соответствии с конфигурацией.

private:
	const global_port_msk_reg_struct	gb_msk_struct;						// Маски регистров всех портов.
				void 						write_image_port_in_registrs	( uint32_t number ) const;		// Служебный метод: записывает образ начальной инициализации в регистры порта.
	constexpr	uint32_t					moder_reg_reset_init_msk_get	( EC_PORT_NAME port_name );
	constexpr	uint32_t					reg_moder_init_msk				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
	constexpr	uint32_t					reg_otyper_init_msk				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
	constexpr	uint32_t					speed_reg_reset_init_msk_get	( EC_PORT_NAME port_name );
	constexpr	uint32_t					reg_speed_init_msk				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
	constexpr	uint32_t					pupd_reg_reset_init_msk_get		( EC_PORT_NAME port_name );
	constexpr	uint32_t					reg_pupd_init_msk				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
	constexpr	uint32_t					reg_lck_init_msk				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
	constexpr	uint32_t					reg_afl_init_msk				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
	constexpr	uint32_t					reg_afh_msk_init_get			( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
	constexpr	uint32_t					reg_od_msk_init_get			( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
	constexpr 	global_port_msk_reg_struct	fill_out_mas_struct				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count );
	constexpr	port_registers_flash_copy_struct fill_out_one_port_struct( EC_PORT_NAME p_name, const pin_config_t *const pin_cfg_array, const uint32_t pin_count );

};
#include "stm32_f20x_f21x_port_constexpr_func_class_global_port.h"

#endif
#endif
