
#pragma once

#include<iostream>
#include<string>
#include<unordered_map>
#include<cstring>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<signal.h>
#include<pthread.h>

#include"ThreadPool.hpp"
class Sock{
    private:
        int listen_sock;

        int port;
    public:
        Sock(const int &port_):port(port_),listen_sock(-1)
        {}
        void Socket()
        {
            listen_sock=socket(AF_INET,SOCK_STREAM,0);
            if(listen_sock<0)
            {
                std::cerr<<"socket error!"<<std::endl;
                exit(2);
            }
        }
        void Bind()
        {
            struct sockaddr_in local;
            bzero(&local,sizeof(local));
            local.sin_family=AF_INET;
            local.sin_port=htons(port);
         //   local.sin_addr.s_addr=inet_addr(ip.c_str());
            local.sin_addr.s_addr=htonl(INADDR_ANY);
            if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
            {
                std::cerr<<"bind error!"<<std::endl;
                exit(3);
            }
        }
        void Listen()
        {
            if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
            {
                std::cerr<<"bind error!"<<std::endl;
                exit(3);
            }
        }
        void Listen()
        {
            if(listen(listen_sock,5)<0)
            {
                std::cerr<<"listen error!"<<std::endl;
                exit(4);
            }
        }
        int Accept()
        {
            struct sockaddr_in peer;
            socklen_t len=sizeof(peer);
            int sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
            if(sock<0)
            {
                std::cerr<<"accept error"<<std::endl;
                return -1;
            }

            return sock;
        }
        ~Sock()
        {
            close(listen_sock);
        }
    };


    class Server;
    typedef struct {
        int sock;
        Server* sp;
    }data_t;

    class Server{
        private:
            Sock sock;
            std::unordered_map<std::string,std::string> dict;
        public:
    Server(const int &port_):sock(port_)
            {
                dict.insert(std::make_pair("hello","nihao"));
                dict.insert(std::make_pair("xpu","XiAnGongChengDaXue")) ;
                dict.insert(std::make_pair("computer","DianNao")) ;
                dict.insert(std::make_pair("desk","ZhuoZi")) ;
                dict.insert(std::make_pair("apple","PingGuo")) ;
            }
            void InitServer()
            {
                signal(SIGCHLD,SIG_IGN);
                sock.Socket();
                sock.Bind();
                sock.Listen();
            }
            void Service(int sock)
            {
                char buf[1024];
                for( ; ; )
                {
                    ssize_t s=read(sock,buf,sizeof(buf)-1);
                    if(s>0)
                    {
                        buf[s]=0;
                        std::cout<<buf<<std::endl;
                        std::string key=buf;
                        std::string val=dict[key];
                        if(val.empty()){
                            val="null";
                        }
                        write(sock,val.c_str(),val.size());
                       // write(sock,buf,strlen(buf));
                    }
                    else if(s==0)
                    {
                        std::cout<<"client is quit..."<<std::endl;
                        break;
                    }
                    else
                    {
                        std::cerr<<"read error"<<std::endl;
                        break;
                    }
                }
                close(sock);
            }
           // static void *ThreadRun(void* arg)
           // {
           //      pthread_detach(pthread_self());
           //     data_t *d=(data_t*)arg;
           //     Server *sp=d->sp;
           //     int sock=d->sock;
           //     delete d;
           //     sp->Service(sock);
           // }
            void Run()
            {
                for( ; ; )
                    {
                        int new_sock=sock.Accept();
                        if(new_sock<0)
                        {
                            continue;
                        }
                        std::cout<<"Get A New Client..."<<std::endl;
                        Task t(sock,Service);
                        pool.AddTask(t);
                   //     data_t *d = new data_t;
                   //     d->sp=this;
                   //     d->sock=new_sock;
                   //     pthread_t tid;
                   //     pthread_create(&tid,NULL,ThreadRun,(void *)d);

         //              pid_t id = fork();
         //             if(id==0){//child
         //                 Service(new_sock);
         //                   exit(0);
         //             }
         //             close(new_sock);
                    }
            }

            ~Server()
            {}
    } ;
