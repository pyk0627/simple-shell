//pen_loop.c
#include "pen.h"
void pen_loop(void)
{
	char *line;//用来存储当前读取的这一行
	char **args;//存储把行分解后的结果
	int status;//当前的状态

	do
	{
		printf("> ");//打印一个标识符
		line = pen_read_line();//调用读取行的函数，并保存结果
		args = pen_split_line(line);//调用分解行的函数，并保存结果
		status = pen_execute(args);//对分解后的结果执行

		free(line);//
		free(args);
	}while(status);//状态正常时，持续运行
}