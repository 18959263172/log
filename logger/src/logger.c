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
  if(routes.file=fopen(buf,"a"))
    {
      fseek(routes.file,0,SEEK_SET);
    }
  else
    {
      printf("error open file \r\n");
	}
  return 1;
}

int write_log()
{
	struct logstr *garbage ;

	if(routes.que!=NULL)
	{
	  if(fputs(routes.que->log,routes.file)!=EOF)
	  {
		fflush(routes.file);
#ifdef WIN32
	  EnterCriticalSection(&g_cs);
	  routes.void_flag=1;
	  garbage=routes.que;	 
	  routes.que=routes.que->next;
	  free(garbage);
	  LeaveCriticalSection(&g_cs);
	  //go out queue 
	  return 1;
	  }
	  else
	{
		//fclose(routes.file);
		return 0;
	}
#endif

#ifdef _LINUX
	  
#endif
	}
      else
	{
#ifdef WIN32
	return 0;
#endif
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
  int timerid ;
  if(routes.freq_ms>0)
    {
      if(timerid=SetTimer(NULL,1000,routes.freq_ms,&TimerProc))
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

int queue_in(char *c_str)
{
  struct logstr *ins,*prev;
#ifdef WIN32
  
  EnterCriticalSection(&g_cs);
  
  ins=routes.que;

  while(ins->next!=NULL)
  {
	ins=ins->next;
  }
  prev=ins;

  ins->next=(struct logstr* )malloc(sizeof(struct logstr));
  
  ins=ins->next;

  ins->prev=prev;
  
  ins->log=(char *)malloc(strlen(c_str)+1);   //fputs should add a /0 in the end of the file
  
  memcpy(ins->log,(char *)c_str,strlen(c_str)+1);  //fputs should add a /0 in the end of the file

  ins->n=strlen(c_str);

  ins->next=NULL;

  LeaveCriticalSection(&g_cs);
#endif
}

int init_que()
{
	InitializeCriticalSection(&g_cs);

	routes.que=(struct logstr*)malloc(sizeof(struct logstr));

	routes.que->log=(char* )malloc(MAX_NUM);

	routes.que->n=sizeof(struct logstr);

	routes.que->next=NULL;

	memcpy((char *)routes.que->log,"first log",sizeof("first log"));

}