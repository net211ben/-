    //（1.5）用户外设模块初始化
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);	//初始化蓝灯
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);	//初始化绿灯
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);	//初始化红灯
......

//（2）======主循环部分（开头）========================================
    for(;;)   //for(;;)（开头）
    { 
        for(int i=0;i<3000000;i++);//定义3000000次循环为一秒
        mCount++;//记录当前时间
        if(mCount==14){mCount=0;}//每到40秒就置零，一个循环
        
        /*
        time(s)	--------------
        red			--------
        green		    ------  --
        blue		--    ------  
        */
        if(mCount==0)
        {
           gpio_set(LIGHT_RED,LIGHT_ON);
           gpio_set(LIGHT_BLUE,LIGHT_ON);
           gpio_set(LIGHT_GREEN,LIGHT_OFF);
        }
        if(mCount==2)
        {
           gpio_set(LIGHT_BLUE,LIGHT_OFF);
        }
        if(mCount==4)
        {
           gpio_set(LIGHT_GREEN,LIGHT_ON);
        }
        if(mCount==6)
        {
           gpio_set(LIGHT_BLUE,LIGHT_ON);
        }
        if(mCount==8)
        {
           gpio_set(LIGHT_RED,LIGHT_OFF);
        }
        if(mCount==10)
        {
           gpio_set(LIGHT_GREEN,LIGHT_OFF);
        }
        if(mCount==12)
        {
        	gpio_set(LIGHT_GREEN,LIGHT_ON);
			gpio_set(LIGHT_BLUE,LIGHT_OFF);
        }
        
    }
