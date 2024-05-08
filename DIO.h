#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)
void DIO_Init(void);
void DIO_ledRedOn(void) ;

void DIO_ledRedOff(void) ;

void DIO_ledBlueOn(void) ;

void DIO_ledBlueOff(void) ;

void DIO_toggleRED(void);

void DIO_toggleBLUE(void);

void DIO_toggleGREEN(void);
void DIO_ledGreenOn(void);

void DIO_ledGreenOff(void);

