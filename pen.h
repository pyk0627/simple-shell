#ifndef PEN_H
#define PEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int pen_execute(char **args);
int pen_launch(char**args);
void pen_loop(void);
char *pen_read_line(void);
char **pen_split_line(char *line);
int pen_cd(char **args);
int ls_help(char **args);
int pen_exit(char **args);
int pen_num_builtins(void);

extern char *builtin_str[];
extern int (*builtin_func[])(char **);

#endif
