#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>

int main(void)
{
	int brightness;
	DDRD |=(1<<PD6);
	TCCR0A |=(1<<COM0A1)|(1<<WGM01)|(1<<WGM00); 
    TCCR0B |=(1<<CS00);
    TCNT0=0;
	while(1)
    {
        for(brightness=0;brightness<255;brightness++)
        {
            OCR0A = brightness;
            _delay_ms(10);
        }
    }
}

