#pragma once

#include "../base/Packet.h"
#include "../base/MemoryPool.h"
#include "Channel.h"

typedef long long LL;   //防止计算时间时溢出

class Channel;
typedef std::shared_ptr<Channel> SP_Channel;

class TimerNode
{
public:
	TimerNode(SP_Channel Channel, int timeout);
	~TimerNode() {}
	LL getExpiredtime();
	void update(int timeout);
	bool isExist();
	bool isDeleted();
	SP_Channel getChannel();

private:
	SP_Channel channel;
	LL expiredtime;
};
typedef std::shared_ptr<TimerNode> SP_TimerNode;

struct TimerCmp
{
	bool operator()(SP_TimerNode& a, SP_TimerNode& b) const
    {
		return a->getExpiredtime() > b->getExpiredtime();   //小顶堆
	}
};

class TimerManager
{
public:
	void addTimer(SP_Channel channel, int timeout);
	void handleExpiredEvent();

private:
	std::priority_queue<SP_TimerNode, std::vector<SP_TimerNode>, TimerCmp> timerheap;   //自定义类型优先队列
	std::unordered_map<int, SP_TimerNode> timermap;     //fd映射TimerNode节点
};

