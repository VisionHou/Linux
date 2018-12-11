#include<iostream>
  2 #include<pthread.h>
  3 #include<string>
  4 #include<unistd.h>
  5 
  6 pthread_mutex_t lock;
  7 pthread_cond_t cond;
  8 using namespace std;
  9 
 10 void *r1(void *arg)
 11 {
 12     std::string t1=(char*)arg;
 13     while(1)
 14     {
 15         pthread_cond_wait(&cond,&lock);
 16         cout<<t1<<"is running"<<endl;
 17     }
 18 }
 19 
 20 void *r2(void *arg)
 21 {
 22     while(1)
 23     {
 24         pthread_cond_signal(&cond);
 25         sleep(2);
 26     }
 27 }
 28 int main()
 29 {
 30     pthread_mute
