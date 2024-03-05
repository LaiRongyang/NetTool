#ifndef CALLBACKS
#define CALLBACKS
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include "../common/datetime/Timestamp.h"

typedef boost::function<void()> TimerCallback;

#endif