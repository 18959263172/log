#ifndef __LOG__
#define __LOG__

#include<stdio.h>

#ifdef WIN32
//brief  support WIN32 
#include<windows.h>

#include<winuser.h>

#endif

#ifdef _LINUX
//brief support LINUX

#include<pthread.h>

#endif

extern logfile interface;

typedef struct log_interface
{
  unsigned char *stdbuf;
  bool void_flag;
  FILE* file;
  int freq_ms;
}logfile;

bool open_log(unsigned char *path);

bool write_log();

bool start_log();

bool clean_log(unsigned char *path);

#endif
