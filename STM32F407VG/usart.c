#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
void Pins_Init(void){
    	GPIO_InitTypeDef GPIO_InitStruct;
    	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
     	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    	GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
void Timer_Init(void){
    	TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    	TIM_BaseStruct.TIM_Prescaler = 0;
    	TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
/* PWM_frequency = timer_tick_frequency / (TIM_Period + 1) */
    	TIM_BaseStruct.TIM_Period = 100;
    	TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    	TIM_BaseStruct.TIM_RepetitionCounter = 0;
    	TIM_TimeBaseInit(TIM4, &TIM_BaseStruct);
    	TIM_Cmd(TIM4, ENABLE);
}
void Receive(void){
	unsigned char A;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);		//usart1 or 6
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_Rx, ENABLE);		//for Tx,Rx,cts,sclk
	USART_Init();
	USART_Cmd(USART1, ENABLE);
	return A;
}
void Transmit(void){
	unsigned char a;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);		//usart1 or 6
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_Tx, ENABLE);		//for Tx,Rx,cts,sclk
	USART_Init();
	USART_Cmd(USART1, ENABLE);
	return A;
}
void Interrupt(void){
	ri;
}
int main(void){
	SystemInit();
	Pins_Init();
	Timer_Init();
	Receive();
    while(1){
    }
}