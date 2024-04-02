#pragma once

#include_next <mcuconf.h>

#undef RP_SPI_USE_SPI1
#define RP_SPI_USE_SPI1 TRUE


#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2 TRUE
#define STM32_I2C_BUSY_TIMEOUT 100  //50
