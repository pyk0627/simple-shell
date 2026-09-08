#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


#define PSH_TOK_DELIM " \t\n"
#define PSH_TOK_BUFSIZE 64
#define PSH_RL_BUFSIZE 1024
//所有函数的声明
int psh_launch(char **args);
int psh_num_builtins();
int psh_cd(char **args);
int psh_help(char **args);
int psh_exit(char **args);
int psh_execute(char **args);
char** psh_split_line(char *line);
char* psh_read_line();
void psh_loop(void);

int psh_launch(char **args)
{
	//pid type，用来存储进程id的
	//pid,wpid是自己命名的变量
	//pid用来接受fork()的返回值
	//也就是子进程的id
	//wpid接受waitpid()的返回值
	//也就是这个状态发生变化的子进程编号
	pid_t pid,wpid;

	int status;

	//以下执行的代码会复制到另一个进程中
	pid=fork();

	//如果是子进程
	if(pid==0)
	{
		//execvp,将当前进程换魂
		//换成args[0]函数
		//参数是args
		//如果换魂成功，该函数永不返回
		//如果返回说明调用失败
		if(execvp(args[0],args)==-1)
		{
			perror("psh");
		}
		exit(EXIT_FAILURE);
	//如果子进程创建失败
	}else if(pid<0)
	{
		perror("psh");
	//如果当前进程是父进程
	}else
	{
		do
		{

			//等待子进程pid
			//用status接受子进程的状态
			//WUNTRACED选项表示
			//如果子进程未被追踪
			//但被暂停
			//waitpid也会立即返回
			wpid=waitpid(pid,&status,WUNTRACED);
		//如果子进程没有被退出而且
		//没有被信号终止
		//则继续循环
		}while(!WIFEXITED(status)&&
		       !WIFSIGNALED(status));
	}
	return 1;
}

//创建一个名字是builtin_str的数组
//存储的数据类型是指向char类型的指针
char *builtin_str[]={
	"cd",
	"help",
	"exit"
};

//builtin_func是一个数组，元素是指针
//指向的是接受char**类型
//返回int类型的函数
int (*builtin_func[])(char **)=
{
	&psh_cd,
	&psh_help,
	&psh_exit
};

int psh_num_builtins()
{
	return sizeof(builtin_str)/sizeof(builtin_str[0]);
}

int psh_cd(char **args)
{
	//args[0]是cd
	//args[1]才是参数
	if(args[1]==NULL)
	{
		fprintf(stderr,
			"pen:expected argument to \"cd\"\n");
	}else
	{
		//chdir，改表路径
		//函数执行成功，返回0
		if(chdir(args[1])!=0)
		{
			perror("pen");
		}
	}
	
	//psh_cd 执行成功
	return 1;
}

int psh_help(char **args)
{
	int i;
	printf("pyk`s simple-shell\n");
	printf("输入命令名和参数回车。\n");
	printf("下面是内置的命令:\n");

	for(i=0;i<psh_num_builtins();i++)
	{
		printf("%s\n",builtin_str[i]);
	}

	return 1;
}

int psh_exit(char **args)
{
	return 0;
}

int psh_execute(char **args)
{
	int i;
	//如果用户什么也没有输入
	//直接按空格或者回车
	//则继续循环
	if(args[0]==NULL)
	{
		return 1;
	}

	for(int i=0;i<psh_num_builtins();i++)
	{
		//比较输入的命令和内置命令是否相等
		if(strcmp(args[0],builtin_str[i])==0)
		{
			return (*builtin_func[i])(args);
		}
	}
	return psh_launch(args);
}

char** psh_split_line(char *line)
{
	//分配存储分解结果的空间
	int bufsize=PSH_TOK_BUFSIZE;
	int position=0;
	
	//相当于创建了一个二维数组
	//每个一维数组存储的就是指向char类型数据的地址
	//所以用char*来分配内存大小
	char **tokens=malloc(sizeof(char*)*bufsize);
	
	//用来存储每次分解的单个结果
	char *token;

	if(!tokens)
	{
		fprintf(stderr,"psh:allocation error\n");
		exit(EXIT_FAILURE);
	}

	//根据PSH_TOK_DELIM来分解line
	token=strtok(line,PSH_TOK_DELIM);

	//strtok返回null表示没有单词了
	while(token!=NULL)
	{
		tokens[position]=token;
		position++;

		if(position>=bufsize)
		{
			bufsize+=PSH_TOK_BUFSIZE;
			tokens=realloc(tokens,
				       sizeof(char*)*bufsize);

			if(!tokens)
			{
				fprintf(stderr,
					"psh:allocation error\n"
					);
				exit(EXIT_FAILURE);
			}
		}
		//第二次传入NULL，上次切的地方继续往后切
		token=strtok(NULL,PSH_TOK_DELIM);
	}
	tokens[position]=NULL;
	return tokens;
}
char* psh_read_line()
{
	int bufsize = PSH_RL_BUFSIZE;
	//当前读取的位置
	int position = 0;
	//申请内存成功的话，malloc会返回地址值
	//失败的话，会返回0
	char *buffer=malloc(sizeof(char)*bufsize);

	//保存读取的结果
	int c;

	if(!buffer)
	{
		//file print format
		fprintf(stderr,"psh:allocation error\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		//读取到的ascll编码
		c=getchar();

		//EOF等价与数据可读了
		if(c==EOF || c=='\n')
		{
			buffer[position]='\0';
			return buffer;
		}else
		{
			buffer[position]=c;
		}
		position++;
		
		//如果缓存区用满了
		if(position>=bufsize)
		{
			bufsize+=PSH_RL_BUFSIZE;
			buffer=realloc(buffer,bufsize);

			if(!buffer)
			{
				fprintf(stderr,
					"psh:allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

//终端的运行是一个循环
void psh_loop(void)
{
	//存储用户的输入
	char *line;
	//存储用户输入的分解
	char **args;
	//存储执行的状态
	int status;

	do
	{
		printf("psh> ");
		//接收用户输入
		line=psh_read_line();
		//处理用户输入
		args=psh_split_line(line);
		//执行用户输入
		status=psh_execute(args);

		//释放之前申请的内存
		free(line);
		free(args);
	}while(status);
}
int main(int argc,char **argv)
{
	//运行终端的循环
	psh_loop();

	//返回退出的状态
	//0表示正常结束，非0表示出错
	return EXIT_SUCCESS;
}
