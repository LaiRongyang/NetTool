CXXFLAGS = -O0 -g  -Wall -I ./include -I ./common -pthread
LDFLAGS = -lpthread -lboost_thread  -lboost_filesystem -lboost_system
BASE_SRC = ./common/logging/Logging.cc ./common/logging/LogStream.cc ./common/thread/Thread.cc  ./common/datetime/Timestamp.cc
LIB_SRC = ./lib/EventLoop.cpp  ./lib/Channel.cpp  ./lib/Poller.cpp



test:$(LIB_SRC)
	g++  ./src/main.cpp $(CXXFLAGS) -o $@  $(LIB_SRC)  $(BASE_SRC)  $(LDFLAGS)


