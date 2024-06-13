#define GLOBLE_VAR
#include "includes.h"      //包含总头文件

//----------------------------------------------------------------------
//声明使用到的内部函数
//main.c使用的内部函数声明处

//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程，参见书稿）

int main(void)
{
	vuint32_t mMainLoopCount;  //主循环次数变量
	uint32_t localMsgID;
	uint32_t txMsgID;
	uint32_t BitRate;
	mMainLoopCount=0;    //主循环次数变量
	localMsgID = 0x0BU;
	txMsgID = 0x0AU;
	BitRate = 36;
	
	DISABLE_INTERRUPTS;
	emuart_init(UART_User,115200);
    uart_init(UART_3,115200);
    //【***CAN模块初始化***】
    can_init(CAN_1,localMsgID,BitRate);
    //（1.6）使能模块中断
    uart_enable_re_int(UART_User);
    uart_enable_re_int(UART_3);
    //【***使能CAN模块中断***】
    can_enable_recv_int(CAN_1);
    //（1.7）【不变】开总中断
	ENABLE_INTERRUPTS;
	while(1)
	{
		mMainLoopCount++;
        //（2.2）未达到主循环次数设定值，继续循环
		if (mMainLoopCount<=12889000)  continue;
		//（2.3）达到主循环次数设定值，执行下列语句，进行灯的亮暗处理
		//（2.3.1）清除循环次数变量
		mMainLoopCount=0;
		//【***CAN模块发送一帧数据***】
		if(can_send(CAN_1, txMsgID, 20, (uint8_t*)"陈泽豪") != 0) printf("failed\r\n");
	}
}
