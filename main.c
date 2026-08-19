//main.c
#include "pen.h"
int main(int argc,char **argv)
{
	//Load config file, if any.

	//Run command loop
	pen_loop();//终端的循环

	//Perform any shutdown/cleanup

	return EXIT_SUCCESS;
	/*EXIT_SUCCESS是c库中的宏定义
	 *0表示正常结束，success
	 *非0表示表示出错
	 * */
}
