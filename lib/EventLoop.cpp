#include "../include/EventLoop.h"
#include "../include/Poller.h"
#include "../include/Channel.h"
__thread EventLoop *t_loopInthisThread = 0;
const int kPollTimeMs = 10000;
// one loop per thread 
EventLoop::EventLoop() : looping_(false),quit_(false), threadId_(muduo::CurrentThread::tid()),poller_(new Poller(this))
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
    quit_ = false;

    while (!quit_)
    {
        activeChannels_.clear();
        poller_->poll(kPollTimeMs, &activeChannels_);
        for (std::vector<Channel *>::iterator iter = activeChannels_.begin(); iter != activeChannels_.end();iter++)
        {
            (*iter)->handleEvent();
        }

    }

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
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    poller_->updateChannel(channel);
}
void EventLoop::quit()
{
    quit_ = true;;
}