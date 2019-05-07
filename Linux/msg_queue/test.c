#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<stdio.h>
int main()
{
    key_t key=ftok(".",1);
    if(key<0)
    {
        perror("ftok");
        exit(0);
    }
    int msgid=msgget(key,IPC_CREAT|0644);
    if(msgid<0)
    {
        perror("msgid");
        exit(1);
    }
    char* str="hello";
    struct msgbuf
    {
        long mtype;
        char mtext[102];
    };
    struct msgbuf buf;
    buf.mtype=1;
    strcpy(buf.mtext,str);
    if(msgsnd(msgid,(void*)&buf,sizeof(buf.mtext),0)<0)
    {
        perror("msgsnd");
        exit(1);
    }
    struct msgbuf rcv;
    if(msgrcv(msgid,(void*)&buf,sizeof(buf.mtext),1,0)<0)
    {
        perror("msgrcv");
        exit(2);
    }
    printf("%s\n",buf.mtext);
    return 0;
}
