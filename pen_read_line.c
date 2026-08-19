//pen_read_line.c
#include "pen.h"
#define PEN_RL_BUFSIZE 1024//每次读取行的缓冲区大小
char *pen_read_line(void)//返回一个字符串
{
	int bufsize = PEN_RL_BUFSIZE;//初始化缓冲区大小
	int position = 0;//当前读取的位置
	char *buffer = malloc(sizeof(char) * bufsize);//申请成功会返回首地址否则返回空指针
	int c;//当前读取的结果

	if(!buffer)
	{
		fprintf(stderr,"lsh:allocation error\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		c=getchar();//得到当前读取结果的ascll编码

		if(c==EOF || c=='\n')//如果读取错误或者读取完毕
		{
			buffer[position]='\0';
			return buffer;
		}else
		{
			buffer[position]=c;//放进缓冲区
		}
		position++;

		if(position>=bufsize)
		{
			bufsize+=PEN_RL_BUFSIZE;
			buffer=realloc(buffer,bufsize);//把buffer的大小重新设置为bufsize
			//申请成功返回首地址，否者返回空指针
			if(!buffer)
			{
				fprintf(stderr,"pen:allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}