#include "EventLoopThreadpool.h"

EventLoopThreadpool::EventLoopThreadpool(int Threadnum)
:	threadnum(Threadnum),
	index(0)
{
	threads.reserve(threadnum);
	for(int i = 0; i < threadnum; ++i)
    {
		SP_ThreadEventLoop t(newElement<ThreadEventLoop>(), deleteElement<ThreadEventLoop>);
		threads.emplace_back(t);
	}	
}

EventLoopThreadpool::~EventLoopThreadpool()
{
	threads.clear();
}

void EventLoopThreadpool::start()
{
	for(auto& temp : threads)
		temp->start();
}

SP_EventLoop EventLoopThreadpool::getNextloop()
{
	index = (index + 1) % threadnum;
	return threads[index]->getLoop();
}
