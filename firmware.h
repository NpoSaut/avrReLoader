/*
 * firmware.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: nazemnyh
 */

#ifndef FIRMWARE_H_
#define FIRMWARE_H_

#include <avr/pgmspace.h>

struct FirmwareInfo
{
	uint32_t startAddr;
	uint32_t endAddr;
	uint8_t fuseLow;
	uint8_t fuseHigh;
	uint8_t fuseEx;
};
FirmwareInfo firmwareInfo __attribute__ ((section (".fm_inf")));

uint8_t firmwareCode [8192] __attribute__ ((section (".fm_code")));


#endif /* FIRMWARE_H_ */
