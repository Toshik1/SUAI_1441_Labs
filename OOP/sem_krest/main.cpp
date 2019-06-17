#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;
using ::this_thread::sleep_for;
using ::chrono::seconds;

class Event{
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
};

class Semaphore
{
    uint32_t max_count;
    uint32_t count;
    mutex CS, CS_2;
    Event *event;
public:
    Semaphore(int max_count) : max_count(max_count), count(0){}
    ~Semaphore(){}
    void lock(){
        CS.lock();
        //lock_guard<mutex>lock(CS);
        if(count < max_count)
        {
            //lock();
            count++;
            //sleep_for(seconds(5));
            cout << "\033[31mCounter start " << count <<"\033[0m"<< endl;
            CS.unlock();
            return;
        }
        else
        {
            count++;
            CS.unlock();
            CS_2.lock();
            event->reset();
            event->wait();
            cout << "Counter start " << count << endl;
            CS_2.unlock();
        }
    }
    void unlock()
    {
        CS.lock();
    //    cout << endl << "Counter finish " << count << endl;
        count--;
        event->set();
        CS.unlock();
    }
};

Semaphore *sema;
auto number = 0;
/*void exec1(int id){
    int n = 3;
    while(n--){
        sema->lock();
        sleep_for(seconds(1));
        ++number;
        cout << endl << id << "=>" << number << endl;
        sema->unlock();
    }
}*/

void exec(){
    sema->lock();
    sleep_for(seconds(1));
    sema->unlock();
}

int main()
{
    vector<thread>pt;
    sema = new Semaphore(5);

    for(int i = 1; i <= 10; i++){
        pt.push_back(thread(exec));
    }
    //thread pt1(exec1, 0), pt2(exec1, 1);
    for(auto &x : pt) x.join();
    //pt1.join(); pt2.join();
    return 0;
}
