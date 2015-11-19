
int16 sensors_ADC[15],black_limit=730;
int16   center_der=0,sensors_BIN[15],base_speed=700,left_correction,right_correction,last_center=16,center,last_error,error,derivative,correction;
float   integral=0,KD=450,KP=70,KI=8;
int RUN=0xFF;//
int16 x=0,delay_time=16000,BoostCounter=0;
//KD=0,KP=125,KI=0,BaseSpeed=700