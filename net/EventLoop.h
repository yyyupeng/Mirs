#pragma once

#include "../base/Mutex.h"
#include "TimerManager.h"
#include "Epoll.h"

class Channel;
class Epoll;
class TimerManager;
typedef std::shared_ptr<Channel> SP_Channel;
typedef std::weak_ptr<Channel> WP_Channel;
typedef std::shared_ptr<Epoll> SP_Epoll;
typedef std::shared_ptr<TimerManager> SP_TimerManager;
typedef std::function<void()> Functor;

class EventLoop : public std::enable_shared_from_this<EventLoop>
{
public:
	EventLoop();
	void addPoller(SP_Channel channel);
	void updatePoller(SP_Channel channel);
	void removePoller(SP_Channel channel);
	void loop();
	void addTimer(SP_Channel channel, int timeout);
	void queueInLoop(Functor&& cb);
	void doPendingFunctors();
	static void setquit(int);

private:
	std::vector<Functor> pendingfunctors;
	int wakeupfd;
	SP_Channel wakeupchannel;
	SP_Epoll poller;
	bool looping;
	static bool quit;
	SP_TimerManager timermanager;
	MutexLock mutex;

};

