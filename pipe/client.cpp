#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    int wfd=open("mypipe",O_WRONLY);
    char buf[1024];
    while(1)
    {
        buf[0]=0;
        printf("please Enter...");
        size_t s=read(0,buf,sizeof(buf)-1);
        if(s>0)
        {
            buf[s]=0;
            write(wfd,buf,strlen(buf));
        }
        else
            perror("wiite error");
    }
close(wfd);
return 0;
}
