#ifndef POLLER
#define POLLER
#include <boost/noncopyable.hpp>
#include <boost/utility.hpp>
#include <vector>
#include "../common/datetime/Timestamp.h"
#include <poll.h>
#include <map>
#include "EventLoop.h"
class Channel;
class Poller : boost::noncopyable
{
    public:
        //typedef std::vector<Channel *> std::vector<Channel *>;
        Poller(EventLoop *loop);
        ~Poller();

        muduo::Timestamp poll(int timeOutMs, std::vector<Channel *> *activeChannels);

        void updateChannel(Channel *channel);

        void assertInLoopThread();

    private:
        void fillActiveChannel(int numEvents, std::vector<Channel *> *activeChannels) const;

        typedef std::vector<struct pollfd> PollFdList;
        typedef std::map<int, Channel *> ChannelMap;

        EventLoop *ownerLoop_;
        PollFdList pollFds_;
        ChannelMap channels_;
};

#endif