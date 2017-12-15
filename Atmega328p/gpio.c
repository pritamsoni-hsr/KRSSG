#include<avr/io.h>
int main(void)
{
    DDRB=0xff;
    while(1)
    {
            PORTB=0x0ff;
    }
}