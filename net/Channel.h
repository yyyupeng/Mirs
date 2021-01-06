#pragma once

#include "../base/Packet.h"
#include "../base/MemoryPool.h"
#include "../log/Logging.h"
#include "EventLoop.h"

class EventLoop;
typedef std::shared_ptr<EventLoop> SP_EventLoop;
typedef std::weak_ptr<EventLoop> WP_EventLoop;
typedef std::function<void()> CallBack;

class Channel
{
public:
	Channel(SP_EventLoop Loop);
	~Channel();
	void setReadhandler(CallBack&& cb);
	void setWritehandler(CallBack&& cb);
	void setClosehandler(CallBack&& cb);
	void setDeleted(bool Deleted);
	void handleEvent();
	void handleClose();
	void setFd(int Fd);
	void setRevents(int Revents);
	void setEvents(int Events);
	void setnotFirst();
	bool isFirst();
	int getFd();
	int getRevents();
	bool isDeleted();
	WP_EventLoop getLoop();

private:
	int fd;
	int events;
	int revents;
	bool deleted;
	bool First;
	WP_EventLoop loop;
	CallBack readhandler;
	CallBack writehandler;
	CallBack closehandler;	
};

