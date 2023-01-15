/*
Title: GPIO initialization and LED output
Purpose: Initialize the GPIO to accept button inputs to control LEDs
Name: Nicholas Curl
Date: 9/2/2021

This file prepared by LJBeato
01/11/2021

*/
#include "msp.h"

#define LED1 BIT0;
#define LED2_RED BIT0;
#define LED2_GREEN BIT1;
#define LED2_BLUE BIT2;
#define SW1 BIT1;
#define SW2 BIT4;
typedef unsigned char BOOLEAN;
#define FALSE 0
#define TRUE  !FALSE
typedef unsigned char BYTE;


// Main Program
// 1. Init LEDs
// 2. Init Switch
// 3. init state=0
// 4. If SW1 pressed, light LED1
// 5. if SW2 pressed, cycle next color of R,G,B,C,M,Y,W
// 5. If button released
//		Turn off the LED
//
//
void LED1_Init(void) {
    // configure PortPin for LED1 as port I/O
    P1->SEL0 &= ~LED1;
    P1->SEL1 &= ~LED1;
    // make built-in LED1 LED high drive strength
    P1->DS |= LED1;
    // make built-in LED1 out
    P1->DIR |= LED1;
    // turn off LED
    P1->OUT &= ~LED1;
}

void LED2_Init(void) {
    // configure PortPin for LED2 as port I/O
    P2->SEL0 &= ~LED2_RED;
    P2->SEL1 &= ~LED2_RED;
    P2->SEL0 &= ~LED2_GREEN;
    P2->SEL1 &= ~LED2_GREEN;
    P2->SEL0 &= ~LED2_BLUE;
    P2->SEL1 &= ~LED2_BLUE;

    // make built-in LED2 LEDs high drive strength
    P2->DS |= LED2_RED;
    P2->DS |= LED2_GREEN;
    P2->DS |= LED2_BLUE;
    // make built-in LED2 out
    P2->DIR |= LED2_RED;
    P2->DIR |= LED2_GREEN;
    P2->DIR |= LED2_BLUE;
    // turn off LED
    P2->OUT &= ~LED2_RED;
    P2->OUT &= ~LED2_GREEN;
    P2->OUT &= ~LED2_BLUE;

}

void Switches_Init(void) {
    // configure PortPin for Switch 1 and Switch2 as port I/O
    P1->SEL0 &= ~SW1;
    P1->SEL1 &= ~SW1;
    P1->SEL0 &= ~SW2;
    P1->SEL1 &= ~SW2;
    // configure as input
    P1->DIR &= ~SW1;
    P1->DIR &= ~SW2;
    // enable pullup resistor
    P1->REN |= SW1;
    P1->OUT |= SW1;
    P1->REN |= SW2;
    P1->OUT |= SW2;

}

//------------Switch_Input------------
// Read and return the status of Switch1
// Input: none
// return: TRUE if pressed
//         FALSE if not pressed
BOOLEAN Switch1_Pressed(void) {
    BOOLEAN retVal = FALSE;
    int val = P1->IN & SW1;
    if (val) {
        retVal = FALSE;
    } else {
        retVal = TRUE;
    }
    // check if pressed

    return (retVal);              // return TRUE(pressed) or FALSE(not pressed)
}

//------------Switch_Input------------
// Read and return the status of Switch2
// Input: none
// return: TRUE if pressed
//         FALSE if not pressed
BOOLEAN Switch2_Pressed(void) {
    BOOLEAN retVal = FALSE;
    // check if pressed
    int val = P1->IN & SW2;
    if (val) {
        retVal = FALSE;
    } else {
        retVal = TRUE;
    }

    return (retVal);              // return TRUE(pressed) or FALSE(not pressed)
}

int main(void) {
    //Initialize any supporting variables
    int mode = -1;
    // Initialize buttons and LEDs
    // Init the RED LED
    LED1_Init();
    // Init the RGB LED
    LED2_Init();
    //initialize Button 1 and Button 2
    Switches_Init();

    for (;;) {

        //Turn on an LED1 (RED) when button 1 is held
        if (Switch1_Pressed() == TRUE) {
            // turn on LED1
            P1->OUT |= LED1;
        } else {
            P1->OUT &= ~LED1;
            // turn off LED1

        }

        // now do the same for LED2
        if (Switch2_Pressed() == TRUE) {
            mode++;
					if (mode >= 0) {
							for(int count = 0; count<3; count++){
                //rgb mode
                if ((mode % 3) == 0) {
                    //red
                    if ((count % 3) == 0) {
                        P2->OUT |= LED2_RED;
                        P2->OUT &= ~LED2_GREEN;
                        P2->OUT &= ~LED2_BLUE;
                    //green
                    } else if ((count % 3) == 1) {
                        P2->OUT &= ~LED2_RED;
                        P2->OUT |= LED2_GREEN;
                        P2->OUT &= ~LED2_BLUE;
                    }
                    //blue
					else if ((count % 3) == 2){
						P2->OUT &= ~LED2_RED;
                        P2->OUT &= ~LED2_GREEN;
                        P2->OUT |= LED2_BLUE;
					}
					else {
						P2->OUT &= ~LED2_RED;
						P2->OUT &= ~LED2_GREEN;
						P2->OUT &= ~LED2_BLUE;
					}
                }
                //cyan, magenta, yellow
				else if ((mode % 3) == 1) {
                    //cyan
                    if ((count % 3) == 0) {
                        P2->OUT &= ~LED2_RED;
                        P2->OUT |= LED2_GREEN;
                        P2->OUT |= LED2_BLUE;
                    }
                    //magenta
                    else if ((count % 3) == 1) {
                        P2->OUT |= LED2_RED;
                        P2->OUT &= ~LED2_GREEN;
                        P2->OUT |= LED2_BLUE;
                    }
                    //yellow
					else if ((count % 3) == 2){
						P2->OUT |= LED2_RED;
                        P2->OUT |= LED2_GREEN;
                        P2->OUT &= ~LED2_BLUE;
					}
					else {
						P2->OUT &= ~LED2_RED;
						P2->OUT &= ~LED2_GREEN;
						P2->OUT &= ~LED2_BLUE;
					}
                }
                //white
				else if ((mode % 3) == 2) {
                   P2->OUT |= LED2_RED;
                   P2->OUT |= LED2_GREEN;
                   P2->OUT |= LED2_BLUE; 
                }
                //turn off
				else {
					P2->OUT &= ~LED2_RED;
					P2->OUT &= ~LED2_GREEN;
					P2->OUT &= ~LED2_BLUE;
				}
                //delay for showing LED colors
				for(int i =0; i<100000; i++){
				}
            }
          }
        } else {
            // Turn off LED2
            P2->OUT &= ~LED2_RED;
			P2->OUT &= ~LED2_GREEN;
			P2->OUT &= ~LED2_BLUE;
        }
    }
}
