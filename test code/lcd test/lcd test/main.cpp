/*
 * lcd test.cpp
 *
 * Created: 16/03/2023 01:01:am
 * Author : Davie
 */ 
#define F_cpu 16000000ul
#include <avr/io.h>
#include <util/delay.h>
# define LCD PORTA  // LCD data port connected to port a

#define EN 7
#define RW 6
#define RS 5

unsigned char keypad()
{
	PORTC=0b11111110;    //make first row=0
	if((PINC&(1<<PINC4))==0)
	{
		_delay_ms(200);
		return '7';
	}
	else if ((PINC&(1<<PINC5))==0)
	{
		_delay_ms(200);
		return '8';
	}
	else if((PINC&(1<<PINC6))==0)
	{
		_delay_ms(200);
		return '9';
	}
	else if ((PINC&(1<<PINC7))==0)
	{
		_delay_ms(200);
		return '/';
	}
	
	PORTC=0b11111101;    // make second row=0
	if ((PINC&(1<<PINC4))==0)
	{
		_delay_ms(200);
		return '4';
	}
	else if ((PINC&(1<<PINC5))==0)
	{
		_delay_ms(200);
		return '5';
	}
	else if ((PINC&(1<<PINC6))==0)
	{
		_delay_ms(200);
		return '6';
	}
	else if ((PINC&(1<<PINC7))==0)
	{
		_delay_ms(200);
		return '*';
	}
	
	PORTC=0b11111011;      //make third row 0
	if((PINC&(1<<PINC4))==0)
	{
		_delay_ms(200);
		return '1';
	}
	else if((PINC&(1<<PINC5))==0)
	{
		_delay_ms(200);
		return '2';
	}
	else if((PINC&(1<<PINC6))==0)
	{
		_delay_ms(200);
		return '3';
	}
	else if((PINC&(1<<PINC7))==0)
	{
		_delay_ms(200);
		return '-';
	}
	
	PORTC=0b11110111;   //make fourth row 0
	if ((PINC&(1<<PIN4))==0)
	{
		_delay_ms(200);
		lcd_clear();
	}
	else if ((PINC&(1<<PINC5))==0)
	{
		_delay_ms(200);
		return '0';
	}
	else if ((PINC&(1<<PINC6))==0)
	{
		_delay_ms(200);
		return '=';
	}
	else if ((PINC&(1<<PINC7))==0)
	{
		_delay_ms(200);
		return '+';
	}
	return 0;
}

void lcdcmd(unsigned char cmd)
{
	PORTD &=(1<<RS);  //RS=0 for command
	PORTD &=~(1<<RW);  //RW=0 for write
	LCD=cmd & 0XF0;  //send upper nibble
	PORTD |=(1<<EN); //EN=1 for H to L pulse
	_delay_ms(1);
	PORTD&=~(1<<EN); //EN=0 for H to L pulse
	
	LCD=cmd<<4;         //send low nibble
	PORTD|=(1<<EN);     //EN =1 for H to l pulse
	_delay_ms(1);
	PORTD&=~(1<<EN);
	
}

void lcddata(unsigned char data)
{
	PORTD |=(1<<RS);  //RS=1 for data
	PORTD &=~(1<<RW);  //RW=0 for write
	LCD=data & 0XF0;  //send upper nibble
	PORTD |=(1<<EN); //EN=1 for H to L pulse
	_delay_ms(1);
	PORTD&=~(1<<EN); //EN=0 for H to L pulse
	
	LCD=data<<4;         //send low nibble
	PORTD|=(1<<EN);     //EN =1 for H to l pulse
	_delay_ms(1);
	PORTD&=~(1<<EN);

}


void lcd_init()
{
	DDRA=0xFF;    //Define output of lcd port
	DDRD=0XFF;     //define RS,EN and RW pin as out put
	PORTD&=~(1<<EN);    //Initialize en=0
	lcdcmd(0x33);
	lcdcmd(0x32);
	lcdcmd(0x28);       //LCD 4 bit mode
	lcdcmd(0x0E);      //display on cursor  on
	lcdcmd(0x01);       //clear lcd
	_delay_ms(2);
}

   
lcd_init();
lcd_clear();
lcd_goto(0,0);
lcd_puts("Emad Helmi") ;





int main(void)
{
	
	
	
	
	
	
	
	
	
	
	unsigned char X;
	DDRC=0x0F;  // make PCO to PC3 =O/P and PC4 to PC7 =I/P
	_delay_ms(1);
	PORTC=0xF0;
	lcd_init();
	
	while (1)
	{
		PORTC=0XF0;   //make all 4 column and all 4 rows 0
		_delay_ms(25);
		if(PINC!=0XF0)
		{
			X=keypad();
			lcddata(X);
		}
	}
	
	return 0;

}


