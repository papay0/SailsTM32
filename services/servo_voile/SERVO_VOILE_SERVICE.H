#ifndef __CERVO_VOILE_H
#define __CERVO_VOILE_H

#include "gpio.h"
#include "clock.h"
#include "timer_1234.h"

void Service_Servo_Init();

void Service_Servo_Set_Angle(int AngleServo);

#endif /* __CERVO_VOILE_H */

//rate =(2.5/45)*AngleServo+2.5;