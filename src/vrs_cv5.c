/*
 * vrs_cv5.c
 *
 *  Created on: 18. 10. 2016
 *      Author: Bálint
 */


#include "vrs_cv5.h"


extern uint16_t value;

void gpioInit(){
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

}

void delay(int pocet){
	int i=0;
	for(i;i<pocet;i++){}
}

void setFrek(uint16_t ADvalue){
	if(ADvalue<2200){
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
			delay(50000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			delay(50000);
	}
	else if(ADvalue<3200){
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
			delay(150000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			delay(150000);
	}
	else if(ADvalue<3600){
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
			delay(300000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			delay(300000);
	}
	else if(ADvalue<3800){
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
			delay(500000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			delay(500000);
		}
	else{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
	}
}

void adcInit(){

	ADC_InitTypeDef ADC_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the HSI oscillator */
	RCC_HSICmd(ENABLE);
	/* Check that HSI oscillator is ready */
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

	/* Initialize ADC structure */
	ADC_StructInit(&ADC_InitStructure);
	/* ADC1 configuration */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	/* ADCx regular channel8 configuration */

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_16Cycles);

	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);
	ADC_ITConfig(ADC1,ADC_IT_OVR,ENABLE);

	/*NVIC initialization*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitStructure.NVIC_IRQChannel=ADC1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);


	ADC_Cmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_ADONS)==RESET);
	ADC_SoftwareStartConv(ADC1);
}

void ADC1_IRQHandler(){		//nazov z startup_stm32l1xx_hd.s
	if(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC))
	{
		value = ADC_GetConversionValue(ADC1);
	}

	if(ADC_GetFlagStatus(ADC1,ADC_FLAG_OVR))
	{
		ADC_ClearFlag(ADC1,ADC_FLAG_OVR);
	}
}
