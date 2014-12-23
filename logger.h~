#ifndef __LOG__
#define __LOG__

#include<malloc.h>
#include<stdio.h>

#ifdef WIN32
//brief  support WIN32 
#include<windows.h>

#include<winuser.h>

#endif

#define DEBUG 1

#ifdef _LINUX
//brief support LINUX

#include<pthread.h>

#endif

#define MAX_NUM 100


struct logstr
{
  struct logstr *next;
  char *log;
  int n;
};

struct log_interface
{
  int log_num;
  struct logstr *que;
  int void_flag;
  FILE* file;
  int freq_ms;
  int i_pos;
  int i_pos_p;
};

typedef  struct log_interface logfile;

int open_log( char *path);

int write_log();

int start_log();

int clean_log( char *path);

int stop_log();

int queue_in(char *buf);

extern logfile routes;

#endif
