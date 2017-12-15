#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
ISR(INT0_vect){
	int i;
	_delay_ms(100);
	for(i=0;i<3;i++){
        PORTB = 0x00;
        _delay_ms(100);
        PORTB = 0x04;
        _delay_ms(100);
	}	
	PORTB = 0x04;
}
int main(void){
    DDRD = (1<<PD2);
	DDRB = 0xFF;
	EIMSK |= (1<<INT0);
	EICRA |= (1<<ISC01) | (1<<ISC00);
	sei();
	while(1){
		PORTB =0x04;
	}
}