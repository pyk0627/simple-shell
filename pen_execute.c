//pen_execute.c
#include "pen.h"
int pen_execute(char **args)
{
	int i;
	if(args[0]==NULL)
	{
		return 1;
	}

	for(int i=0;i<pen_num_builtins();i++)
	{
		if(strcmp(args[0],builtin_str[i])==0)
		{
			return (*builtin_func[i])(args);
		}
	}
	return pen_launch(args);
}