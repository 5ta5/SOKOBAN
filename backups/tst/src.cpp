// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread

using namespace std;

class konstruktor;

void f(konstruktor *x){
    while(true){
        cout<<"a"<<x<<"\n";
    }
}

class konstruktor{
public:
    konstruktor(){
        thread first (f, this);
        std::cout << "main, foo and bar now execute concurrently...\n";
        /*
        while(true){
            cout<<"b\n";
        }
    
        first.join();
        */
        std::cout << "foo and bar completed.\n";
    }
};


int main(){
    konstruktor k;
    while(true){
        cout<<"EEE\n";
    }
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

void *task(void *argument){
    char* msg;
    msg = (char*)argument;
    std::cout<<msg<<std::endl;
}

int main(){
    pthread_t thread1, thread2;
    int i1,i2;
    i1 = pthread_create( &thread1, NULL, task, (void*) "thread 1");
    i2 = pthread_create( &thread2, NULL, task, (void*) "thread 2");
    
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    return 0;
    
}
*/


/*
#include <iostream>
#include <boost/thread.hpp>
//#include <thread>

using namespace boost;
using namespace std;

void task1() { 
    // do stuff
    cout<<"a\n";
}

void task2() { 
    // do stuff
    cout<<"b\n";
}

int main (int argc, char ** argv) {
    
    thread thread_1 = thread(task1);
    thread thread_2 = thread(task2);
    
    // do other stuff
    thread_2.join();
    thread_1.join();
    return 0;
}
*/

/*
#include <string>
#include <iostream>
#include <thread>

using namespace std;

void th(){
    while(true){
        cout<<"true\n";
    }
}

void task1(string msg)
{
    cout << "task1 says: " << msg;
}

int main(){
    cout<<"Hello\n";
    
    //th();
    //thread t1(th);
    
    thread t1(task1, "Hello");
    
    t1.join();
}
*/
