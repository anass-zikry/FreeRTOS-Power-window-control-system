#include "DIO.h"

#include "TM4C123GH6PM.h"

void DIO_Init(void){
  SYSCTL->RCGCGPIO  |= 0x20;
  while((SYSCTL->PRGPIO & 0x00000020) == 0){}
  GPIOF->LOCK = 0x4C4F434B;
  GPIOF->DIR |= (LED_RED | LED_BLUE | LED_GREEN );
  GPIOF->DEN |= (LED_RED | LED_BLUE | LED_GREEN );
}

void DIO_ledRedOn(void) {
    GPIOF->DATA |= LED_RED;
}

void DIO_ledRedOff(void) {
   GPIOF->DATA &=~  LED_RED;
}

void DIO_ledBlueOn(void) {
    GPIOF->DATA |= LED_BLUE;
}

void DIO_ledBlueOff(void) {
     GPIOF->DATA &=~ LED_BLUE;
}
void DIO_ledGreenOn(void) {
    GPIOF->DATA |= LED_GREEN;
}

void DIO_ledGreenOff(void) {
     GPIOF->DATA &=~ LED_GREEN;
}
void DIO_toggleRED(void) {
     GPIOF->DATA ^= LED_RED;
}

void DIO_toggleBLUE(void){
	 GPIOF->DATA ^= LED_BLUE;
}

void DIO_toggleGREEN(void){
	 GPIOF->DATA ^= LED_GREEN;
	
}

