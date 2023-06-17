#include "stm32f10x.h"                  // Device header
//#include "LED.h"
#include "Servo.h"

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_55Cycles5);
	//规则组初始化
	
		
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET);




    ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_Channel_3);
	ADC_AnalogWatchdogThresholdsConfig(ADC1,4095,1500);
	ADC_AnalogWatchdogCmd(ADC1,ADC_AnalogWatchdog_SingleRegEnable);
	ADC_ITConfig(ADC1,ADC_IT_AWD,ENABLE);

    NVIC_InitTypeDef nvic_struct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	nvic_struct.NVIC_IRQChannel = ADC1_2_IRQn;
	nvic_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_struct.NVIC_IRQChannelPreemptionPriority = 3;
	nvic_struct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&nvic_struct);

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
}

uint16_t AD_GetValue(void)
{
	return ADC_GetConversionValue(ADC1);
}


void ADC1_2_IRQHandler(void)
{
	if(ADC_GetITStatus(ADC1,ADC_IT_AWD) == 1)
	{
        //LED2_OFF();
        Servo_SetAngle(180);
        ADC_ClearITPendingBit(ADC1,ADC_IT_AWD);
	}   
}
