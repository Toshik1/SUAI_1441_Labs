#include <pthread.h>
#include <cstring>
#include <iostream>
#include <cstddef>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

using std::cout;
using std::endl;
using std::cin;

/*class Event{
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    //int signalCounter
public:
    Event(){
        pthread_cond_init(&cond, NULL);
        pthread_mutex_init(&mutex, NULL);
        //cout << endl << "PthreadCreate ID: " << syscall(SYS_gettid) << endl;
    }
    ~Event(){
        //cout << endl << "PthreadDestroy ID: " << syscall(SYS_gettid) << endl;
        pthread_cond_destroy(&cond);
        pthread_mutex_destroy(&mutex);
    }
    void set(){
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        //cout << endl << "ThreadSignal ID: " << syscall(SYS_gettid) << endl;
        pthread_mutex_unlock(&mutex);
    }
    void reset(){
        pthread_mutex_lock(&mutex);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    void wait(){
        //cout << endl << "WaitThread ID: " << syscall(SYS_gettid) << endl;
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
    }
};*/

class Semaphore{
private:
    size_t count_max;
    size_t count;
    pthread_mutex_t tCS, tCS2;
    //Event *event;
public:
    Semaphore(int count_max) : count_max(count_max), count(0){
        if(pthread_mutex_init(&tCS, nullptr) != 0)
            cout << "\nMutex init failed\n";
        //event = new Event;
        if(pthread_mutex_init(&tCS2, nullptr) != 0)
            cout << "\nMutex init failed\n";
    }
    ~Semaphore(){
        //delete event;
        pthread_mutex_destroy(&tCS);
        pthread_mutex_destroy(&tCS2);
    }
    void lock(){
        pthread_mutex_lock(&tCS);
        if(count < count_max){
            count++;
            cout << "\033[31mCounter start " << count <<"\033[0m"<< endl;
            pthread_mutex_unlock(&tCS);
            return;
        } else {
            count++;
            pthread_mutex_unlock(&tCS);
            pthread_mutex_lock(&tCS2);
            //event->wait();
            //event->reset();
            cout << "Counter start " << count << endl;
            pthread_mutex_lock(&tCS2);
        }
        return;
    }
    void unlock(){
           pthread_mutex_lock(&tCS);
           cout << "Counter finish " << count << endl;
           //if(count-- >= count_max){
               //event->set();
           //}
           count--;
           pthread_mutex_unlock(&tCS);
   }
};

Semaphore *SEMAPHORE;

void* foo(void*){
    SEMAPHORE->lock();
    sleep(1);
    SEMAPHORE->unlock();
    return NULL;
}

int main(){
    pthread_t tid[30];
    SEMAPHORE = new Semaphore(5);

    for(int i = 0; i < 30; i++){
        pthread_create(&(tid[i]), nullptr, &foo, nullptr);
    }
    for(size_t i = 0; i < 1; i++)
        pthread_join(tid[i], nullptr);
    return 0;
}

