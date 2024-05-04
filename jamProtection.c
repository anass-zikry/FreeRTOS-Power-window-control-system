#include "jamProtection.h"
#include "motor.h"

SemaphoreHandle_t xJamProtectionSemaphore = NULL;

void jamProtectionInit(){
	//enable clock for port b
	SYSCTL->RCGCGPIO |= (1<<1);
	while(SYSCTL->PRGPIO &= (1<<1)==0){}
		 // Set PB1 and PB2 as inputs
		GPIOB->LOCK=0x4C4F434B;
		GPIOB->AMSEL= 0x00;
		GPIOB->PCTL = 0x00000000;
		GPIOB->PUR |= jamProtectionPin;
   GPIOB->DIR &= ~jamProtectionPin;  // Set PB0 as inputs
		GPIOB->AFSEL = 0x00;
		
    // Enable digital functionality on PB0
    GPIOB->DEN |= jamProtectionPin;  // Enable digital functionality on PB0
		GPIOB->IM |= jamProtectionPin;
		GPIOB->IS &= ~jamProtectionPin;    // Set PB1 as edge-sensitive
    GPIOB->IBE &= ~jamProtectionPin;   // Set PB1 as triggering on a single edge
    GPIOB->IEV |= jamProtectionPin;   // Set PB1 to trigger on the rising edge
         // Enable interrupt for PB0
		NVIC_SetPriority(GPIOB_IRQn, 5);
		NVIC_EnableIRQ(GPIOB_IRQn);
__ASM("CPSIE i");
//xJamProtectionSemaphore = xSemaphoreCreateBinary();
		vSemaphoreCreateBinary(xJamProtectionSemaphore);
		xSemaphoreCreateBinary();
}

void vJamProtectionInterruptTask(void *pvParameters){
	//xSemaphoreTake(xJamProtectionSemaphore,0);
	while(1){
	xSemaphoreTake(xJamProtectionSemaphore, portMAX_DELAY);
	start_down();
		vTaskDelay(5000/portTICK_RATE_MS);
		stop_down();
	}
}

/*void moveWindowDown(){
	//motor down direction call and delay for 0.5 second then stop motor
	start_motor_down();
	
}*/