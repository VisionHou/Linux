#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
    umask(0);
    if(mkfifo("mypipe",0644)<0)
    {
        perror("make pipe");
        exit(0);
    }

    int rfd=open("mypipe",O_RDONLY);
    char buf[1024];
    while(1)
    {
        buf[0]=0;
        printf("Please wait...\n");
        size_t s=read(rfd,buf,sizeof(buf)-1);
        if(s>0)
        {
            buf[s-1]=0;
            printf("client says: %s\n",buf);
        }
        else if(s<0)
             {
                 printf("client quit,exit\n");
                 exit(1);
            }
            else
                exit(2);
    }
    close(rfd);
    return 0;
}
