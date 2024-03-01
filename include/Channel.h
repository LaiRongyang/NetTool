#ifndef CHANNEL
#define CHANNEL
#include <boost/noncopyable.hpp>
#include <boost/utility.hpp>
#include<boost/function.hpp>
#include <poll.h>
class EventLoop;

class Channel:boost::noncopyable
{
    public:
        typedef boost::function<void()> EventCallback;

        Channel(EventLoop *loop, int fd);

        void handleEvent();
        void setReadCallback(const EventCallback &cb);
        void setWriteCallback(const EventCallback &cb);
        void setErrorCallback(const EventCallback &cb);

        void enableReading();
        void enableWriting();
        void disableWriting();
        void disableAll();

        int fd() const;
        int events();
        void set_revents(int revt);
        bool IsNoneEvent() const;

        int index();
        void set_index(int idx);

        EventLoop *ownerLoop();

    private:
        void update();

        static const int kNoneEvent;
        static const int kReadEvent;
        static const int kWriteEvent;

        EventLoop *loop_;
        const int fd_;
        int events_;
        int revents_;
        int index_;

        EventCallback readCallback_;
        EventCallback writeCallback_;
        EventCallback errorCallback_;

};


#endif