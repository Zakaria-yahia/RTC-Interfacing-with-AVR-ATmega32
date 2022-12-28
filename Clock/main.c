/*
 * Clock.c
 *
 * Created: 16/09/2022 11:38:45 ص
 * Author : Zakaraia Yahia
 */ 

#include "SEVEN_SEG.h"
#include "TIMER0.h"
#include "LCD.h"
#include "KEYPAD.h"

#define OC_Value  124            // for interrupt every 1s
#define Congif_key 'c'
void Get_Clock();
static void ctc_isr(void);
uint8_t Seconds=0,Minutes=0,Hours=0,flag=0;
 
int main(void)
{
  LCD_init();  	
 KEYPAD_init();	
 timer0_ctc_isr = ctc_isr;	
 TIMER0_CTC_init(OC_Value);	
 SEVEN_SEG_init();   

 

 
   uint8_t key_read=0;
   
    while (1)
    {
			
			key_read = KEYPAD_read();
			
			if(key_read == Congif_key){
				
				Get_Clock();
				
				while(key_read == KEYPAD_read());
			
			}
			
				
			LCD_write_command(0x86);
			LCD_write_num(Seconds);
		
		
			LCD_write_command(0x85);
			LCD_write_data(':');
			LCD_write_command(0x83);
			LCD_write_num(Minutes);
		
		
			LCD_write_command(0x82);
			LCD_write_data(':');
			LCD_write_command(0x80);
			LCD_write_num(Hours);
		
		
		
		
    }
}
void Get_Clock()
{
	uint8_t Clock[6]={'0','0','0','0','0','0'};
	uint8_t count=0,key_read=0,digit_num=0,segment=0;
	Hours=0;
	Minutes=0;
	Seconds=0;
	flag=1;
	LCD_write_command(0x01);
	LCD_write_command(0xc0);
	
	key_read=KEYPAD_read();
	
	while(segment<2)
	{
		
		while (digit_num!=2)
		{
			while(key_read == KEYPAD_read());
			key_read = KEYPAD_read();
			
				if(key_read !=0)
			{
				Clock[count]=key_read;
				
				
				LCD_write_data(Clock[count]);
				Hours=((Clock[0]-48)*10)+(Clock[1]-48);
				Minutes=((Clock[2]-48)*10)+(Clock[3]-48);
				Seconds=((Clock[4]-48)*10)+(Clock[5]-48);
				
				_delay_ms(1);
				count++;
				digit_num++;
				
				
			}
			
			
		}
		while(key_read == KEYPAD_read());
		key_read= KEYPAD_read();
		while(key_read == Congif_key)
		{
			segment++;
			digit_num=0;
			LCD_write_command(0xc2);
			LCD_write_data(':');
			LCD_write_command(0xc3);
			break;
		}
		
	}
	flag=0;
}
	



static void ctc_isr(void){
	static uint8_t count = 0;
	if (flag==0)
	{
		count++;
		if(count == 125){
			
			Seconds++;
			count =0;
		}
		
		
		else if (Seconds>=60)
		{
			Seconds=0;
			Minutes++;
		}
		
		else if (Minutes>=60)
		{
			Seconds=0;
			Minutes=0;
			Hours++;
		}
		else if (Hours>=24)
		{
			Seconds=0;
			Minutes=0;
			Hours=0;
		}
		
		
	}
	SEVEN_SEG_write(0,Seconds/10);
	SEVEN_SEG_write(1,Seconds%10);
	SEVEN_SEG_write(2,Minutes/10);
	SEVEN_SEG_write(3,Minutes%10);
	SEVEN_SEG_write(4,Hours/10);
	SEVEN_SEG_write(5,Hours%10);
	
	
	
	
	
	
	}