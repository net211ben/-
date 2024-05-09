### 1  UART_2初始化
uart_init(UART_User,115200);                    //初始化串口模块
初始化串口号和波特率

### 2  115200波特率，72MHz，BRR值
当OVER8=0  1001110001
当OVER8=1  10011100001

### 3  中断向量表在startup_stm321431rxtx.s,有99项
g_pfnVectors:
	.word	_estack
	.word	Reset_Handler
	.word	NMI_Handler
	.word	HardFault_Handler
	.word	MemManage_Handler
	.word	BusFault_Handler
	.word	UsageFault_Handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SVC_Handler
	.word	DebugMon_Handler
	.word	0
	.word	PendSV_Handler
	.word	SysTick_Handler
	.word	WWDG_IRQHandler
	.word	PVD_PVM_IRQHandler
	.word	TAMP_STAMP_IRQHandler
	.word	RTC_WKUP_IRQHandler
	.word	FLASH_IRQHandler
	.word	RCC_IRQHandler
	.word	EXTI0_IRQHandler
	.word	EXTI1_IRQHandler
	.word	EXTI2_IRQHandler
	.word	EXTI3_IRQHandler
	.word	EXTI4_IRQHandler
	.word	DMA1_Channel1_IRQHandler
	.word	DMA1_Channel2_IRQHandler
	.word	DMA1_Channel3_IRQHandler
	.word	DMA1_Channel4_IRQHandler
	.word	DMA1_Channel5_IRQHandler
	.word	DMA1_Channel6_IRQHandler
	.word	DMA1_Channel7_IRQHandler
	.word	ADC1_IRQHandler
	.word	CAN1_TX_IRQHandler
	.word	CAN1_RX0_IRQHandler
	.word	CAN1_RX1_IRQHandler
	.word	CAN1_SCE_IRQHandler
	.word	EXTI9_5_IRQHandler
	.word	TIM1_BRK_TIM15_IRQHandler
	.word	TIM1_UP_TIM16_IRQHandler
	.word	TIM1_TRG_COM_IRQHandler
	.word	TIM1_CC_IRQHandler
	.word	TIM2_IRQHandler
	.word	0
	.word	0
	.word	I2C1_EV_IRQHandler
	.word	I2C1_ER_IRQHandler
	.word	I2C2_EV_IRQHandler
	.word	I2C2_ER_IRQHandler
	.word	SPI1_IRQHandler
	.word	SPI2_IRQHandler
	.word	USART1_IRQHandler
	.word	USART2_IRQHandler
	.word	USART3_IRQHandler
	.word	EXTI15_10_IRQHandler
	.word	RTC_Alarm_IRQHandler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SDMMC1_IRQHandler
	.word	0
	.word	SPI3_IRQHandler
	.word	0
	.word	0
	.word	TIM6_DAC_IRQHandler
	.word	TIM7_IRQHandler
	.word	DMA2_Channel1_IRQHandler
	.word	DMA2_Channel2_IRQHandler
	.word	DMA2_Channel3_IRQHandler
	.word	DMA2_Channel4_IRQHandler
	.word	DMA2_Channel5_IRQHandler
	.word	0
	.word	0
	.word	0
	.word	COMP_IRQHandler
	.word	LPTIM1_IRQHandler
	.word	LPTIM2_IRQHandler
	.word	0
	.word	DMA2_Channel6_IRQHandler
	.word	DMA2_Channel7_IRQHandler
	.word	LPUART1_IRQHandler
	.word	QUADSPI_IRQHandler
	.word	I2C3_EV_IRQHandler
	.word	I2C3_ER_IRQHandler
	.word	SAI1_IRQHandler
	.word	0
	.word	SWPMI1_IRQHandler
	.word	TSC_IRQHandler
	.word	0
	.word	0
	.word	RNG_IRQHandler
	.word	FPU_IRQHandler
	.word	CRS_IRQHandler

 ### 4  TIM6
 IRQn=54
 NVIC->ISER[1] = 0x400000

 ### 5
UART_User_Handler中断处理函数
void UART_User_Handler(void)
{
	//【1】声明局部变量
	uint8_t ch;
	uint8_t flag;
    //【2】关总中断
	DISABLE_INTERRUPTS; 
	//【3】读取接到的一个字节
	ch=uart_re1(UART_User,&flag);  //调用接收一个字节的函数，清接收中断位
	//【4】根据flag判断是否真正收到一个字节的数据
	if(flag)                        //有数据
	{
		ch=ch+2;
		uart_send1(UART_User,ch);  //回发接收到的字节
	}
	//【5】开总中断
	ENABLE_INTERRUPTS;   
	
 }
 
未交换前运行结果
![image](https://github.com/net211ben/-/assets/93826955/237aaebd-1783-48e6-8620-b1e37f347592)

交换UART_2和TIM6在中断向量表的位置和IRQ号
![image](https://github.com/net211ben/-/assets/93826955/1b5417dd-828f-4e6f-8338-907e587c978f)

交换后运行结果
![image](https://github.com/net211ben/-/assets/93826955/79fcd8dc-af8c-4dd5-a0a4-21eae5448e39)





