/*
    To get proper duty cycle, you have simple equation
    500 = ((TIM_Period + 1) * DutyCycle) / 100 - 1
    where DutyCycle is in percent, between 0 and 100%
*/
#include "misc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx.h"


void Configure_PINS(void)
{
	    GPIO_InitTypeDef H1,H2,H3,G1,G2,G3,G4;
	    EXTI_InitTypeDef E1,E2,E3;
	    NVIC_InitTypeDef N1,N2,N3;


	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	    H1.GPIO_Mode = GPIO_Mode_IN;
	    H1.GPIO_OType = GPIO_OType_PP;
	    H1.GPIO_Pin = GPIO_Pin_5;
	    H1.GPIO_PuPd = GPIO_PuPd_DOWN;
	    H1.GPIO_Speed = GPIO_Speed_100MHz;
	    GPIO_Init(GPIOC, & H1);

	    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource5);

	    E1.EXTI_Line = EXTI_Line5;
	    E1.EXTI_LineCmd = ENABLE;
	    E1.EXTI_Mode = EXTI_Mode_Interrupt;
	    E1.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	    EXTI_Init(&E1);

	    N1.NVIC_IRQChannel = EXTI9_5_IRQn;
	    N1.NVIC_IRQChannelPreemptionPriority = 0x00;
	    N1.NVIC_IRQChannelSubPriority = 0x00;
	    N1.NVIC_IRQChannelCmd = ENABLE;
	    NVIC_Init(&N1);

	    H2.GPIO_Mode = GPIO_Mode_IN;
	   	    H2.GPIO_OType = GPIO_OType_PP;
	   	    H2.GPIO_Pin = GPIO_Pin_6;
	   	    H2.GPIO_PuPd = GPIO_PuPd_DOWN;
	   	    H2.GPIO_Speed = GPIO_Speed_100MHz;
	   	    GPIO_Init(GPIOC, &H2);

	   	    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource6);

	   	    E2.EXTI_Line = EXTI_Line6;
	   	    E2.EXTI_LineCmd = ENABLE;
	   	    E2.EXTI_Mode = EXTI_Mode_Interrupt;
	   	    E2.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	   	    EXTI_Init(&E2);

	   	   N2.NVIC_IRQChannel = EXTI9_5_IRQn;
	   	    N2.NVIC_IRQChannelPreemptionPriority = 0x00;
	   	    N2.NVIC_IRQChannelSubPriority = 0x00;
	   	    N2.NVIC_IRQChannelCmd = ENABLE;
	   	    NVIC_Init(&N2);

	   	 H3.GPIO_Mode = GPIO_Mode_IN;
	   		    H3.GPIO_OType = GPIO_OType_PP;
	   		    H3.GPIO_Pin = GPIO_Pin_7;
	   		    H3.GPIO_PuPd = GPIO_PuPd_DOWN;
	   		    H3.GPIO_Speed = GPIO_Speed_100MHz;
	   		    GPIO_Init(GPIOC, &H3);

	   		    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource7);

	   		    E3.EXTI_Line = EXTI_Line8;
	   		    E3.EXTI_LineCmd = ENABLE;
	   		    E3.EXTI_Mode = EXTI_Mode_Interrupt;
	   		    E3.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	   		    EXTI_Init(&E3);

	   		    N3.NVIC_IRQChannel = EXTI9_5_IRQn;
	   		    N3.NVIC_IRQChannelPreemptionPriority = 0x00;
	   		    N3.NVIC_IRQChannelSubPriority = 0x00;
	   		    N3.NVIC_IRQChannelCmd = ENABLE;
	   		    NVIC_Init(&N3);


	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);


    G1.GPIO_Mode =  GPIO_Mode_AF;
    G1.GPIO_OType = GPIO_OType_PP;
    G1.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
    G1.GPIO_PuPd = GPIO_PuPd_DOWN;
    G1.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &G1);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);

    G2.GPIO_Mode =  GPIO_Mode_AF;
    G2.GPIO_OType = GPIO_OType_PP;
    G2.GPIO_Pin = GPIO_Pin_6;
    G2.GPIO_PuPd = GPIO_PuPd_NOPULL;
    G2.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA, &G2);

    G3.GPIO_Mode =  GPIO_Mode_AF;
        G3.GPIO_OType = GPIO_OType_PP;
        G3.GPIO_Pin = GPIO_Pin_7;
        G3.GPIO_PuPd = GPIO_PuPd_NOPULL;
        G3.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_Init(GPIOA, &G3);

        G4.GPIO_Mode =  GPIO_Mode_AF;
            G4.GPIO_OType = GPIO_OType_PP;
            G4.GPIO_Pin = GPIO_Pin_8;
            G4.GPIO_PuPd = GPIO_PuPd_NOPULL;
            G4.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_Init(GPIOC, &G4);


}

void TIMER4_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_4;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_4.TIM_Prescaler = 0;
    TIM_4.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_4.TIM_Period = 8399;
    TIM_4.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_4.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_4);
    TIM_Cmd(TIM4, ENABLE);
}

void TIMER3_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_3;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_3.TIM_Prescaler = 0;
    TIM_3.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_3.TIM_Period = 8399;
    TIM_3.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_3.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_3);
    TIM_Cmd(TIM3, ENABLE);
}


void EXTI9_5_IRQHandler(void)
{
	TIM_OCInitTypeDef TIM4_OCStruct;
		TIM_OCInitTypeDef TIM3_OCStruct;

		TIM4_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
		TIM4_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM4_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;



		TIM3_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM3_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM3_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;



	if((EXTI_GetITStatus(EXTI_Line5) != RESET)||(EXTI_GetITStatus(EXTI_Line6) != RESET)||(EXTI_GetITStatus(EXTI_Line8) != RESET))
	{
	 uint8_t x;
	 x=(1*GPIO_ReadInputDataBit (GPIOC,GPIO_Pin_5))+(2*GPIO_ReadInputDataBit (GPIOC,GPIO_Pin_6))+(4*GPIO_ReadInputDataBit (GPIOC,GPIO_Pin_8));
	 switch(x)
	 {


	 case 1:
		 TIM4_OCStruct.TIM_Pulse =4399;
		 TIM_OC1Init(TIM4, &TIM4_OCStruct);
		 TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 TIM4_OCStruct.TIM_Pulse = 0;
		 TIM_OC2Init(TIM4, &TIM4_OCStruct);
		 TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 TIM4_OCStruct.TIM_Pulse = 0;
		 TIM_OC3Init(TIM4, &TIM4_OCStruct);
		 TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

         TIM3_OCStruct.TIM_Pulse =0;
         TIM_OC1Init(TIM3, &TIM3_OCStruct);
         TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

         TIM3_OCStruct.TIM_Pulse =0;
         TIM_OC2Init(TIM3, &TIM3_OCStruct);
         TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

         TIM3_OCStruct.TIM_Pulse = 4399;
         TIM_OC3Init(TIM3, &TIM3_OCStruct);
         TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		 break;
	 case 2:
		 		 TIM4_OCStruct.TIM_Pulse =0;
		 		 TIM_OC1Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 TIM4_OCStruct.TIM_Pulse = 4399;
		 		 TIM_OC2Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 TIM4_OCStruct.TIM_Pulse = 0;
		 		 TIM_OC3Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =4399;
		          TIM_OC1Init(TIM3, &TIM3_OCStruct);
		          TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =0;
		          TIM_OC2Init(TIM3, &TIM3_OCStruct);
		          TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =0;
		          TIM_OC3Init(TIM3, &TIM3_OCStruct);
		          TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		 		 break;

	 case 3:
		 		 TIM4_OCStruct.TIM_Pulse =0;
		 		 TIM_OC1Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 TIM4_OCStruct.TIM_Pulse = 4399;
		 		 TIM_OC2Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 TIM4_OCStruct.TIM_Pulse = 0;
		 		 TIM_OC3Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =0;
		          TIM_OC1Init(TIM3, &TIM3_OCStruct);
		          TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =0;
		          TIM_OC2Init(TIM3, &TIM3_OCStruct);
		          TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =4399;
		          TIM_OC3Init(TIM3, &TIM3_OCStruct);
		          TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		 		 break;

	 case 4:
		 		 TIM4_OCStruct.TIM_Pulse =0;
		 		 TIM_OC1Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 TIM4_OCStruct.TIM_Pulse =0;
		 		 TIM_OC2Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 TIM4_OCStruct.TIM_Pulse = 4399;
		 		 TIM_OC3Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =0;
		          TIM_OC1Init(TIM3, &TIM3_OCStruct);
		          TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =4399;
		          TIM_OC2Init(TIM3, &TIM3_OCStruct);
		          TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =0;
		          TIM_OC3Init(TIM3, &TIM3_OCStruct);
		          TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		 		 break;


	 case 5:
		 		 TIM4_OCStruct.TIM_Pulse =4399;
		 		 TIM_OC1Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 TIM4_OCStruct.TIM_Pulse =0;
		 		 TIM_OC2Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 TIM4_OCStruct.TIM_Pulse =0;
		 		 TIM_OC3Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =0;
		          TIM_OC1Init(TIM3, &TIM3_OCStruct);
		          TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =4399;
		          TIM_OC2Init(TIM3, &TIM3_OCStruct);
		          TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =0;
		          TIM_OC3Init(TIM3, &TIM3_OCStruct);
		          TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		 		 break;


	 case 6:
		 		 TIM4_OCStruct.TIM_Pulse =0;
		 		 TIM_OC1Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 TIM4_OCStruct.TIM_Pulse = 0;
		 		 TIM_OC2Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 TIM4_OCStruct.TIM_Pulse = 4399;
		 		 TIM_OC3Init(TIM4, &TIM4_OCStruct);
		 		 TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =4399;
		          TIM_OC1Init(TIM3, &TIM3_OCStruct);
		          TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =0;
		          TIM_OC2Init(TIM3, &TIM3_OCStruct);
		          TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

		          TIM3_OCStruct.TIM_Pulse =0;
		          TIM_OC3Init(TIM3, &TIM3_OCStruct);
		          TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		 		 break;


	 default:

		 	 	 	 	 TIM4_OCStruct.TIM_Pulse =0;
		 		 		 TIM_OC1Init(TIM4, &TIM4_OCStruct);
		 		 		 TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 		 TIM4_OCStruct.TIM_Pulse = 0;
		 		 		 TIM_OC2Init(TIM4, &TIM4_OCStruct);
		 		 		 TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		 		 TIM4_OCStruct.TIM_Pulse = 0;
		 		 		 TIM_OC3Init(TIM4, &TIM4_OCStruct);
		 		 		 TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

		 		          TIM3_OCStruct.TIM_Pulse =0;
		 		          TIM_OC1Init(TIM3, &TIM3_OCStruct);
		 		          TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

		 		          TIM3_OCStruct.TIM_Pulse =0;
		 		          TIM_OC2Init(TIM3, &TIM3_OCStruct);
		 		          TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

		 		          TIM3_OCStruct.TIM_Pulse =0;
		 		          TIM_OC3Init(TIM3, &TIM3_OCStruct);
		 		          TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		 		 		 break;


	 }

	}
	 EXTI_ClearITPendingBit(EXTI_Line5);
	 EXTI_ClearITPendingBit(EXTI_Line6);
	 EXTI_ClearITPendingBit(EXTI_Line7);
}


int main(void)
{
	Configure_PINS();
	TIMER4_Init();
	TIMER3_Init();
    while(1)
    {

    }
}
