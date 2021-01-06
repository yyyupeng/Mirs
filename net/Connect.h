#pragma once

#include "../base/Packet.h"
#include "../base/ContentType.h"
#include "../base/MemoryPool.h"
#include "../base/LFUCache.h"
#include "Buffer.h"
#include "EventLoop.h"

enum METHOD { METHOD_GET, METHOD_POST };
enum HTTPVERSION { HTTP_11 };
enum PARSESTATE { PARSE_ERROR, PARSE_METHOD, PARSE_HEADER, PARSE_SUCCESS };

class Channel;
typedef shared_ptr<Channel> SP_Channel;

class Connect
{
public:
	Connect(SP_Channel channel);
	Connect() {}

private:
	typedef function<PARSESTATE()> CallBack;
	CallBack handleparse[4];
	SP_Channel channel;
	int pos;
	int size;
	bool keepalive;
	string inbuffer;
	string path;
	string filetype;
	string storage;
	METHOD method;
	HTTPVERSION version;
	PARSESTATE parsestate;
	unordered_map<string, string> header;
	
    PARSESTATE parseMethod();
	PARSESTATE parseHeader();
	PARSESTATE parseError();
	PARSESTATE parseSuccess();
	void parse();
	void initmsg();
	void send();
	bool Read(string& msg, string str);
	void handleError(int errornum, string msg);
};


