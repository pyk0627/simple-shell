//main.c
#include "pen.h"
int main(int argc,char **argv)
{
	//Load config file, if any.

	//Run command loop
	pen_loop();//终端的循环

	//Perform any shutdown/cleanup

	return EXIT_SUCCESS;
}