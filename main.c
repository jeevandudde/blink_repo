#include <msp430.h> 

/*
 * main.c
 */
#include <msp430.h>

/*
 * main.c
 */
volatile int is_int_run;
int main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    __enable_interrupt();

    P1DIR |= BIT0;                                        // P1DIR P1.0 -- LED

    P1DIR |= BIT4;                                     // clk on this pin
    P1SEL |= BIT4;

    DCOCTL |= 0xE0;                        //to select 1.5 mhz
    BCSCTL1 |= 0x87;                    //  1000 0111 xt2 is off, rsel=7, dco=3

    BCSCTL2 |= DIVS_2;                    // SMCLK divided by 2^2=4

    TACTL = TASSEL_2 + MC_1+ ID_3;        // TASSEL_2= ACLK, contmode(MC_1 = up mode clk will recount) ID= divider for input clk
    CCTL0 = CCIE;                         // interrupt enabled
    CCR0 = 34198;							//  CCR0  24198 (0x5E86) increase the number to increase dealy


 is_int_run = 0;
enum fre{
LED_high;
LED_med;
LED_low
}
enum fre state= LED_low;
while(1) {
  switch(state) {
  case LED_low:
    CCR0=45098;
	if (is_int_run) 
	{
    		P1OUT ^= BIT0;
    		is_int_run = 0;
    }
state = LED_med;
    break;
  case LED_med:
    CCR0=25098;
	if (is_int_run) 
	    {
    		P1OUT ^= BIT0;
    		is_int_run = 0;
    	}
    state = LED_high; // LED back on on next round
    break;
  case LED_high:
    CCR0=15098;
	if (is_int_run) 
	  {
    		P1OUT ^= BIT0;
    		is_int_run = 0;
      }
   
state= LED_low;
   break;
  /**  while(1) {

	 if (is_int_run) {
    		P1OUT ^= BIT0;
    		is_int_run = 0;
    	}
    */ }

}

/**
 * Timer A0 interrupt service routine
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer_a0(void) {
		//SAVE INT INFO

	 is_int_run = 1;

}
