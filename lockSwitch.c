#include "lockSwitch.h"


//SemaphoreHandle_t xLockSwitchSemaphore = NULL;


void lockSwitchInit(){
	//enable clock for port b
	SYSCTL->RCGCGPIO |= (1<<1);
	while(SYSCTL->RCGCGPIO &= (1<<1)==0){}
		 // Set PB4 as inputs
    GPIOB->DIR &= ~lockSwitchPin;  // Set PB4 as inputs
		//xLockSwitchSemaphore = xSemaphoreCreateBinary();
    // Enable digital functionality on PB1 and PB2
    GPIOB->DEN |= lockSwitchPin;  // Enable digital functionality on PB4
		//GPIOB->IS &= ~lockSwitchPin;    // Set PB4 as edge-sensitive
    //GPIOB->IBE &= ~lockSwitchPin;   // Set PB4 as triggering on a single edge
    //GPIOB->IEV |= lockSwitchPin;   // Set PB4 to trigger on the rising edge
    //GPIOB->IM |= lockSwitchPin;     // Enable interrupt for PB4
		//NVIC_SetPriority(GPIOB_IRQn, 3);
		//NVIC_EnableIRQ(GPIOB_IRQn);

}

uint8_t getLockSwitchState(){
	return (GPIOB->DATA & lockSwitchPin);
}