#include "base/Conf.h"
#include "net/Server.h"
#include <signal.h>

int main()
{
	init_memorypool();
	const char *conf = "base/WebServer.conf";
	getconf().init(conf);
	getCache().init();
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, EventLoop::setquit);
	signal(SIGQUIT, EventLoop::setquit);
	Server server(getconf().getport().c_str(), getconf().getthreads());
	server.start(); //启动事件循环
    return 0;
}
