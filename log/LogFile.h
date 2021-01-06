#pragma once

#include "../base/Mutex.h"
#include "../base/MemoryPool.h"
#include "FileUtil.h"

class LogFile : noncopyable
{
public:
	LogFile(const std::string& Basename, int FlushEveryN = 1024);
	~LogFile() {}
	void append(const char *logline, int len);
	void flush();

private:
	const std::string basename;
	const int flushEveryN;
	int count;
	MutexLock mutex;
	UP_FileUtil file;
	
    void append_unlocked(const char *logline, int len);
};
