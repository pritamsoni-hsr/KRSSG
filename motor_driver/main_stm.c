#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_uart.h"

// usart{1,2,3,6} and uart4
/*
U(S)ARTx    TX   RX         TX   RX         TX  RX      APB
USART1      PA9  PA10       PB6  PB7                    2
USART2      PA2  PA3        PD5  PD6                    1
USART3      PB10 PB11       PC10 PC11       PD8 PD9     1
UART4       PA0  PA1        PC10 PC11                   1
UART5       PC12 PD2                                    1
USART6      PC6  PC7        PG14 PG9                    2
UART7       PE8  PE7        PF7  PF6                    1
UART8       PE1  PE0                                    1
*/

void Pins_Init(void){
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_Tx, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_Tx, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_Tx, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_Tx, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_Tx, ENABLE);

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1); //TX
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1); //RX
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //TX
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //RX
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //TX
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //RX
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); //TX
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); //RX
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4); //TX
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4); //RX

    GPIO_InitTypeDef gpio1,gpio2,gpio3,gpio6,gpio4;
    gpio1.GPIO_Mode = GPIO_Mode_AF;                  //usart1
    gpio1.GPIO_OType = GPIO_OType_PP;
    gpio1.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    gpio1.GPIO_PuPd = GPIO_PuPd_UP;
    gpio1.GPIO_Speed = GPIO_Speed_50MHz;

    gpio2.GPIO_Mode = GPIO_Mode_AF;                  //usart2
    gpio2.GPIO_OType = GPIO_OType_PP;
    gpio2.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    gpio2.GPIO_PuPd = GPIO_PuPd_UP;
    gpio2.GPIO_Speed = GPIO_Speed_50MHz;

    gpio3.GPIO_Mode = GPIO_Mode_AF;                  //usart3
    gpio3.GPIO_OType = GPIO_OType_PP;
    gpio3.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    gpio3.GPIO_PuPd = GPIO_PuPd_UP;
    gpio3.GPIO_Speed = GPIO_Speed_50MHz;

    gpio6.GPIO_Mode = GPIO_Mode_AF;                  //usart6
    gpio6.GPIO_OType = GPIO_OType_PP;
    gpio6.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    gpio6.GPIO_PuPd = GPIO_PuPd_UP;
    gpio6.GPIO_Speed = GPIO_Speed_50MHz;

    gpio4.GPIO_Mode = GPIO_Mode_AF;                  //uart4
    gpio4.GPIO_OType = GPIO_OType_PP;
    gpio4.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    gpio4.GPIO_PuPd = GPIO_PuPd_UP;
    gpio4.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB,GPIOA,GPIOB,GPIOC,GPIOA, &gpio1,&gpio2,&gpio3,&gpio6,&gpio4);
}
void USART_Initialize(){
    RCC_APB2PeriphClockCmd (RCC_APB1Periph_USART1, ENABLE);
    RCC_APB1PeriphClockCmd (RCC_APB1Periph_USART2, ENABLE);
    RCC_APB1PeriphClockCmd (RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd (RCC_APB1Periph_USART6, ENABLE);
    RCC_APB1PeriphClockCmd (RCC_APB1Periph_UART4, ENABLE);

    USART_InitTypeDef usart1 usart2 usart3 usart6 uart4;
    usart1.USART_BaudRate = 9600;
    usart1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart1.USART_Parity = USART_Parity_No;
    usart1.USART_StopBits = USART_StopBits_1;
    usart1.USART_WordLength = USART_WordLength_8b;
    usart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    usart2.USART_BaudRate = 9600;
    usart2.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart2.USART_Parity = USART_Parity_No;
    usart2.USART_StopBits = USART_StopBits_1;
    usart2.USART_WordLength = USART_WordLength_8b;
    usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    usart3.USART_BaudRate = 9600;
    usart3.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart3.USART_Parity = USART_Parity_No;
    usart3.USART_StopBits = USART_StopBits_1;
    usart3.USART_WordLength = USART_WordLength_8b;
    usart3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    usart6.USART_BaudRate = 9600;
    usart6.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart6.USART_Parity = USART_Parity_No;
    usart6.USART_StopBits = USART_StopBits_1;
    usart6.USART_WordLength = USART_WordLength_8b;
    usart6.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    uart4.USART_BaudRate = 9600;
    uart4.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    uart4.USART_Parity = USART_Parity_No;
    uart4.USART_StopBits = USART_StopBits_1;
    uart4.USART_WordLength = USART_WordLength_8b;
    uart4.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1,USART2,USART3,USART6, &usart1,&usart2,&usart3,&usart6,&uart4);
    USART_Cmd(USART1, ENABLE);
    USART_Cmd(USART2, ENABLE);
    USART_Cmd(USART3, ENABLE);
    USART_Cmd(USART6, ENABLE);
    USART_Cmd(UART4, ENABLE);
}
void Receive(void){
    return data;
}
void Transmit(void){        //page 974

    unsigned char a;
}
int main(void){
    uint8_t s1=0,s2=0,s3=0,s4=0,drxn=1;
    SystemInit();
    Pins_Init();
    USART_Initialize();
    ENABLE_USART();
    while(1){
        Transmit();
    }
}
