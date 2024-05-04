#ifndef jamProtection_H
#include <FreeRTOS.h>
#include "semphr.h"


extern SemaphoreHandle_t xJamProtectionSemaphore;

#endif
//port b pin0 for jam protection
#define jamProtectionPin (1<<0)
#define GPIOB_IRQn 1
void jamProtectionInit();
void moveWindowDown();
void vJamProtectionInterruptTask(void *pvParameters);