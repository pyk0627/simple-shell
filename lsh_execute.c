//lsh_execute.c
#include "lsh.h"
int lsh_execute(char **args)
{
	int i;
	if(args[0]==NULL)
	{
		return 1;
	}

	for(int i=0;i<lsh_num_builtins();i++)
	{
		if(strcmp(args[0],builtin_str[i])==0)
		{
			return (*builtin_func[i])(args);
		}
	}
	return lsh_launch(args);
}