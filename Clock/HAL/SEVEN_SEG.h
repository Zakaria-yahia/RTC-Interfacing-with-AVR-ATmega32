/*
 * SEVEN_SEG.c
 *
 * Created: 8/18/2022 8:32:20 PM
 *  Author: Zakaria yahia 
 */ 



#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_

#include "std_macros.h"

#define INIT_SEVEN_SEG_PINS DDRC |= 0xff;
#define INIT_SEVEN_SEG_En_PINS DDRD |= 0xff;
#define PORT_DISABLE_ALL_SS PORTD=0;
void SEVEN_SEG_init(void);
void SEVEN_SEG_write(uint8_t , uint8_t);



#define EN0 SETBIT(PORTD,0); 
#define EN1 SETBIT(PORTD,1); 
#define EN2 SETBIT(PORTD,2); 
#define EN3 SETBIT(PORTD,3);
#define EN4 SETBIT(PORTD,4); 
#define EN5 SETBIT(PORTD,5);


#define PORT_WRITE PORTC


#endif /* SEVEN_SEG_H_ */