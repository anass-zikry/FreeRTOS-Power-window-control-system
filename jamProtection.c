#include "jamProtection.h"

SemaphoreHandle_t xJamProtectionSemaphore = NULL;

void jamProtectionInit(){
	//enable clock for port b
	SYSCTL->RCGCGPIO |= (1<<1);
	while(SYSCTL->RCGCGPIO &= (1<<1)==0){}
		 // Set PB1 and PB2 as inputs
    GPIOB->DIR &= ~jamProtectionPin;  // Set PB0 as inputs
		xJamProtectionSemaphore = xSemaphoreCreateBinary();
    // Enable digital functionality on PB0
    GPIOB->DEN |= jamProtectionPin;  // Enable digital functionality on PB0
		GPIOB->IS &= ~jamProtectionPin;    // Set PB1 as edge-sensitive
    GPIOB->IBE &= ~jamProtectionPin;   // Set PB1 as triggering on a single edge
    GPIOB->IEV |= jamProtectionPin;   // Set PB1 to trigger on the rising edge
    GPIOB->IM |= jamProtectionPin;     // Enable interrupt for PB0
		NVIC_SetPriority(GPIOB_IRQn, 3);
		NVIC_EnableIRQ(GPIOB_IRQn);


}

void vJamProtectionInterruptTask(void *pvParameters){
	xSemaphoreTake(xJamProtectionSemaphore, portMAX_DELAY);
	moveWindowDown();
}

void moveWindowDown(){
	//motor down direction call and delay for 0.5 second then stop motor
}