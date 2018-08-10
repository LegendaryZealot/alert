#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "define.h"
#include "worker.h"

char buf[BUFSIZE];

int main(int argc, char const *argv[])
{
    if(1==argc)
    {
        printf("worker pid:\n");
        sprintf(buf,"cat %s",PIDREC);
        system(buf);
        return 0;
    }
    if(3==argc)
    {
        if(0!=access(argv[2],F_OK))
        {
            printf("Bad audio file:%s\n",argv[2]);
            return 0;
        }
        if(0==access(PIDREC,R_OK))
        {
            int pid=-1;
            FILE *fp=fopen(PIDREC,"r");
            fscanf(fp,"%d",&pid);
            fclose(fp);
            sprintf(buf,"kill %d",pid);
            system(buf);
            sprintf(buf,"rm -f %s",PIDREC);
            system(buf);
        }
        sprintf(buf,"rm -f %s",AUDIOPATH);
        system(buf);
        sprintf(buf,"cp %s %s",argv[2],AUDIOPATH);
        system(buf);
        SetBackgroundWorker(atoi(argv[1]));
        return 0;
    }
    printf("set job:\n");
    printf("./app min(time) path(audio)\n");
    printf("get job:\n");
    printf("./app\n");
    return 0;
}
