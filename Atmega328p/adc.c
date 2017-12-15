#define F_CPU 16000000UL
#include<avr/io.h>
int main(void){
        int adc1,adc2,emf;
        uint8_t brightness=0;
        ADMUX |= (1<<REFS0)|(1<<ADLAR);
        ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADSC);
        TCCR0A |= (1<<WGM00)|(1<<WGM01)|(1<<COM0A1);
        TCCR0B |= (1<<CS00);
        DDRC=0x00;
        while(ADCSRA & (1<<ADSC));
        adc1 = (ADCH <<2);           //adc=0
        adc2 = (ADCL>>6);
        emf = ((adc1 + adc2)/1023)*5;
        brightness=emf*255/5;
        if(ADSC=0){
                OCR0A=brightness;
        }
        if(ADSC=1){
                OCR0A=brightness;
        }
}