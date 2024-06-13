#define GLOBLE_VAR
#include "includes.h"      //包含总头文件

//----------------------------------------------------------------------
//声明使用到的内部函数
//main.c使用的内部函数声明处
void Delay_ms(uint16_t u16ms);
float Regression_Ext_Temp(uint16_t tmpAD);      //环境温度AD值转为实际温度
float Regression_MCU_Temp(uint16_t mcu_temp_AD); //MCU温度AD值转为实际温度

//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程，参见书稿）
int main(void)
{	
	float a15=0,a17=0;
	uint16_t d15=0,d17=0;
	adc_init(15,AD_SINGLE);
	adc_init(17,AD_SINGLE);
	while(1)
	{
		Delay_ms(2000);
		d15=adc_read(15);
		Delay_ms(100);
		d17=adc_read(17);
		a15=tempRegression(d15);
		a17=adc_mcu_temp(d17);
		printf("温度AD值%d：",d15);
		printf("温度为%6.2f：",a15);
		printf("芯片AD值%d：",d17);
		printf("芯片温度为%6.2f：\n",a17);
	}
}
