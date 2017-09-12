#pragma once

#include "f2_api_conf.h"

#ifdef MODULE_ADC
#include "mk_hardware_interfaces_adc.h"
#include "adc_struct.h"

#define ADC_ONE_CHANNEL_CFG_TEMPLATE_HEADING            ADC::CFG::NAME           ADCx,  \
                                                        uint8_t                  CH,    \
                                                        ADC::CFG::RES            RES,   \
                                                        ADC::CFG::SAMPLING_TIME  ST

#define ADC_ONE_CHANNEL_CFG_TEMPLATE_PARAM              ADCx, CH, RES, ST

template < ADC_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void adc_one_channel< ADC_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::reinit ( void ) const {
    ADC::R_STRUCT* A = ( ADC::R_STRUCT* )ADCx;
    A->C2 = 0;
    A->C1 = ( ( uint8_t )RES << M_EC_TO_U32( ADC::C1_R_BF_POS::RES ) ) |
                                M_EC_TO_U32( ADC::C1_R_BF_MSK::DISCEN );
    A->SMP[0] = ( ( uint8_t )CH > 9 ) ? ( uint8_t )ST << 3 * ( ( uint8_t )CH - 10 ) : 0;
    A->SMP[1] = ( ( uint8_t )CH < 10 ) ? ( uint8_t )ST << 3 * ( uint8_t )CH  : 0;
    A->SQ[0] = 0;
    A->SQ[3] = ( uint8_t )CH;
}

template < ADC_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void adc_one_channel< ADC_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::on ( void ) const {
    ADC::R_STRUCT* A = ( ADC::R_STRUCT* )ADCx;
    A->C2 |= M_EC_TO_U32( ADC::C2_R_BF_MSK::ADON );
}

template < ADC_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void adc_one_channel< ADC_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::off ( void ) const {
    ADC::R_STRUCT* A = ( ADC::R_STRUCT* )ADCx;
    A->C2 &= ~M_EC_TO_U32( ADC::C2_R_BF_MSK::ADON );
}

template < ADC_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void adc_one_channel< ADC_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::start_measurement ( void ) const {
    ADC::R_STRUCT* A = ( ADC::R_STRUCT* )ADCx;
    A->C2 |= M_EC_TO_U32( ADC::C2_R_BF_MSK::SWSTART );
}

template < ADC_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
SPI::FUNC_RESULT adc_one_channel< ADC_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::get_measurement ( uint32_t& channel_measurement ) const {
    ADC::R_STRUCT* A = ( ADC::R_STRUCT* )ADCx;
    if ( A->S & M_EC_TO_U32( ADC::S_R_BF_MSK::EOC ) ) {
        channel_measurement = A->D;     // S сбросится сам в момент считывания.
        return SPI::FUNC_RESULT::OK;
    } else {
        return SPI::FUNC_RESULT::MEASUREMENT_IS_MISSING;
    }
}

#endif


