#include"comm.h"

static int commMsgQueue(int flags)
{
    key_t _key=ftok(PATHNAME,PROJ_ID);//消息队列的名字
    if(_key<0)
    {
        perror("ftok");
        return -1;
    }
    int msgid=msgget(_key,flags);
    if(msgid<0)
    {
        perror("msgget");
    }
    return msgid;
}

int createMsgQueue()
{
    return commMsgQueue(IPC_CREAT|IPC_EXCL|0666);//不存在创建，存在出错
}

int getMsgQueue()
{
    return commMsgQueue(IPC_CREAT);//不存在创建，存在打开
}

int sendMsg(int msgid,int who,char* msg)
{
    struct msgbuf buf;
    buf.mtype=who;
    strcpy(buf.mtext,msg);

    if(msgsnd(msgid,(void*)&buf,sizeof(buf.mtext),0)<0)
    {
        perror("msgsend");
        return -1;
    }
    return 0;
}

int recvMsg(int msgid,int recvType,char out[])//接收消息缓冲区
{
    struct msgbuf buf;
    if(msgrcv(msgid,(void*)&buf,sizeof(buf.mtext),recvType,0)<0)
    {
        perror("msgrecv");
        return -1;
    }
    strcpy(out,buf.mtext);
    return 0;
}
int destroyMsgQueue(int msgid)
{
    if(msgctl(msgid,IPC_RMID,NULL)<0)
    {
        perror("msgctl");
        return -1;
    }
    return 0;
}
