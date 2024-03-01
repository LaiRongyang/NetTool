// 使用举例：
#include <iostream>
#include <thread>
#include <mutex>
#include <boost/thread/shared_mutex.hpp>
#include <list>
#include "../include/EventLoop.h"
#include"../common/thread/Thread.h"

EventLoop *g_pEventLoop = nullptr;

void threadFunc()
{
    std::cout << "threadFunc() : pid " << getpid() << " "
              << "tid " << muduo::CurrentThread::tid() << std::endl;
    g_pEventLoop->loop();
}

int main()
{
    std::cout << "main() : pid " << getpid() << " "
              << "tid " << muduo::CurrentThread::tid() << std::endl;
    EventLoop loop;
    g_pEventLoop  = & loop;
    muduo::Thread thread(threadFunc);
    thread.start();
    pthread_exit(NULL);
    return 0;
}
