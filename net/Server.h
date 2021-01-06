#pragma once

#include "../base/Packet.h"
#include "../log/Logging.h"
#include "Connect.h"
#include "EventLoop.h"
#include "EventLoopThreadpool.h"

class Connect;
typedef shared_ptr<Connect> SP_Connect;

class Server
{
public:
	Server(const char *port, int threadnum);
	~Server();
	void start();	

private:
	SP_EventLoop loop;
	SP_Channel serverchannel;
	UP_EventLoopThreadpool iothreadpool;
	int listenfd;
	std::unordered_map<int, SP_Connect> Connmap;	
	
    void handleconn();
	void handleclose(WP_Channel channel); 
	void deletemap(SP_Channel channel);
};

