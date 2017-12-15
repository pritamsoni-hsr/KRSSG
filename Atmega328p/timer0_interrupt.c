/*led blink at delay of 3sec*/
#define F_CPU 16000000UL
#include<avr/io.h>
#include<avr/interrupt.h>
volatile uint8_t total_ovrflow;
void timer0_init(){
    TCCR0B |=(1<<CS02) | (1<<CS00);
    TCNT0 =0;
    TIMSK0 |=(1<<TOIE0);
    sei();
    total_ovrflow=0;
}
ISR(TIMER0 OVF_vect){
    total_ovrflow++;
}
int main(void){
    DDRB |=(1<<PB2);
    timer0_init();
    while(1){
        if (total_ovrflow>=183){
            if (TCNT0>=209){
                PORTB ^= (1<<PB2);
                TCNT0 = 0;
                total_ovrflow = 0;
            }
        }
    }   
}