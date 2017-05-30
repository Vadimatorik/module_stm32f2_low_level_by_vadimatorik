#ifndef STM32F2_API_PORT_STM32_F20X_F21X_PORT_CONSTEXPR_FUNC_CLASS_GLOBAL_PORT_H_
#define STM32F2_API_PORT_STM32_F20X_F21X_PORT_CONSTEXPR_FUNC_CLASS_GLOBAL_PORT_H_

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

#include "stm32_f20x_f21x_port_struct_class_global_port.h"
#include "stm32_f20x_f21x_port_struct.h"

/*
 * Конструктор готовит маски для начальной инициализации выводов.
 * Количество портов, а так же их имена задаются автоматически после выбора чипа в stm32_f20x_f21x_conf.h.
 */
/*****************************************************************************************************
 * Необходимые для конструктора global_port constexpr функции (готовят маски из массива структур).
 * Методы проверяет все pin_config структуры и в случае, если структура относится к port_name порту,
 * на основе ее конфигурации производится изменение маски регистра порта.
 *****************************************************************************************************/
constexpr uint32_t global_port::moder_reg_reset_init_msk_get( EC_PORT_NAME port_name ) {
	switch(M_EC_TO_U8(port_name)){
		case M_EC_TO_U8(EC_PORT_NAME::A):	return 0xA8000000;
		case M_EC_TO_U8(EC_PORT_NAME::B):	return 0x00000280;
		default: 		return 0;
	};
}

// Режим работы.
constexpr uint32_t global_port::reg_moder_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name ) {
	uint32_t reg_moder = this->moder_reg_reset_init_msk_get(port_name);								// Начальное значение зависит от порта.
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){								// Проходимся по всем структурам.
		if (pin_cfg_array[loop_pin].port != port_name) { continue; };							// Если вывод не относится к нашему порту - выходим.
		reg_moder &= ~(0b11 << (M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name) * 2));							// Сбрасываем предыдущую настройку этого вывода.
		reg_moder |= M_EC_TO_U8(pin_cfg_array[loop_pin].mode) << (M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name) * 2);		// Иначе производим добавление по маске.
	}
	return reg_moder;
}

// Режим выхода.
constexpr uint32_t global_port::reg_otyper_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name ) {
	uint32_t reg_otyper = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name) { continue; };
		reg_otyper &= ~(1 << M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name));
		reg_otyper |= M_EC_TO_U8(pin_cfg_array[loop_pin].output_config) <<
				M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name);
	}
	return reg_otyper;
}


constexpr uint32_t global_port::speed_reg_reset_init_msk_get( EC_PORT_NAME port_name ) {
	switch(M_EC_TO_U8(port_name)){
		case M_EC_TO_U8(EC_PORT_NAME::B):	return 0x000000C0;
		default: 		return 0;
	};
}

// Скорость.
constexpr uint32_t global_port::reg_speed_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name ) {
	uint32_t reg_ospeeder = this->speed_reg_reset_init_msk_get(port_name);
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		reg_ospeeder &= ~(0b11 << M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name) * 2);
		reg_ospeeder |= M_EC_TO_U8(pin_cfg_array[loop_pin].speed) <<
				(M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name) * 2);
	}
	return reg_ospeeder;
}

constexpr uint32_t global_port::pupd_reg_reset_init_msk_get( EC_PORT_NAME port_name ) {
	switch(M_EC_TO_U8(port_name)){
		case M_EC_TO_U8(EC_PORT_NAME::A):	return 0x64000000;
		case M_EC_TO_U8(EC_PORT_NAME::B):	return 0x00000100;
		default: 		return 0;
	};
}
// Подтяжка.
constexpr uint32_t global_port::reg_pupd_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name ) {
	uint32_t reg_pupdr = this->pupd_reg_reset_init_msk_get(port_name);
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		reg_pupdr &= ~(0b11 << M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name * 2));
		reg_pupdr |= M_EC_TO_U8(pin_cfg_array[loop_pin].pull) << (M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name) * 2);
	}
	return reg_pupdr;
}

// Блокировка настроек.
constexpr uint32_t global_port::reg_lck_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name ) {
	uint32_t reg_lckr = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		reg_lckr &= ~(1 << M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name));
		reg_lckr |= M_EC_TO_U8(pin_cfg_array[loop_pin].locked) <<
				M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name);
	}
	return reg_lckr;
}

// Младший регистр выбора альтернативной функции.
constexpr uint32_t global_port::reg_afl_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name ) {
	uint32_t reg_afrl = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		if (pin_cfg_array[loop_pin].pin_name < EC_PORT_PIN_NAME::PIN_8) {
			reg_afrl &= ~(0b1111 << M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name) * 4);
			reg_afrl |= M_EC_TO_U8(pin_cfg_array[loop_pin].locked) <<
					(M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name) * 4);
		}
	}
	return reg_afrl;
}

// Старший регистр выбора альтернативной функции.
constexpr uint32_t global_port::reg_afh_msk_init_get( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name ) {
	uint32_t reg_afrh = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++) {
		if (pin_cfg_array[loop_pin].port != port_name) { continue; };
		if (pin_cfg_array[loop_pin].pin_name > EC_PORT_PIN_NAME::PIN_7) {
			reg_afrh &= ~(0b1111 << (M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name) - 8) * 4);
			reg_afrh |= M_EC_TO_U8(pin_cfg_array[loop_pin].locked) <<
					((M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name) - 8) * 4);
		}
	}
	return reg_afrh;
}

// Состояние на выводах после инициализации (для выводов, настроенных на выход).
constexpr uint32_t global_port::reg_od_msk_init_get( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name ) {
	uint32_t reg_odr = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		reg_odr &= ~(1 << M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name));
		reg_odr |= M_EC_TO_U8(pin_cfg_array[loop_pin].state_after_init) << M_EC_TO_U8(pin_cfg_array[loop_pin].pin_name);
	}
	return reg_odr;
}

/*
 * Функция заполняет структуру, необходимую для работы с одном портом.
 */
constexpr port_registers_flash_copy_struct global_port::fill_out_one_port_struct( EC_PORT_NAME p_name, const pin_config_t *const pin_cfg_array, const uint32_t pin_count ) {
	port_registers_flash_copy_struct		st_port = {
		.p_port			= p_base_port_address_get				( p_name ),
		.mode			= this->reg_moder_init_msk				( pin_cfg_array, pin_count, p_name ),
		.mode_res		= this->moder_reg_reset_init_msk_get	( p_name ),
		.otype			= this->reg_otyper_init_msk				( pin_cfg_array, pin_count, p_name ),
		.speed			= this->reg_speed_init_msk				( pin_cfg_array, pin_count, p_name ),
		.pupd			= this->reg_pupd_init_msk				( pin_cfg_array, pin_count, p_name ),
		.lck			= this->reg_lck_init_msk				( pin_cfg_array, pin_count, p_name ),
		.afl			= this->reg_afl_init_msk				( pin_cfg_array, pin_count, p_name ),
		.afh			= this->reg_afh_msk_init_get			( pin_cfg_array, pin_count, p_name ),
		.od				= this->reg_od_msk_init_get				( pin_cfg_array, pin_count, p_name ),
		.p_look_key		= bb_p_port_look_key_get				( p_name )
	};
	return st_port;
}

/*
 * Функция заполняет основную структуру объекта.
 */
constexpr global_port_msk_reg_struct global_port::fill_out_mas_struct( const pin_config_t *const pin_cfg_array, const uint32_t pin_count ) {
	global_port_msk_reg_struct	p_st = {
		.port = {
#ifdef PORTA															// Если данный порт есть в чипе.
					this->fill_out_one_port_struct( EC_PORT_NAME::A, pin_cfg_array, pin_count ),
#endif
#ifdef PORTB
					this->fill_out_one_port_struct( EC_PORT_NAME::B, pin_cfg_array, pin_count ),
#endif
#ifdef PORTC
					this->fill_out_one_port_struct( EC_PORT_NAME::C, pin_cfg_array, pin_count ),
#endif
#ifdef PORTD
					this->fill_out_one_port_struct( EC_PORT_NAME::D, pin_cfg_array, pin_count ),
#endif
#ifdef PORTE
					this->fill_out_one_port_struct( EC_PORT_NAME::E, pin_cfg_array, pin_count ),
#endif
#ifdef PORTF
					this->fill_out_one_port_struct( EC_PORT_NAME::F, pin_cfg_array, pin_count ),
#endif
#ifdef PORTG
					this->fill_out_one_port_struct( EC_PORT_NAME::G, pin_cfg_array, pin_count ),
#endif
#ifdef PORTH
					this->fill_out_one_port_struct( EC_PORT_NAME::H, pin_cfg_array, pin_count ),
#endif
#ifdef PORTI
					this->fill_out_one_port_struct( EC_PORT_NAME::I, pin_cfg_array, pin_count )
#endif
		}
	};
	return p_st;
}

constexpr global_port::global_port( const pin_config_t *const pin_cfg_array, const uint32_t pin_count ):
	gb_msk_struct(this->fill_out_mas_struct(pin_cfg_array, pin_count)) {};

#endif
#endif