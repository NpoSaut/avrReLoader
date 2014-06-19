/*
 * main.cpp
 *
 *  avrReLoader -- программа для обновления загрузчика AVR
 *  ******************************************************
 *
 *  Обновляет загрузчик соседнего полукомплекта, подключенного по SPI
 */

#include <avr/eeprom.h>
#include <cpp/io.h>
#include <cpp/universal.h>
#include <cpp/timers.h>
#include <util/delay.h>

#include "hard.h"
#include "firmware.h"

// DEBUG ONLY
#include "cpp/can-dat.h"
typedef CanDat < INT_TYPELIST_2(0x1888, 0x1A88),
				 INT_TYPELIST_2(0x0A08, 0x0B08),
				 NullType,
					128,
					NullType,
				 100 >									// BaudRate = 100 Кбит, SamplePoint = 75% (по умолчанию)
	CanDatType;
CanDatType canDat;

void Init (void) __attribute__ ((naked)) __attribute__ ((section (".init5")));
void Init (void)
{
	// Светодиоды.
//	reg.portD.pin7.out();
//	reg.portD.pin7 = true;
//	configSelfComplectPin();
//	lconfig();

	// Watchdog
	wdt_enable (WDTO_500MS);

	// Кнопка сброса
//	reg.portB.pin5.in();
}

int main ()
{
	asm volatile ("nop"); // !!! 126 version hack !!!

	sei();
	ledInit();
	ledDown(1);
	ledUp(0);

	Complex<uint32_t> start, stop;
	start = pgm_read_dword(&firmwareInfo.startAddr);
	stop = pgm_read_dword(&firmwareInfo.endAddr);

	uint8_t test[8] = {
			start[3],
			start[2],
			start[1],
			start[0],
			stop[3],
			stop[2],
			stop[1],
			stop[0]
	};
	canDat.send<0x1888> (test);

    for (;;)
    {
    	wdt_reset();
    }
}
