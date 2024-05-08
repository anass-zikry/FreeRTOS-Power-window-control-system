#include "TM4C123GH6PM.h"
#include <FreeRTOS.h>
#include <task.h>
#include "DIO.h"

int watchup=9;
int watchdown=8;

void init_motor(void){
	
	
	//enable port F for the bush buttons for the up and down 
	 SYSCTL->RCGCGPIO |= 0x20;   /* enable clock to GPIOF */
	 while((SYSCTL->PRGPIO&0x00000020) == 0){}
   GPIOF->LOCK = 0x4C4F434B;   // unlockGPIOCR register
   GPIOF->CR = 0x01;           // Enable GPIOPUR register enable to commit
   GPIOF->PUR |= 0x11;        // Enable Pull Up resistor PF4//10001
   GPIOF->DIR |= 0x00;          //set PF0 as an output and PF4 as an input pin//01110
   GPIOF->DEN |= 0x11;         // Enable PF0 and PF4 as a digital GPIO pins 
		 
		 
	//enable port A for output signal
	 SYSCTL->RCGCGPIO |= 0x01;   /* enable clock to GPIOA */
	 while((SYSCTL->PRGPIO&0x00000001) == 0){}
   GPIOA->LOCK = 0x4C4F434B;   // unlockGPIOCR register
 //  GPIOA->CR = 0xB4;           // Enable GPIOPUR register enable to commit		84218421
	 GPIOA->PUR |= 0x84; 					//																						10000100
	 GPIOA->DIR |= 0x70;		 //set PA4 and PA5 as output  and PA2 and PA7 as an input 01110000                 
   GPIOA->DEN |= 0xF4;         // Enable PA4 and PA5 as a digital GPIO pins              1111 0100
	 GPIOA->DATA  =0;   
		GPIOA->DATA |=1<<6;     		 //set pA6(PWM)to 1
		//left btn fifth bit
		//right btn first bit
	  //PA6 motor pwm
		 
		 
		 //enable port B
		 //	pin4 -> lock switch
	 SYSCTL->RCGCGPIO |= 0x02;   /* enable clock to GPIOA */
	 while((SYSCTL->PRGPIO&0x00000002) == 0){}
   GPIOB->LOCK = 0x4C4F434B;   // unlockGPIOCR register

	 GPIOB->PUR |= 0x10; 					//						00010000																10000100
	 GPIOB->DIR |= 0x00;		 //set PA4 as INPUT                 
   GPIOB->DEN |= 0x10;         // Enable PA4 and PA5 as a digital GPIO pins              1111 0100
	 GPIOB->DATA  =0;   
   

}
int check_motor_up(){
	
	return ((GPIOF->DATA & 0x10)==0);
}

int check_motor_down(){

	return ((GPIOF->DATA & 0x01)==0);
}

void auto_motor_up(void){
	GPIOA->DATA |=0x10; 
	DIO_ledRedOn();
}

void auto_motor_down(void){
	GPIOA->DATA |=0x20; 
	DIO_ledBlueOn();
	
}

//left is up 
//set PA4 to 1  ,PA2 as input for up
void manual_motor_up(void){
		watchup=GPIOA->DATA& 0x04;
		if(((GPIOF->DATA & 0x10)==0)||((GPIOA->DATA& 0x04)==0))
		{
	
		GPIOA->DATA |=0x10; 
		DIO_ledRedOn();
		
		}
		else{
			GPIOA->DATA &=~0x10; 
			DIO_ledRedOff();
		}

}


	
//right is down  
//set PA5 to 1   PA7 as down
void manual_motor_down(void){
	watchdown=GPIOA->DATA & 0x80;
	if(((GPIOF->DATA & 0x01)==0)||((GPIOA->DATA & 0x80)==0))
		//if((GPIOF->DATA & 0x01)==0)
	
	{


		
		GPIOA->DATA |=0x20; 
  	 DIO_ledBlueOn();
	
		
	}
	else{
		 GPIOA->DATA &=~0x20; 
			DIO_ledBlueOff();
		
	}


}
	


void start_up(void){
GPIOA->DATA |=0x10; 
		DIO_ledRedOn();
}
void stop_up(void){
GPIOA->DATA &=~0x10; 
			DIO_ledRedOff();
}
void start_down(void){
	GPIOA->DATA |=0x20; 
  	 DIO_ledBlueOn();
}
void stop_down(void){
	GPIOA->DATA &=~0x20; 
			DIO_ledBlueOff();
}

void lock_switch(){
	if ((GPIOB->DATA & 0x10)==0){
		DIO_ledGreenOn();
		GPIOA->DATA &=~ 0x40; 
		  
		
}
	if ((GPIOB->DATA & 0x10)!=0){
	DIO_ledGreenOff();	  
  GPIOA->DATA |=1<<6; 
}
	
}
