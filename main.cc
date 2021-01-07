#include "base/Conf.h"
#include "net/Server.h"
#include <signal.h>

int main()
{
	const char *conf = "base/WebServer.conf";   //配置文件目录
	getconf().init(conf);   //配置文件初始化
	init_memorypool();      //内存池初始化
	getCache().init();      //LFU缓存初始化
	signal(SIGINT, EventLoop::setquit);         //信号设置(ctrl + c 停止服务器)
	Server server(getconf().getport().c_str(), getconf().getthreads());     //服务器初始化(端口号 + 创建线程数)
	server.start();         //启动事件循环
    return 0;
}
