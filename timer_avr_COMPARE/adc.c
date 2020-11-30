#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay_basic.h>
#include "lcd.h"


void InitADC()
  {
    ADMUX=(1<<REFS0);// For Aref=AVcc;
    ADCSRA=(1<<ADEN)|(7<<ADPS0);
   }

uint16_t ReadADC(uint8_t ch)
   {
	//Select ADC Channel ch must be 0-7
	ADMUX&=~(1<<0);
	ADMUX&=~(1<<1);
	ADMUX&=~(1<<2);
	ADMUX&=~(1<<3);
	ADMUX&=~(1<<4);
	ch=ch&0b00011111;
	ADMUX|=ch;
	
	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	ADCSRA|=(1<<ADIF);

	return(ADC);
   }


  void delay()
   {
      int i;
       for(i=0;i<100;i++)
       {
        _delay_loop_2(0);
       }
    }
	 
/* main program....................................*/	
void main()
{
    MCUCSR=0x80;
    MCUCSR=0x80;
	uint16_t adc_value;
	uint8_t t,i;
	InitLCD(LS_ULINE);
	LCDClear();
	InitADC();	
	USARTInit(95);
	LCDWriteStringXY(0,0,"Congrates");
	LCDWriteStringXY(0,1,"Loading");	

	for (i=0;i<99;i++)
	{
		LCDWriteIntXY(10,1,i,3);
		LCDWriteStringXY(13,1,"%");
		_delay_ms(5);
		
		
	}
	LCDClear();
	while(1)
	{
	adc_value=ReadADC(5);
    t=adc_value/2;
	LCDWriteStringXY(0,0,"Current Temp");
    LCDWriteIntXY(0,1,t,3);
	USARTWriteChar(t);
	
				
    	/*	if(t>(m+2))
		{	
		    PORTD|=(1<<0);
			LCDClear();
			LCDWriteStringXY(0,0,"Temp Exceded...");
			LCDWriteStringXY(0,1,"Current Temp");
		    LCDWriteIntXY(13,1,t,3);
		    _delay_ms(20);
		
		}
		else
		{
		PORTD&=~(1<<0);
		LCDClear();
		LCDWriteString("Current Temp");
		LCDWriteIntXY(0,1,t,3);
		_delay_ms(20);
		}*/
	
	
     	}
       }



	
