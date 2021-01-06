#include "TimerManager.h"

typedef struct timeval ST;
/*
    struct timeval
    {
    __time_t tv_sec;         Seconds. 
    __suseconds_t tv_usec;   Microseconds. 
    };
*/

TimerNode::TimerNode(SP_Channel Channel, int timeout)
:	channel((Channel))
{
	ST now;
	gettimeofday(&now, NULL);   //获取时间
	expiredtime = (LL)now.tv_sec * 1000 + now.tv_usec / 1000 + timeout;
}

LL TimerNode::getExpiredtime()
{
	return expiredtime;
}

void TimerNode::update(int timeout)
{
	ST now;
	gettimeofday(&now, NULL);
	expiredtime = (LL)now.tv_sec * 1000 + now.tv_usec / 1000 + timeout;
}

bool TimerNode::isExist()
{
	ST now;
	gettimeofday(&now, NULL);
	LL temp = (LL)now.tv_sec * 1000 + now.tv_usec / 1000;
	if(temp < expiredtime)
		return true;
	return false;
}

bool TimerNode::isDeleted()
{
	return channel->isDeleted();
}

SP_Channel TimerNode::getChannel()
{
	return channel;	
}

void TimerManager::addTimer(SP_Channel channel, int timeout)
{
	SP_TimerNode timernode(newElement<TimerNode>(channel, timeout), deleteElement<TimerNode>);
	int fd = channel->getFd();
	if(channel->isFirst())
    {
		timerheap.push(timernode);
		channel->setnotFirst();
	}
	timermap[fd] = std::move(timernode);
}

void TimerManager::handleExpiredEvent()
{
	while(!timerheap.empty())
    {
		SP_TimerNode now = timerheap.top();
		if(now->isDeleted() || !now->isExist())
        {
			timerheap.pop();
			SP_TimerNode timernode = timermap[now->getChannel()->getFd()];
			if(now == timernode)
            {
				timermap.erase(now->getChannel()->getFd());
				now->getChannel()->handleClose();
			}
			else
				timerheap.push(timernode);
		}
		else
			break;
	}
}
