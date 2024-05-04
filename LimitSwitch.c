#include "limitSwitch.h"


SemaphoreHandle_t xLimitSwitchSemaphore = NULL;

void LimitSwitchInit(){
	//enable clock for port b
	SYSCTL->RCGCGPIO |= (1<<1);
	while(SYSCTL->RCGCGPIO &= (1<<1)==0){}
		 // Set PB1 and PB2 as inputs
    GPIOB->DIR &= ~(limitSwitchUpPin | limitSwitchDownPin);  // Set PB1 and PB2 as inputs
		xLimitSwitchSemaphore = xSemaphoreCreateBinary();
    // Enable digital functionality on PB1 and PB2
    GPIOB->DEN |= limitSwitchUpPin | limitSwitchDownPin;  // Enable digital functionality on PB1 and PB2
		GPIOB->IS &= ~limitSwitchUpPin | ~limitSwitchDownPin;    // Set PB1 as edge-sensitive
    GPIOB->IBE &= ~limitSwitchUpPin | ~limitSwitchDownPin;   // Set PB1 as triggering on a single edge
    GPIOB->IEV |= limitSwitchUpPin | limitSwitchDownPin;   // Set PB1 to trigger on the rising edge
    GPIOB->IM |= limitSwitchUpPin | limitSwitchDownPin;     // Enable interrupt for PB1
		NVIC_SetPriority(GPIOB_IRQn, 3);
		NVIC_EnableIRQ(GPIOB_IRQn);
}
void vLimitSwitchInterruptTask(void *pvParameters){
	
	xSemaphoreTake(xLimitSwitchSemaphore, portMAX_DELAY);
	//Stop Motor

}

/*
void GPIOB_Handler(void) {
    // Check if the interrupt was triggered by pin 1
    if (GPIOB->RIS & limitSwitchUpPin) {
        // Clear the interrupt flag for pin 1
        GPIOB->ICR |= limitSwitchUpPin;

        // Give the semaphore to signal the ISR completion
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(xLimitSwitchSemaphore, &xHigherPriorityTaskWoken);

        // Perform any other necessary actions here
    }
		else if (GPIOB->RIS & limitSwitchDownPin) {
        // Clear the interrupt flag for pin 1
        GPIOB->ICR |= limitSwitchDownPin;

        // Give the semaphore to signal the ISR completion
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(xLimitSwitchSemaphore, &xHigherPriorityTaskWoken);

        // Perform any other necessary actions here
    }
}
*/
