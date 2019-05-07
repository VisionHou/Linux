#ifndef _COMM__H_
#define _COMM__H_
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#define PATHNAME "."
#define PROJ_ID 0x6666

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct msgbuf
{
    long mtype;
    char mtext[1024];
};

int createMsgQueue();
int getMsgQueue();
int sendMsg(int msgid,int who,char* msg);
int recvMsg(int msgid,int recvType,char out[]);
int destroyMsgQueue(int msgid);
#endif
