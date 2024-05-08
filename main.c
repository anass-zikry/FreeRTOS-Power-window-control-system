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
uint8_t flag=0x99;
void GPIOB_Handler(void);
void intit_task(void *pvParameters)
{
	init_motor();
	DIO_Init();
	jamProtectionInit();
	vTaskDelete(NULL);
	
	
}	
void motor_up(void *pvParameters)
{
	
	/*for(;;){
		manual_motor_up();
	}*/
	uint8_t upManualFlag=0;
	for(;;){
		if(check_motor_up()){
			if(xSemaphoreTake(xMotorMutex,0)==pdPASS){
				xSemaphoreGive(xMotorMutex);}
			else continue;
			if(upManualFlag)continue;
			
			vTaskDelay(250/portTICK_RATE_MS);
			if(check_motor_up()){
				upManualFlag=1;
				start_up();
				
				//manual_motor_up();
				//while(1){manual_motor_up();}
				//taskYIELD();
			}
			else if(!upManualFlag){
				while(1){auto_motor_up();}
			}
		
		}
		else if(upManualFlag){
			upManualFlag=0;
			stop_up();
		//manual_motor_up();
		}

	
}
}	
void motor_down(void *pvParameters)
{
	 /*for(;;){
		manual_motor_down();
	}
	*/
	uint8_t downManualFlag=0;
	for(;;){
		
		if(check_motor_down()){
			if(xSemaphoreTake(xMotorMutex,0)==pdPASS){
			xSemaphoreGive(xMotorMutex);
			}else continue;
			if(downManualFlag)continue;
		vTaskDelay(250/portTICK_RATE_MS);
		if(check_motor_down()){
			downManualFlag=1;
			start_down();
			//manual_motor_down();
			//while(!check_motor_down()){}
		}
		else if(!downManualFlag){
		 while(1){auto_motor_down();}
	  }
	
	  }
		else if(downManualFlag){
			downManualFlag=0;
			stop_down();
			
		//manual_motor_down();
		}
  
}
 }

 void lock_switch_check(void *pvParameters)
	 
{
	for(;;){
		lock_switch();
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
 xTaskCreate( intit_task, "intit_task",40,0,5,0 );
	 xTaskCreate( motor_up, "motor_up",40,0,2,0 );
	 xTaskCreate( motor_down, "motor_down",40,0,2,0 );
	xTaskCreate(vJamProtectionInterruptTask,"jam_protection_interrupt_task",140,0,3,0);
	xTaskCreate(lock_switch_check,"lock_switch_check",40,0,2,0);
	// Startup of the FreeRTOS scheduler.  The program should block here.  
	vTaskStartScheduler();
	
	// The following line should never be reached.  
	//Failure to allocate enough memory from the heap could be a reason.
	for (;;);
	
}



void GPIOB_Handler(void) {
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
		
    // Check if the interrupt was triggered by which pin
		if ((GPIOB->RIS & jamProtectionPin) ==1) {
        // Clear the interrupt flag for pin
        GPIOB->ICR |= jamProtectionPin;

        // Give the semaphore to signal the ISR completion
        xSemaphoreGiveFromISR(xJamProtectionSemaphore, &xHigherPriorityTaskWoken);

        // Perform any other necessary actions here
    }
     if (GPIOB->RIS & limitSwitchUpPin) {
        // Clear the interrupt flag for pin
        GPIOB->ICR |= limitSwitchUpPin;

        // Give the semaphore to signal the ISR completion
        xSemaphoreGiveFromISR(xLimitSwitchSemaphore, &xHigherPriorityTaskWoken);

        // Perform any other necessary actions here
    }
		 if (GPIOB->RIS & limitSwitchDownPin) {
        // Clear the interrupt flag for pin
        GPIOB->ICR |= limitSwitchDownPin;

        // Give the semaphore to signal the ISR completion
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



