#ifndef EVENTLOOP
#define EVENTLOOP
#include <boost/noncopyable.hpp>
#include <boost/utility.hpp>
#include <iostream>
#include <assert.h>
#include <poll.h>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "../common/thread/Thread.h"
/*
1. 什么都不做的EventLoop
首先定义EventLoop class的基本接口：构造函数、析构函数、loop()成员函数。
注意EventLoop是不可拷贝的，因此它继承了boost::noncopyable。
muduo中的大多数class都是不可拷贝的，因此以后只会强调某个class是可拷贝的。

2. one loop per thread顾名思义每个线程只能有一个EventLoop对象，
因此EventLoop的构造函数会检查当前线程是否已经创建了其他EventLoop对象.
EventLoop的构造函数会记住本对象所属的线程（threadId_）。
创建了EventLoop对象的线程是IO线程，其主要功能是运行事件循环EventLoop::loop()。
EventLoop对象的生命期通常和其所属的线程一样长，它不必是heap对象。
*/
class Channel;
class Poller;
class EventLoop : boost ::noncopyable
{
public:
    EventLoop();
    ~EventLoop();

    void loop();

    void assertInLoopThread();

    bool isInLoopThread() const;

    static EventLoop *getEventLoopOfCurrentThread();

    void updateChannel(Channel * );

    void quit();

private:
    void abortNotInLoopThread();

    bool looping_;
    const pid_t threadId_;

    //typedef std::vector<Channel *> std::vector<Channel *>;

    bool quit_;

    boost::scoped_ptr<Poller> poller_;

    std::vector<Channel *> activeChannels_;
};

#endif