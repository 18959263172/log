 #include"logger.h"

logfile interface;

bool open_log(unsigned char *buf)
{
  if(interface.file=fopen(buf,"a+"))
    {
      
    }
  else
    {
      printf("error open file");
    }
}

bool write_log()
{
  if(interface.void_flag)
    {
      reutrn 0;
    }
  else
    {
      fputs(interface.stdbuf,interface.file,);
      return 1;
  }
}

bool clean_log(unsigned char * buf)
{
  if(!remove(buf))

    return 1;
  return 0; 
}  


#ifdef WIN32

DOWROD callback TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{
  
  write_log();

}

#endif

bool start_log(logfile *log)
{
#ifdef WIN32 
  
  HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);
  WaitForSingleObject(handle, INFINITE);
  if(interface.freq_ms>0)
    {
      SetTimer(NULL,0,interface.freq_ms,TimerProc);
    }
  return 0;
  
#endif


}
