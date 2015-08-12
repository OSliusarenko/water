// Watering program for plants
// Watering every 24 hours

#include <msp430f2001.h>

volatile unsigned char deepSleepCnt;
volatile unsigned int  deepSleepCnt10sec, deepSleep10sec;

void deepSleep(unsigned int ten_sec_intervals);


int main(void) {

    WDTCTL = WDTPW | WDTHOLD;
    P1DIR |= 0x03;
    P1OUT = 0;
    
    while(1) { 
        P1OUT |= 0x03; 
        deepSleep(1); // water 10 sec

        P1OUT &= ~0x03; 

        deepSleep(8640); // wait approx 24 hrs
        deepSleep(8640); // wait approx 24 hrs
    }
}

void __attribute__ ((interrupt(WDT_VECTOR))) watchdog_timer (void)
{
    if(++deepSleepCnt==45) // approx 10 seconds interval
    {
        deepSleepCnt = 0;
        if(++deepSleepCnt10sec==deepSleep10sec)
        {
            _BIC_SR_IRQ(LPM0_bits); // Clear LPM0 bits from 0(SR)
        };
    };
}

void deepSleep(unsigned int ten_sec_intervals)
{
    // SMCLK as WDT+ source is not good since consumes much
    // power but since the quartz is abscent...
    BCSCTL2 |= DIVS_3;                        // SMCLK/8
    WDTCTL = WDT_MDLY_32;                   // WDT SMCLK 32ms interval timer

    deepSleepCnt = 0;
    deepSleepCnt10sec = 0;
    deepSleep10sec = ten_sec_intervals;

    IE1 = WDTIE;                             // Enable WDT interrupt
    _BIS_SR(LPM0_bits + GIE);               // Enter LPM3
    WDTCTL = WDTPW | WDTHOLD;
}



