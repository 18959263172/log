// logger.cpp : 定义控制台应用程序的入口点。
//
#include "project.h"

extern "C"
{
	#include"./src/logger.h"	
};

#include"string.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
	char *test="hello \r\n\0";

	open_log("d:\\test.log");
	
	routes.void_flag=0;

	routes.freq_ms=1000;

	routes.stdbuf=test;
	
	start_log();
		
	return 1;
}
