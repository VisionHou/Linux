#ifndef __CP_HPP__
#define __CP_HPP__

#include<iostream>
#include<queue>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>


class BlockQueue{
    private:
        std::queue<int> bq;
        int cap;
        int water_level;
        pthread_mutex_t lock;
        pthread_cond_t cond_p;//queue empty
        pthread_cond_t cond_c;//queue full
    private:
        void LockQueue()
        {
            pthread_mutex_lock(&lock);
        }
        void UnlockQueue()
        {
            pthread_mutex_unlock(&lock);
        }
        void ProductWait()
        {
            pthread_cond_wait(&cond_p,&lock);
        }
        void ConsumeWait()
        {
            pthread_cond_wait(&cond_c,&lock);
        }
        bool ISFull()
        {
            return bq.size()==cap?true:false;
        }
        bool ISEmpty()
        {
            return bq.size()==0?true:false;
        }
        void SignalConsume()
        {
            pthread_cond_signal(&cond_c);
        }
        void SignalProduct()
        {
            pthread_cond_signal(&cond_p);
        }
    public:
        BlockQueue(int cap_):cap(cap_),water_level(cap_*2/3)
        {
            pthread_mutex_init(&lock,NULL);
            pthread_cond_init(&cond_c,NULL);
            pthread_cond_init(&cond_p,NULL);
        }

        void PushData(const int& data)
        {
            LockQueue();
            while(ISFull())
            {
                SignalConsume();
                ProductWait();
            }

            bq.push(data);
            if(bq.size()>water_level)
            {
                SignalConsume();
                }
            UnlockQueue();
        }

        void PopData(int& data)
        {
            LockQueue();
            while(ISEmpty()){
                SignalProduct();
                ConsumeWait();
            }

            data=bq.front();
            bq.pop();
            UnlockQueue();
        }
        ~BlockQueue()
        {
            pthread_mutex_destroy(&lock);
            pthread_cond_destroy(&cond_c);
            pthread_cond_destroy(&cond_p);
        }
};

#endif
