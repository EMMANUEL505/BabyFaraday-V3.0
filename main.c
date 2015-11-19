#include <30f5015.h>
#include "Config.h"
#include "Global_Variables.c"
#include <stdlib.h>
#include "Functions.h"

void main(void)
{	
	ADC_Init();
	Motor_Init(PWM_PERIOD);
	setup_motor_pwm(3,MPWM_FREE_RUN,64,0,9999); 
    set_motor_unit(3,3,MPWM_INDEPENDENT | MPWM_ENABLE_H | MPWM_FAULT_NO_CHANGE,0,0); 
    set_motor_pwm_duty(3,3,910); //set PWM 3 to 1000us 
	delay_ms(4000);
    set_motor_pwm_duty(3,3,425); //set PWM 3 to 1000us
    while(true)
	{
		Set_Motor_Duty(0,0);
		while(!input_state(PIN_D8) )//&& !RUN)   //While loop used for waiting an input high  in D8 to start
   		{
			output_toggle(PIN_D5);
      		delay_ms(250);
   		}
    	set_motor_pwm_duty(3,3,1600); //set PWM 3 to 1000us 
		output_high(PIN_D5);
		delay_ms(2000);

		while(RUN){
			Read_Sensors(sensors_ADC);
			Digitalize_Array(Sensors_ADC,Sensors_BIN,Black_Limit,0,14);
			Get_Average_Center(Sensors_BIN,2,12,&Center);  

			if(center>last_center)center_der=center-last_center;
			else if(last_center>=center)center_der=last_center-center;

         	if(center==-1 || center_der>16)	center=last_center;
			Print_Center(center);
		 	last_center=center;
      	 	error=SET_POINT-center;
		 	derivative=error-last_error;
		 	if(error>4 || error<-4) integral=integral+error;
			else integral=0;
			if(integral>120) integral=100;
			if(integral*(-1)>120) integral=-100;
		 	//integral=integral+error;
	     	correction=error*(KP)+derivative*(KD)+integral*(KI);
		 	last_error=error;

		   	if(center>14 && center<18 && BoostCounter<14) 
			{
				BoostCounter++;
				if(BoostCounter>4) base_speed=1200; //set_motor_pwm_duty(3,3,2500);correction=0 ;//Boost=499-BaseSpeed;
			}	
		    else
			{
				BoostCounter=0; base_speed=800;//set_motor_pwm_duty(3,3,2650);}*/
			}

         	left_correction=(base_speed)-correction;
     	 	right_correction=(base_speed)+correction;      
			Set_Motor_Duty(left_correction,right_correction);
	  		delay_us(delay_time);
		}
   }
}

