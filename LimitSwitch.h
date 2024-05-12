#ifndef limitSwitch_H

#include <FreeRTOS.h>
#include "semphr.h"
#include "queue.h"
#include "motor.h"

extern SemaphoreHandle_t xLimitSwitchSemaphore;
extern QueueHandle_t xLimitQueue;
#endif /* limitSwitch_H */

// port B pin1
#define limitSwitchUpPin (1<<1)
#define limitSwitchDownPin (1<<2)



void LimitSwitchInit();
void vLimitSwitchInterruptTask(void );
