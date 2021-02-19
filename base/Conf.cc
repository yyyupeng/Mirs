#include "Conf.h"

#define DEFAULT_THREADS 3
#define DEFAULT_PORT "8888"
#define DEFAULT_LISTENQ 2048
#define DEFAULT_STORAGE "test/"
#define DEFAULT_KEEPALIVE 20000
#define DEFAULT_LOGFILE "log/WebServer.log"
#define DEFAULT_CAPACITY 10

void Conf::init(const char *path)
{
	strncpy(conf, path, 99);
	map<string,string> m;
	fstream file;
	file.open(conf, ios::in);
	string buf;
	while(!file.eof())
    {
		getline(file, buf);
		pretreatment(buf);
		if("" == buf)
			continue;
		parse(m, buf);
	}
	file.close();
	if(m.find("threads") != m.end())
		threads = stoi(m["threads"]);
	else
		threads = DEFAULT_THREADS;
	if(m.find("port") != m.end())
		port = m["port"];
	else
		port = DEFAULT_PORT;
	if(m.find("listenq") != m.end())
		listenq = stoi(m["listenq"]);
	else
		listenq = DEFAULT_LISTENQ;
	if(m.find("storage") != m.end())
		storage = m["storage"];
	else
		storage = DEFAULT_STORAGE;
	if(m.find("keepalive") != m.end())
		keepalive = stoi(m["keepalive"]);
	else
		keepalive = DEFAULT_KEEPALIVE;
	if(m.find("logfile") != m.end())
		logfile = m["logfile"];
	else
		logfile = DEFAULT_LOGFILE;
	if(m.find("capacity") != m.end())
		capacity = stoi(m["capacity"]);
	else
		capacity = DEFAULT_CAPACITY;
}

int Conf::getthreads()
{
	return threads;
}

string Conf::getport()
{
	return port;
}

int Conf::getlistenq()
{
	return listenq;
}

int Conf::getkeepalive()
{
	return keepalive;
}

string Conf::getstorage()
{
	return storage;
}

string Conf::getlogfile()
{
	return logfile;
}

int Conf::getcapacity()
{
	return capacity;
}

int Conf::getpos(string& buf, int start, int end, bool flag)
{
	for(; start < end; ++start)
    {
		if(flag)
        {
			if(' ' == buf[start] || '\t' == buf[start])
				return start;
		}
		else
        {
			if(' ' != buf[start] && '\t' != buf[start])
				return start;
		}
	}
	return start;
}

void Conf::parse(map<string,string>& m, string& buf)
{
	int kstart = getpos(buf, 0, buf.size(), false);
	int kend = getpos(buf, kstart, buf.size(), true);
	int vstart = getpos(buf, kend, buf.size(), false);
	int vend = getpos(buf, vstart, buf.size(), true);
	
    //满足条件后加入map
    if(vstart != buf.size())
		m[buf.substr(kstart, kend - kstart)] = buf.substr(vstart, vend - vstart);
}

void Conf::pretreatment(string& buf)
{
	int last = buf.find("#", 0);
	if(string::npos == last)
		return;
	buf = buf.substr(0, last);
	return;
}

Conf& getconf()
{
	static Conf conf;
	return conf;
}

