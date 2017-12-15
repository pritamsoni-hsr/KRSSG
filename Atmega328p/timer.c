/* double led blinks alternatively at a delay of 0.4 sec */
#define F_CPU 16000000UL
#include<avr/io.h>
int main(void)
{
    DDRB=0x0f;              //port C as output
    TCCR1B |=(1<<CS12);      //prescale 256
    TCNT1=0;
    while(1)
    {
        for(TCNT1=0;TCNT1<24999;)      //0.4sec delay
        {
            PORTB =0b00000100;
        }
        for(TCNT1=24999;TCNT1<49998;)
        {
            PORTB =0b00000000;
        }
        TCNT1=0;
    }
}