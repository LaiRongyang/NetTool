#ifndef TIMERID
#define TIMERID

#include "../common/datetime/copyable.h"

class Timer;
class TimerId:public muduo ::copyable
{
    public:
        explicit TimerId(Timer *timer):value_(timer)
        {
            
        }

    private:
        Timer *value_;
};
#endif