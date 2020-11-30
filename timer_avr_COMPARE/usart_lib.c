#include<avr/io.h>
#include<util/delay.h>
#include"lcd.h"

#define EOT '%'
#define SOT '^'


void USARTInit(uint16_t ubrr_value)
{

   //Set Baud rate

   UBRRL = ubrr_value;
   UBRRH = (ubrr_value>>8);

   /*Set Frame Format


   >> Asynchronous mode
   >> No Parity
   >> 1 StopBit

   >> char size 8

   */

   UCSRC=(1<<URSEL)|(3<<UCSZ0);


   //Enable The receiver and transmitter

   UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(1<<TXCIE);


}


//This function is used to read the available data
//from USART. This function will wait untill data is
//available.
char USARTReadChar()
{
   //Wait untill a data is available

   while(!(UCSRA & (1<<RXC)))
   {
      //Do nothing
   }

   //Now USART has got data from host
   //and is available is buffer

   return UDR;
}


//This fuction writes the given "data" to
//the USART which then transmit it via TX line
void USARTWriteChar(char data)
{
   //Wait untill the transmitter is ready

   while(!(UCSRA & (1<<UDRE)))
   {
      //Do nothing
   }

   //Now write the data to USART buffer

   UDR=data;
}



void USARTWriteInt(int val,unsigned int field_length)
{
	/***************************************************************
	This function writes a integer type value to LCD module

	Arguments:
	1)int val	: Value to print

	2)unsigned int field_length :total length of field in which the value is printed
	must be between 1-5 if it is -1 the field length is no of digits in the val

	****************************************************************/

	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	while(val)
	{
	str[i]=val%10;
	val=val/10;
	i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	if(val<0) USARTWriteChar('-');
	for(i=j;i<5;i++)
	{
	USARTWriteChar(48+str[i]);
	//USARTWriteChar(48+str[i]);
	for(i=0;i<4;i++)
	{
	_delay_ms(10);
	}
}}

void write(char *data)
{
	//USARTWriteChar('#');
	//USARTWriteChar(3);
	//USARTWriteChar(1);
	while(*data)
	USARTWriteChar(*data++);
	//USARTWriteChar('\n');
	//USARTWriteInt(data,2);
	//while(*data) USARTWriteChar(*data++);
}


