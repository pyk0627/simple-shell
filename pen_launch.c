//pen_launch.c
#include "pen.h"
int pen_launch(char **args)
{
	pid_t pid,wpid;//process id type
	//进程id类型的变量
	int status;

	pid = fork();//创建一个子进程
	if(pid==0)//如果当前的进程是子进程
	{
		if(execvp(args[0],args)==-1)//执行另一个程序
		{
			perror("pen");
		}
		exit(EXIT_FAILURE);
	}else if(pid<0)//如果子进程创建失败
	{
		perror("pen");
	}else
	{
		do
		{
			wpid=waitpid(pid,&status,WUNTRACED);//等待未被追踪但被暂停的子进程
		}while(!WIFEXITED(status)&&!WIFSIGNALED(status));
		//Wait If Exited,子进程是否正常退出了？
		//Wait If Signaled，子进程是否被信号终止了？
	}
	return 1;//1代表shell可以继续运行
}