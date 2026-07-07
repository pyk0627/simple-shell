void lsh_loop(void)
{
	char *line;
	char **args;
	int status;

	do
	{
		printf("> ");
		line = lsh_read();
		args = lsh_split_line(line);
		status = lsh_execute(args);

		free(line);
		free(args);
		free(status);
	}while(status);
}