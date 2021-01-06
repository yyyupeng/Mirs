#pragma once

#include "../base/ThreadEventLoop.h"
#include "../base/MemoryPool.h"

class EventLoopThreadpool
{
public:
	EventLoopThreadpool(int Threadnum);
	~EventLoopThreadpool();
	void start();
	SP_EventLoop getNextloop();

private:
	vector<SP_ThreadEventLoop> threads;	
	int threadnum;	
	int index;
};

typedef std::unique_ptr<EventLoopThreadpool, decltype(deleteElement<EventLoopThreadpool>)*> UP_EventLoopThreadpool;
