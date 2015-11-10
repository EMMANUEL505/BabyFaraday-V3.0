
int16 sensors_ADC[15],black_limit=730;
int16   sensors_BIN[15],base_speed=1400,left_correction,right_correction,last_center,center,last_error,error,derivative,correction;
float   integral=0,KD=750,KP=90,KI=0;
int RUN=0xFF;//
int16 x=0,delay_time=9800;
char buffer[50];
//KD=0,KP=125,KI=0,BaseSpeed=700