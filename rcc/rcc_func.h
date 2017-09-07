#pragma once

#include "f2_api_conf.h"

#ifdef MODULE_RCC

#include "rcc.h"
#include "port.h"
#include <cmath>

/**********************************************************************
 * Область constexpr конструкторов.
 **********************************************************************/

constexpr rcc::rcc( const rcc_cfg* const cfg ):
    cfg( cfg ) {};

#endif
