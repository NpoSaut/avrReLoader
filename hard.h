/*
 * hard.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: nazemnyh
 */

#ifndef HARD_H_
#define HARD_H_

#include <cpp/io.h>

void ledInit ()
{
	reg.portC.pin4.out ();
	reg.portC.pin5.out ();
}

void ledUp (uint8_t n)
{
	if (n == 0)
		reg.portC.pin4 = false;
	if (n == 1)
		reg.portC.pin5 = false;
}

void ledDown (uint8_t n)
{
	if (n == 0)
		reg.portC.pin4 = true;
	if (n == 1)
		reg.portC.pin5 = true;
}

void ledToggle (uint8_t n)
{
	if (n == 0)
		reg.portC.pin4.toggle();
	if (n == 1)
		reg.portC.pin5.toggle();
}

void resetInit (void) __attribute__ ((section (".unsafe")));
void resetInit ()
{
	reg.portB.pin4.out();
}

void resetSet (bool p) __attribute__ ((section (".unsafe")));
void resetSet (bool p)
{
	reg.portB.pin4 = p;
}



#endif /* HARD_H_ */
