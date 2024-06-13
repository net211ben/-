# 94-101
main_loop:                      //主循环标签（开头）
//（2.1）主循环次数变量mMainLoopCount+1
		ldr r2,=mMainLoopCount     //r2←mMainLoopCount的地址
		ldr r1, [r2]
		add r1,#1
		str r1,[r2]	
//（2.2）未达到主循环次数设定值，继续循环
    ldr r2,=MainLoopNUM
		cmp r1,r2
		blO  main_loop     //未达到，继续循环
//（2.3）达到主循环次数设定值，执行下列语句，进行灯的亮暗处理

//测试代码部分[理解机器码存储]

void main_loop(int& mMainLoopCount, int MainLoopNUM)
{
  int r1 = mMainLoopCount;
  while(r1<MainLoopNum)
  {
    r1 += 1;
    mMainLoopCount = r1;
  }
}
