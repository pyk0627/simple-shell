//pen_t.c
#include "pen.h"
//三个函数的声明
int pen_cd(char **args);
int pen_help(char **args);
int pen_exit(char **args);

//内置命令名称
//名字为builtin_str的数组，元素类型是：char *
char *builtin_str[]=
{
	"cd",
	"help",
	"exit"
};

/*
builtin_func[]表示builtin_func是一个数组
*builtin_func[]表示builtin_func数组中元素是函数指针
指向的函数接受的参数类型是，char**
返回类型是int
*/
int (*builtin_func[])(char**)=
{
	&pen_cd,
	&pen_help,
	&pen_exit
};

//内置命令的数量
int pen_num_builtins()
{
	return sizeof(builtin_str)/sizeof(char *);
}

int pen_cd(char **args)
{
	if(args[1]==NULL)
	{
		//formatted print to file/stream
		//格式化打印到文件流/输出流
		fprintf(stderr,"pen:expected argument to \"cd\"\n");
	}else
	{
		if(chdir(args[1])!=0)
		{
			//print error
			//打印错误信息
			perror("pen");
		}
	}
	return 1;
}

int pen_help(char **args)
{
	int i;
	printf("pyk`s simple-shell\n");
	printf("输入程序名和参数然后回车。\n");
	printf("下面是内置的程序:\n");

	for(int i=0;i<pen_num_builtins();i++)
	{
		printf("	%s\n",builtin_str[i]);
	}

	//printf("");
	return 1;
}

int pen_exit(char **args)
{
	return 0;
}
