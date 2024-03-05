#ifndef TIMER
#define TIMER
#include<boost/noncopyable.hpp>
#include"../common/datetime/Timestamp.h"
#include"Callbacks.h"

class Timer:boost::noncopyable
{
    public:
        Timer(const TimerCallback & callback, muduo::Timestamp when,double interval ):
        callback_(callback),expiration_(when),interval_(interval),repeat_(interval>0.0)
        {

        }
        
        void run() const{
            callback_();
        }

        muduo::Timestamp expiration() const 
        {
            return expiration_;
        }

        bool repeat() const
        {
            return repeat_;
        }

        void restart(muduo::Timestamp now);
        

    private : 
        const TimerCallback callback_;
        muduo::Timestamp expiration_;
        const double interval_;
        const bool repeat_;
};

#endif