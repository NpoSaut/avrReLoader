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

//	sei();
	ledInit();
	ledDown(1);
	ledUp(0);

    for (uint8_t i = 0; i < 50; i++)
    {
    	_delay_ms (100);
    	wdt_reset();
    }

    ledToggle(0);
    ledToggle(1);

    resetInit();
    resetSet(true);

    for (uint8_t i = 0; i < 100; i++)
    {
    	_delay_ms(100);
    	wdt_reset();
    }

    resetSet(false);
    ledUp(0);
    ledUp(1);

    for (;;)
    {
    	wdt_reset();
    }
}
