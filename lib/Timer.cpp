
#include "../include/Timer.h"
void Timer::restart(muduo::Timestamp now)
{
    if(repeat_)
    {
        expiration_ = muduo::addTime(now, interval_);
    }else{
        expir
    }
}