#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "worker.h"
#include "define.h"

char buf[BUFSIZE];
int forkCode;

void DoBackgroundWorker();

void SetBackgroundWorker(int minute)
{
    forkCode=fork();
    if(forkCode<0)
    {
        printf("fork error!\n");
        exit(0);
    }
    if(0==forkCode)
    {
        sprintf(buf,"echo %ld > %s",(long)getpid(),PIDREC);
        system(buf);
        long s=minute*60;
        while(1)
        {
            DoBackgroundWorker();
            sleep(s);
        }
    }
    if(0<forkCode)
    {
        printf("job done!\n");
    }
}

void DoBackgroundWorker()
{
    sprintf(buf,"date >> %s",LOGPATH);
    system(buf);
    sprintf(buf,CMDFORMATE,AUDIOTOOL,AUDIOPATH);
    FILE *fp=popen(buf,"r");
    if(fp)
    {
        //to do log
    }
    pclose(fp);
}