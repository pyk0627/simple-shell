//lsh_t.c
#include "lsh.h"
//三个函数的声明
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

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
	&lsh_cd,
	&lsh_help,
	&lsh_exit
};

//内置命令的数量
int lsh_num_builtins()
{
	return sizeof(builtin_str)/sizeof(char *);
}

int lsh_cd(char **args)
{
	if(args[1]==NULL)
	{
		//formatted print to file/stream
		//格式化打印到文件流/输出流
		fprintf(stderr,"lsh:expected argument to \"cd\"\n");
	}else
	{
		if(chdir(args[1])!=0)
		{
			//print error
			//打印错误信息
			perror("lsh");
		}
	}
	return 1;
}

int lsh_help(char **args)
{
	int i;
	printf("pyk`s simple-shell\n");
	printf("输入程序名和参数然后回车。\n");
	printf("下面是内置的程序:\n");

	for(int i=0;i<lsh_num_builtins();i++)
	{
		printf("	%s\n",builtin_str[i]);
	}

	//printf("");
	return 1;
}

int lsh_exit(char **args)
{
	return 0;
}
