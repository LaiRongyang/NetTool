#include "../include/Channel.h"
#include "../include/EventLoop.h"
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1)
{

}

void Channel::update()
{
    loop_->updateChannel(this);
}

EventLoop *Channel::ownerLoop()
{
    return loop_;
}

int Channel::index()
{
    return index_;
}

void Channel::set_index(int idx)
{
    index_ = idx;
}

int Channel::fd() const
{
    return fd_;
}

int Channel::events()
{
    return events_;
}
void Channel::set_revents(int revt)
{
    revents_ = revt;
}
bool Channel::IsNoneEvent() const
{
    return events_ == kNoneEvent;
}

void Channel::handleEvent()
{
    if(revents_ & POLLNVAL)
    {
        std::cout << "Channel::handle_event() POLLNVAL" << std::endl;
    }
    if(revents_ & (POLLERR | POLLNVAL))
    {
        if(errorCallback_)
        {
            errorCallback_();
        }
    }
    if(revents_ & (POLLIN | POLLPRI | POLLRDHUP))
    {
        if(readCallback_)
        {
            readCallback_();
        }
    }
    if(revents_ & POLLOUT)
    {
        if(writeCallback_)
        {
            writeCallback_();
        }
    }
}

void Channel::enableReading()
{
    events_ |= kReadEvent;
    update();
}
void Channel::enableWriting()
{
    events_ |= kWriteEvent;
    update();
}
void Channel::disableWriting()
{
    events_ &= ~kWriteEvent;
    update();
}
void Channel::disableAll()
{
    events_ = kNoneEvent;
    update();
}

void Channel::setReadCallback(const EventCallback &cb)
{
    readCallback_ = cb;
}
void Channel::setWriteCallback(const EventCallback &cb)
{
    writeCallback_ = cb;
}
void Channel::setErrorCallback(const EventCallback &cb)
{
    errorCallback_ = cb;
}
