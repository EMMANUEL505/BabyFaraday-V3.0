#include <30f5015.h>
#include "Config.h"
#include "Global_Variables.c"
#include <stdlib.h>
#include "Functions.h"

void main(void)
{	
	printf("System enabled\n\r");
	ADC_Init();
	Motor_Init(PWM_PERIOD);
    //enable_interrupts(INT_RDA);

	setup_motor_pwm(3,MPWM_FREE_RUN,64,0,9999); 
    set_motor_unit(3,3,MPWM_INDEPENDENT | MPWM_ENABLE_H | MPWM_FAULT_NO_CHANGE,0,0); 
    set_motor_pwm_duty(3,3,910); //set PWM 3 to 1000us 
	delay_ms(4000);
    set_motor_pwm_duty(3,3,425); //set PWM 3 to 1000us

    while(true)
	{
		Set_Motor_Duty(0,0);
		while(!input_state(PIN_F6) )//&& !RUN)   //While loop used for waiting an input high  in D8 to start
   		{
			output_toggle(PIN_E3);
      		delay_ms(250);
   		}
    	set_motor_pwm_duty(3,3,1500); //set PWM 3 to 1000us 
		output_high(PIN_E2);
		delay_ms(2000);

		while(RUN){
			//output_toggle(PIN_E2);
			Read_Sensors(sensors_ADC);
			Digitalize_Array(Sensors_ADC,Sensors_BIN,Black_Limit,0,14);
			Get_Average_Center(Sensors_BIN,2,12,&Center);  
         	//Read_Sensors_Digital(sensors_BIN);
         	//Get_Average_Center_Digital(sensors_BIN,2,12,&center); 
         	if(center==-1)	center=last_center;
			Print_Center(center);
		 	last_center=center;
      	 	error=SET_POINT-center;
		 	derivative=error-last_error;
		 	integral=integral+(error/10);
	     	correction=error*(KP)+derivative*(KD)+integral*(KI);
		 	last_error=error;
         	left_correction=(base_speed)-correction;
     	 	right_correction=(base_speed)+correction;      
			Set_Motor_Duty(left_correction,right_correction);
	  		delay_us(delay_time);
			//for(i=2;i<=12;i++)printf("%d",Sensors_BIN[i]);
			//printf("%d\n\r",center);
		}
   }
}

