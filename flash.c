int main(void)
{
	uint8_t str_r[20], str_w[20]="chenzehao";
	flash_init();
	flash_erase(50);//32106200014
	printf("擦除数据\n");
	flash_write(50,0,10, str_w);
	flash_read_logic(str_r,50,0,20);
	printf("%s\n",str_r);
	printf("---------------------------\n");
	printf("没有擦除数据\n");
	//假如没有擦除便写入数据
	flash_write(50,0,20,str_w);
	flash_read_logic(str_r,50,0,20);
	printf("%s\n",str_r);
}
