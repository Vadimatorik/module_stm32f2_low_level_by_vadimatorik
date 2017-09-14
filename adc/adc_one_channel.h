#pragma once

#include "f2_api_conf.h"

#include "adc_struct.h"
#include "mk_hardware_interfaces_adc.h"

template < ADC::CFG::NAME           ADCx,
           uint8_t                  CH,
           ADC::CFG::RES            RES,
           ADC::CFG::SAMPLING_TIME  ST >
class adc_one_channel : public adc_one_channel_base {
public:
    constexpr adc_one_channel () {}
    void                reinit                          ( void ) const;
    void                on                              ( void ) const;
    void                off                             ( void ) const;
    void                start_continuous_conversion     ( void ) const;
    SPI::FUNC_RESULT    get_measurement                 ( uint32_t& channel_measurement ) const;
};

#include "adc_one_channel_func.h"
