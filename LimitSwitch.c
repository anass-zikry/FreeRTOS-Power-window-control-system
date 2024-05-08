#include "limitSwitch.h"

                                                                                                              
SemaphoreHandle_t xLimitSwitchSemaphore = NULL;
QueueHandle_t xQueue;
void LimitSwitchInit(){
	//enable clock for port b
	SYSCTL->RCGCGPIO |= (1<<1);
	while(SYSCTL->PRGPIO &= (1<<1)==0){}
		GPIOB->LOCK=0x4C4F434B;
		GPIOB->AMSEL= 0x00;
		GPIOB->PCTL = 0x00000000;
		GPIOB->PUR |= (limitSwitchUpPin | limitSwitchDownPin);
		 // Set PB1 and PB2 as inputs
    GPIOB->DIR &= ~(limitSwitchUpPin | limitSwitchDownPin);  // Set PB1 and PB2 as inputs
		GPIOB->AFSEL = 0x00;
		
    // Enable digital functionality on PB1 and PB2
    GPIOB->DEN |= limitSwitchUpPin | limitSwitchDownPin;  // Enable digital functionality on PB1 and PB2
		GPIOB->IM |= limitSwitchUpPin | limitSwitchDownPin;     // Enable interrupt for PB1
		GPIOB->IS &= ~limitSwitchUpPin | ~limitSwitchDownPin;    // Set PB1 as edge-sensitive
    GPIOB->IBE &= ~limitSwitchUpPin | ~limitSwitchDownPin;   // Set PB1 as triggering on a single edge
    GPIOB->IEV |= limitSwitchUpPin | limitSwitchDownPin;   // Set PB1 to trigger on the rising edge
    
		NVIC_SetPriority(GPIOB_IRQn, 5);
		NVIC_EnableIRQ(GPIOB_IRQn);
		__ASM("CPSIE i");
		vSemaphoreCreateBinary(xLimitSwitchSemaphore);
		xSemaphoreCreateBinary();
		xQueue = xQueueCreate(2, sizeof(int));
}
void vLimitSwitchInterruptTask(void){
	while(1){
	xSemaphoreTake(xLimitSwitchSemaphore, portMAX_DELAY);
	//Stop Motor
		if((GPIOB->DATA & limitSwitchUpPin)==0){
			//up limit switch triggered
			//flagLimit=1;
			//xQueueSendToBack( xQueue, &flagLimit, 10 );
		}
		else if((GPIOB->DATA & limitSwitchDownPin)==0){
			//down limit switch triggered
			//flagLimit=2;
			//xQueueSendToBack( xQueue, &flagLimit, 10 );
		}
	}
	

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
