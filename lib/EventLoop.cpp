#include "../include/EventLoop.h"

__thread EventLoop *t_loopInthisThread = 0;

// one loop per thread 
EventLoop::EventLoop() : looping_(false), threadId_(muduo::CurrentThread::tid())
{
    std::cout << "EventLoop Created " << this << " in thread" << threadId_<<std::endl;
    if(t_loopInthisThread)
    {
        std::cout << "current thread has created another EventLoop object " << t_loopInthisThread << std::endl;
    }else{
        t_loopInthisThread = this;
    }
}

EventLoop::~EventLoop()
{
    assert(!looping_);
    t_loopInthisThread = nullptr;
}

void EventLoop::assertInLoopThread()
{
    if (!isInLoopThread())
    {
        abortNotInLoopThread();
    }
}

EventLoop *EventLoop::getEventLoopOfCurrentThread()
{
    return t_loopInthisThread;
}

bool EventLoop::isInLoopThread() const
{
    return threadId_ == muduo::CurrentThread::tid();
}

void EventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;
    poll(nullptr, 0, 5 * 1000);

    std::cout << "EventLoop " << this << " stop looping" << std::endl;
    looping_ = false;
}

void EventLoop::abortNotInLoopThread()
{
    std::cout << "abort NotInLoopThread." << std::endl;
    assert(0);
    return;
}

void EventLoop::updateChannel(Channel * channel)
{

}