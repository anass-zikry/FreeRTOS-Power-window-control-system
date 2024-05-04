#include <stdint.h>
#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include "limitSwitch.h"
#include "jamProtection.h"
#include "motor.h"
#include "DIO.h"

/*
Port Pins Map
	Port B:
		pin0 -> jam protection
		pin1 -> limit switch up
		pin2 -> limit switch down
		pin4 -> lock switch
	Port F:
		pin0 -> button
		pin5 -> button
	Port A:
		pin2 -> input to up
		pin7 -> input to down
		pin4 -> output1 motor
		pin5 -> output2 motor
		pin6 -> motor pwm
*/

void intit_task(void *pvParameters)
{
	init_motor();
	DIO_Init();
	vTaskDelete(NULL);
	
	
}	
void motor_up(void *pvParameters)
{
for(;;){
	 if(check_motor_up()){
		vTaskDelay(250/portTICK_RATE_MS);
			if(check_motor_up()){
				start_motor_up();
				taskYIELD();
				stop_motor_up();
				taskYIELD();
			}
			
	 else{
		 while(1){
		 auto_motor_up();
		 }
	}
		
	}

}
}	
void motor_down(void *pvParameters)
{
 for(;;){
	 if(check_motor_down()){
		vTaskDelay(250/portTICK_RATE_MS);
			if(check_motor_down()){
				start_motor_down();
				taskYIELD();
				stop_motor_down();
				taskYIELD();
			}
			
	 else{
		 while(1){
		 auto_motor_down();
		 }
	 }
	
	 }
}	
 }
int main()
{

	/*BaseType_t xTaskCreate( TaskFunction_t pxTaskCode,
                            const char * const pcName,
                            const configSTACK_DEPTH_TYPE usStackDepth,
                            void * const pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t * const pxCreatedTask );*/
 xTaskCreate( intit_task, "intit_task",140,0,3,0 );
	 xTaskCreate( motor_up, "motor_up",140,0,2,0 );
	 xTaskCreate( motor_down, "motor_down",140,0,2,0 );
	// Startup of the FreeRTOS scheduler.  The program should block here.  
	vTaskStartScheduler();
	
	// The following line should never be reached.  
	//Failure to allocate enough memory from the heap could be a reason.
	for (;;);
	
}



void GPIOB_Handler(void) {
    // Check if the interrupt was triggered by which pin
		if (GPIOB->RIS & jamProtectionPin ) {
        // Clear the interrupt flag for pin
        GPIOB->ICR |= jamProtectionPin;

        // Give the semaphore to signal the ISR completion
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(xJamProtectionSemaphore, &xHigherPriorityTaskWoken);

        // Perform any other necessary actions here
    }
    else if (GPIOB->RIS & limitSwitchUpPin) {
        // Clear the interrupt flag for pin
        GPIOB->ICR |= limitSwitchUpPin;

        // Give the semaphore to signal the ISR completion
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(xLimitSwitchSemaphore, &xHigherPriorityTaskWoken);

        // Perform any other necessary actions here
    }
		else if (GPIOB->RIS & limitSwitchDownPin) {
        // Clear the interrupt flag for pin
        GPIOB->ICR |= limitSwitchDownPin;

        // Give the semaphore to signal the ISR completion
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(xLimitSwitchSemaphore, &xHigherPriorityTaskWoken);

        // Perform any other necessary actions here
    }
		
}

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06



