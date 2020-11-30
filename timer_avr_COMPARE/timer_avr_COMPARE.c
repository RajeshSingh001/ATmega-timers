#include <avr/io.h>
#include <avr/interrupt.h>

#include "lcd.h"

//Global variable for the clock system
volatile unsigned int   clock_millisecond=0;
volatile unsigned char  clock_second=0;

volatile unsigned char  clock_minute=0;

main()
{
   //Initialize the LCD Subsystem
   InitLCD(LS_BLINK);
   //Clear the display
   LCDClear();

   //Set up the timer1 as described in the
   //tutorial

   TCCR1B=(1<<WGM12)|(1<<CS11)|(1<<CS10);
   OCR1A=250;

   //Enable the Output Compare A interrupt
   TIMSK|=(1<<OCIE1A);


   LCDWriteStringXY(0,0,"Time Base Demo");
   LCDWriteStringXY(0,1,"  :   (MM:SS)");

   //Enable interrupts globally

   sei();

   //Continuasly display the time
   while(1)
   {
      LCDWriteIntXY(0,1,clock_minute,2);
      LCDWriteIntXY(3,1,clock_second,2);
      _delay_loop_2(0);
   }

}


//The output compate interrupt handler
//We set up the timer in such a way that
//this ISR is called exactly at 1ms interval
ISR(TIMER1_COMPA_vect)
{
   clock_millisecond++;
   if(clock_millisecond==1000)
   {
      clock_second++;
      clock_millisecond=0;
      if(clock_second==60)
      {
         clock_minute++;
         clock_second=0;
      }
   }
}
