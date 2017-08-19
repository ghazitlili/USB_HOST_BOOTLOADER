/*
 * CRC_32.h
 *
 *  Created on: Aug 16, 2017
 *      Author: root
 */
#include "stm32f4xx_crc.h"
#include "stm32f4xx_rcc.h"

#ifndef CRC_32_H_
#define CRC_32_H_

uint32_t calcCrc32(uint32_t* data, uint32_t len);
uint8_t Compare_CRC(uint32_t* crc_computed,uint32_t* crc_file);
#endif /* CRC_32_H_ */
