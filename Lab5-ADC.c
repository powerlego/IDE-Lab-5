/*
* Rochester Institute of Technology
* Department of Computer Engineering
* CMPE 460  Interfacing Digital Electronics
* LJBeato
* 1/14/2021
*
* Filename: main_timer_template.c
*/
#include <stdio.h>
#include <stdlib.h>

#include "msp.h"
#include "uart.h"
#include "leds.h"
#include "switches.h"
#include "Timer32.h"
#include "CortexM.h"
#include "Common.h"
#include "ADC14.h"
// The sprintf function seemed to cause a change in the interrupt service routine.
// I think if we increase the HEAP size, it will work
// change to Heap_Size       EQU     0x00000200 in startup_msp432p401r_uvision.s


BOOLEAN Timer1RunningFlag = FALSE;
BOOLEAN Timer2RunningFlag = FALSE;

unsigned long MillisecondCounter = 0;



// Interrupt Service Routine for Timer32-1
void Timer32_1_ISR(void)
{		int f;
		char str2[78];
		char str[78];
    int ch = ADC_In();
		
	
	
//The value is read in Volts. 
	
		uart0_put("\r\nThe ADC reading is:");
    sprintf(str, "%d\r\n", ch);
    uart0_put(str);
	

}


// Interrupt Service Routine
void Timer32_2_ISR(void)
{
    int ch = ADC_In();
	
    char str2[78];
    sprintf(str2, "%d\r\n", ch);
    uart0_put(str2);
}
// main
int main(void)
{
    char temp[64];
    unsigned int analogIn = 0;
    //initializations
    uart0_init();
    uart0_put("\r\nLab5 ADC demo\r\n");
    LED1_Init();
    LED2_Init();
    Switch2_Init();
    ADC0_InitSWTriggerCh6();
    Timer32_1_Init(&Timer32_1_ISR, SystemCoreClock/2, T32DIV1);
    Timer32_2_Init(&Timer32_2_ISR, SystemCoreClock/2, T32DIV1);
    EnableInterrupts();
    TIMER32_CONTROL1 |= BIT7;
  while(1)
    {
        WaitForInterrupt();

  }
}