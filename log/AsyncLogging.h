#pragma once

#include "../base/Thread.h"
#include "../base/Mutex.h"
#include "../base/Condition.h"
#include "LogStream.h"
#include "LogFile.h"
#include "FixedBuffer.h"
#include <vector>

class AsyncLogging : noncopyable
{
public:
	AsyncLogging(const std::string logFileName, int FlushInterval = 2);
	~AsyncLogging();
	void append(const char *logfile, int len);
	void start();
	void stop();	

private:
	typedef FixedBuffer<kLargeBuffer> Buffer;
	typedef std::vector<std::shared_ptr<Buffer>> BufferVector;
	typedef std::shared_ptr<Buffer> BufferPtr;
	const int flushInterval;
	bool running;
	std::string basename;
	Thread thread_;
	MutexLock mutex;
	Condition cond;
	BufferPtr currentBuffer;
	BufferPtr nextBuffer;
	BufferVector buffers;
	
    void threadFunc();
};

typedef std::unique_ptr<AsyncLogging, decltype(deleteElement<AsyncLogging>)*> UP_AsyncLogging;

