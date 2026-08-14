#define LSH_TOK_BUFSIZE 64//参数的缓冲区大小
#define LSH_TOK_DELIM " \t\r\n\a"//分隔符
char **lsh_split_line(char *line)//接受一行内容，返回参数的数组首地址
{
	int bufsize=LSH_TOK_BUFSIZE;//初始化参数缓冲区大小
	char **tokens = malloc(sizeof(char*)*bufsize);//为二维数组分配内存
	char *token;

	if(!tokens)
	{
		fprintf(stderr,"lsh:allocation error\n");
		exit(EXIT_FAILURE);
	}

	token=strtok(line,LSH_TOK_DELIM);//得到第一个参数
	while(token!=NULL)
	{
		tokens[position]=token;
		position++;

		if(position>=bufsize)
		{
			bufsize+=LSH_TOK_BUFSIZE;
			tokens=realloc(tokens,buffsize*sizeof(char*));
			//tokens中的元素是char*
			if(!tokens)
			{
				fprintf(stderr,"lsh:allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token=strtok(line,LSH_TOK_DELIM);
	}
	tokens[position]=NULL;
	return tokens;
}