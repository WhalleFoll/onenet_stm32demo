/*-------------------------------------------------------------------------------
�ļ����ƣ�usart.c
�ļ�������adc�⺯��
Ӳ��ƽ̨����ĪM3S������
           ----------------------------------------------------
          |                                                    |
          | PC1 - ADC1 �����ⲿ��ѹ(ͨ��һ��������������ѹ)|
          |                                                    |
           ----------------------------------------------------
��д����shifang
�̼���  ��V3.5
������̳��www.doflye.net
��    ע��ͨ�����޸Ŀ�����ֲ�����������壬����������Դ�����硣
---------------------------------------------------------------------------------*/

#include "adc.h"


/*����DMA��ADC��ͨ���ɼ�*/

volatile u16 ADCConvertedValue[10][3];//�������ADCת�������Ҳ��DMA��Ŀ���ַ,3ͨ����ÿͨ���ɼ�10�κ���ȡƽ����
         
void Dma_Init(void)
{

    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//ʹ��ʱ��

    DMA_DeInit(DMA1_Channel1);    //��ͨ��һ�Ĵ�����ΪĬ��ֵ
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);//�ò������Զ���DMA�������ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;//�ò������Զ���DMA�ڴ����ַ(ת���������ĵ�ַ)
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//�ò����涨����������Ϊ���ݴ����Ŀ�ĵػ�����Դ���˴�����Ϊ��Դ
    DMA_InitStructure.DMA_BufferSize = 3*10;//����ָ��DMAͨ����DMA����Ĵ�С,��λΪ���ݵ�λ������Ҳ����ADCConvertedValue�Ĵ�С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�趨�����ַ�Ĵ����������,�˴���Ϊ���� Disable
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�����趨�ڴ��ַ�Ĵ����������,�˴���Ϊ������Enable
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���ݿ��Ϊ16λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���ݿ��Ϊ16λ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //������ѭ������ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMAͨ��ӵ�и����ȼ� �ֱ�4���ȼ� �͡��С��ߡ��ǳ���
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//ʹ��DMAͨ�����ڴ浽�ڴ洫��
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);//����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��

    DMA_Cmd(DMA1_Channel1, ENABLE);//����DMAͨ��һ
}

void Adc_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    /*3��IO�ڵ����ã�PA0��PA1��PA2��*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /*IO��ADCʹ��ʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //����ת��
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 3;
    ADC_Init(ADC1, &ADC_InitStructure);
    
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);//ͨ��һת��������浽ADCConvertedValue[0~10][0]
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_239Cycles5);//ͨ����ת��������浽ADCConvertedValue[0~10][1]
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_239Cycles5);//ͨ����ת��������浽ADCConvertedValue[0~10][2]

	  
    ADC_DMACmd(ADC1, ENABLE);//����ADC��DMA֧��
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));

}

void ADC_dma_init(void)
{
	 Dma_Init();
	 Adc_Init();
	 ADC_SoftwareStartConvCmd(ADC1, ENABLE);//��ʼ�ɼ�
}

void adc_data(void)
{
 int sum;
	u8 i,j;
	float ADC_Value[3];//�������澭��ת���õ��ĵ�ѹֵ
	for(i=0;i<3;i++)
		{
			sum=0;
			for(j=0;j<10;j++)
			{
				sum+=ADCConvertedValue[j][i];
			}
			ADC_Value[i]=(float)sum/(10*4096)*3.3;//��ƽ��ֵ��ת���ɵ�ѹֵ
			//��ӡ���ԣ�
			//UsartPrintf(USART_DEBUG, "\r\n ͨ�� %d -ADC�ɼ� = %f V\r\n",i,ADC_Value[i]);
		}
		//��ʱ���ԣ�
}
