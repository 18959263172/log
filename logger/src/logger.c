/**file logger.c the inplement of this module
*
*
*/
#include"logger.h"

#ifdef WIN32
CRITICAL_SECTION g_cs;

#endif

logfile routes;

int open_log(char *buf)
{
  if(routes.file=fopen(buf,"a+"))
    {
      
    }
  else
    {
      printf("error open file \r\n");
	}
  return 1;
}

int write_log()
{
  if(routes.void_flag)
    {
      return 0;
    }
  else
    {
      if(fputs("hello world \r\n\0",routes.file)==0)
	{
	  EnterCriticalSection(&g_cs);
	  routes.void_flag=1;
	  return 1;
	  LeaveCriticalSection(&g_cs);
	}
      else return 0;
    }
}

int clean_log( char * buf)
{
  if(!remove(buf))
    return 1;
  return 0; 
}  

#ifdef WIN32



HANDLE handle;

void CALLBACK  TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{
  if(write_log())
  {
#if DEBUG
	  printf("open data ok! \r\n");
#endif
  }
  else
  {
#if DEBUG
    printf("write data error \r\n");
#endif
    
  }
}

//brief not use MFC you can use this for console 
#ifndef __AFX_H__
DWORD WINAPI Fun(LPVOID lpParamter)
{
  BOOL bRet;
  MSG msg;
  int x;
  int timerid = SetTimer(NULL,111,3000,TimerProc);
  if(routes.freq_ms>0)
    {
      if(SetTimer(NULL,10,routes.freq_ms,&TimerProc))
	x=-1;
    }
  PeekMessage(&msg,NULL,WM_USER,WM_USER,PM_NOREMOVE);
  while ((bRet = GetMessage(&msg,NULL,0,0))!=0)
    {
      if (bRet == -1)
	{
	  printf("Error:the thread will quit,error id is %d/n",GetLastError());
	  break;
	}
      else
	{
	  TranslateMessage(&msg);
	  DispatchMessage(&msg);
	}
    }
  KillTimer(NULL,timerid);
  printf("thread end here/n");
  return 0;
}
#else
//USE MFC,you can attach the interface to the WINDOW's callback function
//in MFC you should add a callback function on message WM_TIMER

#endif

#endif

int start_log()
{
#ifdef WIN32 
  
  routes.stdbuf=(struct log_interface*)malloc(sizeof(struct log_interface)*MAX_NUM);

  InitializeCriticalSection(&g_cs);
  
  handle = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
  
  WaitForSingleObject(handle, INFINITE);

  //brief wait until the thread is end
  return 0;
  
#endif
}


int stop_log()
{
  CloseHandle(handle);
}

int queue_in()
{
  EnterCriticalSection(&g_cs);
  
  
  LeaveCriticalSection(&g_cs);
}
