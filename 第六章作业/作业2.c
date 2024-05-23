# 1、构件方式
void UART_User_Handler(void)
{
	//【1】声明局部变量
	uint8_t ch;
	uint8_t flag;
    //【2】关总中断
	DISABLE_INTERRUPTS; 
	//【3】读取接到的一个字节
	//ch=uart_re1(UART_User,&flag);  //调用接收一个字节的函数，清接收中断位
	//【4】根据flag判断是否真正收到一个字节的数据
	if(flag)                        //有数据
	{		
		ch=ch+1;
		uart_send1(UART_User,ch);  //回发接收到的字节
		if(ch=='H')
			gpio_set(LIGHT_GREEN,LIGHT_ON);
		else if(ch=='S')
			gpio_set(LIGHT_RED,LIGHT_ON);
		else if(ch=='C')
			gpio_set(LIGHT_BLUE,LIGHT_ON);
		else
		{
			gpio_set(LIGHT_GREEN,LIGHT_OFF);	
			gpio_set(LIGHT_RED,LIGHT_OFF);	
			gpio_set(LIGHT_BLUE,LIGHT_OFF);	
		}		
	}
	//【5】开总中断
	ENABLE_INTERRUPTS;   	
 }


# 2、直接地址方式
     for(;;)
    {
    	//【1】声明局部变量
		uint8_t ch;
		uint8_t flag;
	    //【2】关总中断
		DISABLE_INTERRUPTS; 
		//【3】读取接到的一个字节
		//ch=uart_re1(UART_User,&flag);  //调用接收一个字节的函数，清接收中断位
		uint32_t t;
		for (t = 0; t < 0xFBBB; t++)//查询指定次数
		{
			//判断接收缓冲区是否满
			if (*uart_isr & USART_ISR_RXNE_Msk)
			{
				ch=*uart_rdr;    //获取数据,清接收中断位
				flag = 1;  //接收成功
				break;
			}
		}//end for
		if(t >= 0xFBBB)
		{
			ch = 0xFF;
			flag = 0;    //未收到数据
		}
		
		
		//【4】根据flag判断是否真正收到一个字节的数据
		if(flag)                        //有数据
		{		
			ch=ch+1;
			//uart_send1(UART_User,ch);  //回发接收到的字节
			for (uint32_t t = 0; t < 0xFBBB; t++)//查询指定次数
			{
				//发送缓冲区为空则发送数据
				if ( *uart_isr & USART_ISR_TXE_Msk )
				{
					*uart_tdr = ch;
					break;
				}
			}//end for
			
			
			if(ch=='H')
				gpio_set(LIGHT_GREEN,LIGHT_ON);
			else if(ch=='S')
				gpio_set(LIGHT_RED,LIGHT_ON);
			else if(ch=='C')
				gpio_set(LIGHT_BLUE,LIGHT_ON);
			else
			{
				gpio_set(LIGHT_GREEN,LIGHT_OFF);	
				gpio_set(LIGHT_RED,LIGHT_OFF);	
				gpio_set(LIGHT_BLUE,LIGHT_OFF);	
			}
				
		}
		//【5】开总中断
		ENABLE_INTERRUPTS; 
    }
