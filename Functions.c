
void ADC_Init(void)
{
	setup_adc_ports(sAN0|sAN1|sAN2|sAN3|sAN4|sAN5|sAN6|sAN7|sAN8|sAN9|sAN10|sAN11|sAN15);//sAN12|sAN13|sAN14|sAN15);//*******Setup ch0 and ch1 as ADC inputs in Px and Py******
	setup_adc(ADC_CLOCK_INTERNAL);
}

void Motor_Init(int16 period)
{
    setup_compare(1, COMPARE_PWM | COMPARE_TIMER3); 			// en OC1 pin 46 M1       
    setup_compare(2, COMPARE_PWM | COMPARE_TIMER2); 			// en OC2 pin 49 M1
    setup_compare(3, COMPARE_PWM | COMPARE_TIMER3); 			// en OC3 pin 50 M2      
   	setup_compare(4, COMPARE_PWM | COMPARE_TIMER3); 			// en OC4 pin 51 M2
 
    setup_timer2(TMR_INTERNAL | TMR_DIV_BY_1,PWM_PERIOD ); 
    setup_timer3(TMR_INTERNAL | TMR_DIV_BY_1,PWM_PERIOD );

    set_pwm_duty(1, 0);    										// M2 Duty 0%   LEFT+
    set_pwm_duty(2, 0);    										// M1 Duty 0%   LEFT-
    set_pwm_duty(3, 0);   										// M2 Duty 0%   RIGHT-
    set_pwm_duty(4, 0);     									// M1 Duty 0%   RIGHT+
}

void Set_Motor_Duty(int16 Left, int16 Right)
{
	if(Left<0)       
    {   
 	   if(Left<-PWM_PERIOD )       Left=-PWM_PERIOD ;
		set_pwm_duty(1, 0); // M2 Duty 25%  izquierdo
		set_pwm_duty(2, (int16)-Left); // M2 Duty 25%  izquierdo      
	}
	if(Left>=0)       
	{   
		if(Left>PWM_PERIOD )       Left=PWM_PERIOD ;
		set_pwm_duty(1, (int16)Left); // M2 Duty 25%  izquierdo
		set_pwm_duty(2, 0); // M2 Duty 25%  izquierdo      
	}
	if(Right<0)
	{
		if(Right<-PWM_PERIOD )    Right=-PWM_PERIOD ;
		set_pwm_duty(3, (int16)-Right); // M1 Duty 25% 
		set_pwm_duty(4, 0); // M1 Duty 25% 
	}
	if(Right>=0)
	{
		if(Right>PWM_PERIOD )    Right=PWM_PERIOD ;
		set_pwm_duty(3, 0); // M1 Duty 25% 
		set_pwm_duty(4,(int16)Right); // M1 Duty 25% 
	}
}

void Print_Center(int16 center)
{
	if(center<16 && center>=0)  { output_low(PIN_E3);		output_high(PIN_E4);}
	if(center>16)   			{ output_high(PIN_E3);		output_low(PIN_E4);}
	if(center==16)   			{ output_low(PIN_E3);		output_low(PIN_E4);} 
}

void Read_Sensors_Digital(int16* value_array)
{
	*(value_array+2)=input_state(PIN_B9);
	*(value_array+3)=input_state(PIN_B7);
    *(value_array+4)=input_state(PIN_B5);
	*(value_array+5)=input_state(PIN_B3);
	*(value_array+6)=input_state(PIN_B1);
	*(value_array+7)=input_state(PIN_B0);
	*(value_array+8)=input_state(PIN_B2);
	*(value_array+9)=input_state(PIN_B4);
	*(value_array+10)=input_state(PIN_B6);
	*(value_array+11)=input_state(PIN_B8);
	*(value_array+12)=input_state(PIN_B10);
}

void Read_Sensors(int16* value_array)
{
	set_adc_channel(9); 
	*(value_array+2)=read_ADC();
	delay_us(5);
	set_adc_channel(7); 
	*(value_array+3)=read_ADC();
	delay_us(5);
	set_adc_channel(5); 
	*(value_array+4)=read_ADC();
	delay_us(5);
	set_adc_channel(3); 
	*(value_array+5)=read_ADC();
	delay_us(5);
	set_adc_channel(1); 
	*(value_array+6)=read_ADC();
	delay_us(5);
	set_adc_channel(0);			//Center sensor			 
	*(value_array+7)=read_ADC();
	delay_us(5);
	set_adc_channel(2); 
	*(value_array+8)=read_ADC();
	delay_us(5);
	set_adc_channel(4); 
	*(value_array+9)=read_ADC();
	delay_us(5);
	set_adc_channel(6); 
	*(value_array+10)=read_ADC();
	delay_us(5);
	set_adc_channel(8); 
	*(value_array+11)=read_ADC();
	delay_us(5);
	set_adc_channel(10); 
	*(value_array+12)=read_ADC();
	delay_us(5);
}

void Get_Black_Limit(int16* limit,int st_index,int end_index,int16* array)
{
	int i=0;
	int16 min=1024,max=0;
	for(i=st_index;i<=end_index;i++)
	{	
		if(*(array+i)>max) max=*(array+i);
		if(*(array+i)<min) min=*(array+i);
	}
	if((max-min)>204) *limit=min+(max-min)/2;//Limite un 80% arriba del minimo
}

void Digitalize_Array(int16* array_ADC,int16* array_BIN,int16 limit,int st_index,int end_index)
{
	int i=0;
	for(i=st_index;i<=end_index;i++)
	{	
		if(*(array_ADC+i)>limit) *(array_BIN+i)=0;
		if(*(array_ADC+i)<=limit)*(array_BIN+i)=1;
	}
}
void Get_Average_Center_Digital(int16* array_BIN,int st_index,int end_index,int16* center)
{
	int i=0;
	int16 pixels_w=0,values_w=0;
	for(i=st_index;i<=end_index;i++)
	{	
		if(*(array_BIN+i)==1)
			{
				values_w=values_w+((i+1)*2);
				pixels_w=pixels_w+1;
			}
	}
	if(pixels_w!=0 ) *center=values_w/pixels_w;
	else *center=-1;
}

void Get_Average_Center(int16* array_BIN,int st_index,int end_index,int16* center)
{
	int i=0;
	int16 pixels_b=0,values_b=0,pixels_w=0,values_w=0;
	for(i=st_index;i<=end_index;i++)
	{	
		if(*(array_BIN+i)==1)
			{
				values_w=values_w+((i+1))*2;
				pixels_w=pixels_w+1;
			}
		if(*(array_BIN+i)==0)
			{
				values_b=values_b+((i+1))*2;
				pixels_b=pixels_b+1;
			}
	}
	if(pixels_w!=11 && pixels_b!=11 ) 
		{
			if(pixels_w<pixels_b) *center=values_w/pixels_w;
			if(pixels_b<pixels_w) *center=values_b/pixels_b;
		}
	else *center=-1;
}

void Powered_Error(float error, float* correction, float max, float max_c)
{
	float step=1,value;
	step=step/max;
	if(error!=0)
	{
		step=error*step;
		value=step*step;
		*correction=max_c*value;
		if(error<0)	*correction=*correction*-1;
	}
	else *correction=0;
	
}

void Get_Value(float* val)
{	
	int i=0;
	do
    {	
		buffer[i]=getc();
		i++;
    }while(buffer[i-1]!=13);
	x=atol(buffer);
	*val=x;		
	putc(13);
}

void Get_Value_L(int16* val)
{	
	int i=0;
	do
    {	
		buffer[i]=getc();
		i++;
    }while(buffer[i-1]!=13);
	x=atol(buffer);
	*val=x;		
	putc(13);
}

#INT_RDA
void isr()
{	
	char option="r";
	option=getc();
	if(option=='r')
		{
			RUN=!RUN;
		}
	if(option=='c')
	{		
		Set_Motor_Duty(0,0);
		printf("base_speed=%u value=",base_speed);
		Get_Value_L(&base_speed);
		printf("delay_time=%u value(ms)=",delay_time);
		Get_Value_L(&delay_time);
		printf("KP=%u value=",(int16)KP);
		Get_Value(&KP);	
		printf("KI=%u value(x0.01)=",(int16)KI);
		Get_Value(&KI);
		KI=KI*.01;
		printf("KD=%u value=(x0.1)",(int16)KD);
		Get_Value(&KD); 
		KD=KD*.1;   
		RUN=0;
	}	
	output_toggle(PIN_D5);
}
