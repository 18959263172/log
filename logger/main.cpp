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

	open_log("d:\\test.log");
	
	routes.freq_ms=200;

	init_que();

	queue_in("hfffh\r\n\0");

	queue_in("fff\r\n\0");

	queue_in("ffffirst\r\n\0");

	start_log();
		
	return 1;
}
