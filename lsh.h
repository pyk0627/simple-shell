#ifndef LSH_H
#define LSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int lsh_execute(char **args);
int lsh_launch(char**args);
void lsh_loop(void);
char *lsh_read_line(void);
char **lsh_split_line(char *line);
int lsh_cd(char **args);
int ls_help(char **args);
int lsh_exit(char **args);
int lsh_num_builtins(void);

extern char *builtin_str[];
extern int (*builtin_func[])(char **);

#endif