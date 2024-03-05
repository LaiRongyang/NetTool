#include"../include/Poller.h"
#include "../include/Channel.h"
void Poller::assertInLoopThread()
{
    ownerLoop_->assertInLoopThread();
}
Poller::Poller(EventLoop * loop)
{
    ownerLoop_ = loop;
}
Poller::~Poller()
{
}
muduo::Timestamp Poller::poll(int timeOutMS, std::vector<Channel *> *activeChannels)
{
    int numEvents = ::poll(&(*pollFds_.begin()), pollFds_.size(), timeOutMS);
    muduo::Timestamp now(muduo::Timestamp::now());
    if (numEvents>0)
    {
        fillActiveChannel(numEvents, activeChannels);
    }else if(0 == numEvents )
    {
        std::cout << "nothing happened." << std::endl;
    }else{
        std::cout << "Poller::poll() error" << std::endl;
    }
    return now;
}

void Poller::fillActiveChannel(int numEvents, std::vector<Channel *> *activeChannels) const
{
    for (PollFdList::const_iterator iterFd=pollFds_.begin(); iterFd != pollFds_.end() && numEvents>0; iterFd++)
    {
        if(iterFd->revents>0)
        {
            numEvents--;
            ChannelMap::const_iterator iterChannel = channels_.find(iterFd->fd);
            assert(iterChannel != channels_.end());
            Channel *pChannel = iterChannel->second;
            assert(pChannel->fd() == iterFd->fd);
            pChannel->set_revents(iterFd->revents);
            activeChannels->push_back(pChannel);
        }
    }
}

void Poller::updateChannel(Channel *channel)
{
    assertInLoopThread();
    std::cout << "update fd = " << channel->fd() << " events " << channel->events() << std::endl;
    if(channel->index()<0)//添加fd
    {
        assert(channels_.find(channel->fd()) == channels_.end());
        struct pollfd fd;
        fd.fd = channel->fd();
        fd.events = static_cast<short>(channel->events());
        fd.revents = 0;
        pollFds_.push_back(fd);
        int idx = static_cast<int>(pollFds_.size() - 1);
        channel->set_index(idx);
        channels_[fd.fd] = channel;
    }else{//更新fd
        assert(channels_.find(channel->fd()) != channels_.end());
        assert(channels_[channel->fd()] == channel);
        int idx = channel->index();
        assert(idx >= 0 && idx < static_cast<int>(pollFds_.size()));
        struct pollfd &fd = pollFds_[idx];
        assert(fd.fd == channel->fd() || fd.fd == -1);
        fd.events = static_cast<short>(channel->events());
        fd.revents = 0;
        if(channel->IsNoneEvent())//忽略这个fd???
        {
            fd.fd = -1;
        }
    }
}

