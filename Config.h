#DEVICE ADC=10
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES FRC_PLL16                //Internal Fast RC oscillator with 16X PLL
//#FUSES FRC_PLL8               //Internal Fast RC oscillator with 8X PLL
#FUSES PR_PLL                   //Primary Oscillator with PLL
#FUSES NOCKSFSM                 //Clock Switching is disabled, fail Safe clock monitor is disabled
#FUSES WPSB16                   //Watch Dog Timer PreScalar B 1:16
#FUSES WPSA512                  //Watch Dog Timer PreScalar A 1:512
#FUSES PUT64                    //Power On Reset Timer value 64ms
#FUSES NOBROWNOUT               //No brownout reset
#FUSES BORRES                
#FUSES LPOL_HIGH                //Low-Side Transistors Polarity is Active-High (PWM 0,2,4 and 6)
   //PWM module low side output pins have active high output polar
#FUSES HPOL_HIGH                //High-Side Transistors Polarity is Active-High (PWM 1,3,5 and 7)
   //PWM module high side output pins have active high output polarity
#FUSES NOPWMPIN                 //PWM outputs drive active state upon Reset
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOWRT                    //Program memory not write protected
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOCOE                    //Device will reset into operational mode
//#FUSES ICSP1                    //ICD uses PGC1/PGD1 pins
#use delay(clock=117920000)
//#use delay(clock=58960000)
//#use rs232(UART1,baud=115200,bits=8, xmit=PIN_F3,rcv=PIN_F2, parity=N, TIMEOUT=5000)
#DEFINE PWM_PERIOD 	1499
#DEFINE SET_POINT	16