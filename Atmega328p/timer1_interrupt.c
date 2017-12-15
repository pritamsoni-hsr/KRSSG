/* single led blinks with 5 sec delay,using timer1 interrupt */
#define F_CPU 16000000UL
#include<avr/io.h>
#include<avr/interrupt.h>
volatile uint8_t total_ovrflow;
ISR(TIMER1_OVF_vect){
    total_ovrflow++;
}
int main(void){
    DDRB |=(1<<PB2);
    TCCR1B |=(1<<CS12) | (1<<CS10);          //prescale-1024
    TCNT1=0;
    TIMSK1 |=(1<<TOIE1);         //enable overflow
    sei();                      //global int enable
    total_ovrflow=0;
    while(1){
        if(total_ovrflow>=1){       // 65535 steps done{
            if(TCNT1>=12589){        //65535+12589=78124 steps done{
                PORTB ^=(0x04);
                TCNT1=0;
                total_ovrflow=0;
            }
        }
    }

}