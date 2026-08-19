//pen_split_line.c
#include "pen.h"
#define PEN_TOK_BUFSIZE 64//参数的缓冲区大小
#define PEN_TOK_DELIM " \t\r\n\a"//分隔符
char **pen_split_line(char *line)//接受一行内容，返回参数的数组首地址
{
	int bufsize=PEN_TOK_BUFSIZE;//初始化参数缓冲区大小
	int position=0;
	char **tokens = malloc(sizeof(char*)*bufsize);//为二维数组分配内存
	char *token;

	if(!tokens)
	{
		fprintf(stderr,"pen:allocation error\n");
		exit(EXIT_FAILURE);
	}

	token=strtok(line,PEN_TOK_DELIM);//得到第一个参数
	while(token!=NULL)
	{
		tokens[position]=token;
		position++;

		if(position>=bufsize)
		{
			bufsize+=PEN_TOK_BUFSIZE;
			tokens=realloc(tokens,bufsize*sizeof(char*));
			//tokens中的元素是char*
			if(!tokens)
			{
				fprintf(stderr,"pen:allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token=strtok(NULL,PEN_TOK_DELIM);
	}
	tokens[position]=NULL;
	return tokens;
}