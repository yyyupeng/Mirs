#include "EventLoop.h"

bool EventLoop::quit = false;

EventLoop::EventLoop()
:	poller(newElement<Epoll>(), deleteElement<Epoll>),
	looping(false),
	timermanager(newElement<TimerManager>(), deleteElement<TimerManager>)
{
	wakeupfd = Eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
}

void EventLoop::addPoller(SP_Channel channel)
{
	poller->add(channel);
}

void EventLoop::updatePoller(SP_Channel channel)
{
	poller->update(channel);
}

void EventLoop::removePoller(SP_Channel channel)
{
	poller->del(channel);
}

void EventLoop::loop()
{
	wakeupchannel = SP_Channel(newElement<Channel>(shared_from_this()), deleteElement<Channel>);
	wakeupchannel->setFd(wakeupfd);
	wakeupchannel->setRevents(EPOLLIN | EPOLLET); //ET模式
	wakeupchannel->setReadhandler(std::bind(&EventLoop::doPendingFunctors, shared_from_this()));
	addPoller(wakeupchannel);
	std::vector<SP_Channel> temp;
	while(!quit)
    {
		poller->poll(temp);
		for(auto &ti : temp)
			ti->handleEvent();
		temp.clear();
		timermanager->handleExpiredEvent();
	}
}

void EventLoop::addTimer(SP_Channel channel, int timeout)
{
	timermanager->addTimer(std::move(channel), timeout);
}

void EventLoop::queueInLoop(Functor&& cb)
{
    //将cb放入队列并唤醒
	{
		MutexLockGuard lock(mutex);
		pendingfunctors.emplace_back(std::move(cb));
	}
	uint64_t buffer = 1;
	if(write(wakeupfd, &buffer, sizeof(buffer)) < 0)
		LOG << "wake up write error";
}

void EventLoop::doPendingFunctors()
{
	uint64_t buffer;
	if(read(wakeupfd, &buffer, sizeof(buffer)) < 0)
		LOG << "wake up read error";
	std::vector<Functor> next;
	{
		MutexLockGuard lock(mutex);
		next.swap(pendingfunctors);     //减小临界区长度，避免死锁
	}
	for(auto &ti : next)
		ti();   //执行Functor
}

void EventLoop::setquit(int signal)
{
	quit = true;
}
