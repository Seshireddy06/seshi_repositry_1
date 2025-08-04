#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;
mutex m;
class Cricket{
public:
condition_variable cv;
bool flag=false;
void umpire()
{
    unique_lock<mutex> lock(m);
    cout<<"wait for third umpire\n";
    cv.wait(lock,[this](){return flag;});
    if(flag==true)
    {
    cout<<"not out\n";}
    else
    {
    cout<<"out\n";
    }
}
void thirdUmpire()
{
    {
        lock_guard<mutex> lock(m);
        flag=true;
        cout<<"signal is passed\n";
    }
    cv.notify_one();
}
};
int main()
{
    Cricket ck;
    thread t1(&Cricket::umpire,&ck);
    thread t2(&Cricket::thirdUmpire,&ck);
    t1.join();
    t2.join();
    cout<<"main thread is executed\n";
    return 0;
}