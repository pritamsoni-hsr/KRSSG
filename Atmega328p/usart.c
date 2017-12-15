/* led blinks if data received is exactly the data received */
#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)
#include<avr/io.h>
#include<usart/usart.h> 
int main(void){
    unsigned char data;
    UBRR0H = (BAUDRATE>>8);
    UBRR0L=BAUDRATE;
    UCSR0B |= (1<<TXEN0);     //treans enavle
    UCSR0C |= (1<<UMSEL00) | (1<<UCSZ01) | (1<<UCSZ00);       //8bit data
    while (!(UCSR0A & (1<<UDRE0)));     //trans
    UDR0 = data;
    /*
    while(!(UCSR0A)& (1<<RXC0));        //rcv
    return UDR0;
*/
    while(1){
        while (!(UCSR0A & (1<<UDRE0)));     //trans
        UDR0 = data;
    }
}