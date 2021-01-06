#pragma once

#include "../net/EventLoop.h"
#include "Thread.h"
#include <vector>

class ThreadEventLoop
{
public:
	ThreadEventLoop();
	~ThreadEventLoop();
	void start();
	SP_EventLoop getLoop();

private:
	SP_EventLoop loop;
	UP_Thread thread;

    void Loop();
};

typedef std::shared_ptr<ThreadEventLoop> SP_ThreadEventLoop;
