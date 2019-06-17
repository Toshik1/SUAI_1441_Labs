/*
	2.	Создать R потоков с приоритетом F, отличных по подаваемой функции от потоков, создаваемых в пункте 1.
   1.	Создать Y потоков с одинаковым набором атрибутов и приоритетом P
   6.	Основной поток изменяет себе приоритет на S.
  8.	Поток из пункта 2 выводит свой номер и приоритет L раз.
  5.	Основной поток ожидает завершения выполнения потоков, созданных в пункте 2.
  (можно использовать цикл, в котором будет производится вызов требуемой функции).
 9.	Создать поток, который будет ожидать завершение основного потока, и после этого выводить прощальную фразу.
*/
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>


#define Y 7
#define P 8
#define R 1
#define F 10
#define S 6
#define L 25

using namespace std;
int nom=0;

typedef struct numif
{
    int num;
} numifi;

void *thread_1(void *args);
void *thread_2(void *args);
void *thread_glav(void *args);

int main()
{
    cout<<"begins!"<<endl;
	
	  /*Создать R потоков с приоритетом F*/
      pthread_t thread2[R];
      nom = 0;
       for(int i=0; i<R; i++)
       {
           pthread_create(&thread2[i], NULL, thread_2, (void*) nom);
       }

    numifi nimf[Y];

    for(int i=0; i<Y; i++)
    {
        nimf[i].num=nom;
        nom++;
    }

	/*оздать Y потоков с одинаковым набором атрибутов и приоритетом P*/
    pthread_attr_t trib;
    pthread_attr_init(&trib);
    struct sched_param par;

    int pol;
    pthread_getschedparam(pthread_self(), &pol,&par);

    par.sched_priority=P;

    par.sched_priority=P;
    pthread_attr_setschedparam(&trib, &par);

    cout<<"before creating threads"<<endl;

	pthread_t thread[Y];

    for(int i=0; i<Y; i++)
    {
        pthread_create(&thread[i], &trib, thread_1, (void*) &nimf[i]);
    }
       /*Основной поток меняет себе приоритет на S*/
       	pthread_setschedprio (pthread_self(), S);

       for(int i=0; i<R; i++)
       {
       /*Основной поток ожидает завершения выполнения потоков, созданных в пункте 2*/
          pthread_join(thread2[i], NULL);
          nom++;
       }

       	/*ожидать завершение основного потока, и после этого выводить прощальную фразу*/
       	    pthread_t t_gl;
       	   	pthread_t ttt = pthread_self();
       	   	pthread_create(&t_gl, &trib, thread_glav, (void*) &ttt);

	pthread_exit(0);
}

void *thread_1(void *args)
{
    numifi* struk=(numifi*)args;

		cout<<"one"<<endl;
		cout<<"My ID="<<pthread_self()<<endl;
		cout<<"my number="<<struk->num<<endl;
		cout<<"from one"<<endl<<endl;
}


void *thread_2(void *args)
{
    int num=(int)args;

    cout<<"two"<<endl;
    cout<<"My ID="<<pthread_self()<<endl;
    cout<<"my number="<<num<<endl;
    cout<<"from two"<<endl<<endl;
    pthread_t t22 = pthread_self ();
    pthread_setschedprio (t22, F);
    /*Поток из пункта 2 выводит свой номер и приоритет L раз*/
    for(int i=0; i<L; i++)
        {
            cout<<"my number="<<num<<endl;
            cout<<"priori="<<getprio(0)<<endl;
        }

}

void *thread_glav(void *args)
{	/*ожидать завершение основного потока, и после этого выводить прощальную фразу*/
	pthread_t tt = (pthread_t)args;
	pthread_join(tt, NULL);
    cout<<"!!!Good by !!!"<<endl;
}

