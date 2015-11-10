#include "Functions.c"

void ADC_Init(void);
void Motor_Init(int16 period);
void Set_Motor_Duty(int16 Left, int16 Right);
void Print_Center(int16 center);

void Read_Sensors(int16* value_array);
void Read_Sensors_Digital(int16* value_array);
void Get_Black_Limit(int16 limit,int st_index,int end_index,int16* array);
void Digitalize_Array(int16* array_ADC,int16* array_BIN,int16 limit,int st_index,int end_index);
void Get_Average_Center(int16* array_BIN,int st_index,int end_index,int16* center);
void Get_Average_Center_Digital(int16* array_BIN,int st_index,int end_index,int16* center);
void Powered_Error(float error, float* correction, float max, float max_c);
void Get_Value(float* val);
void Get_Value_L(int16* val);