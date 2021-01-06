#pragma once

#include "../base/Conf.h"
#include "AsyncLogging.h"
#include "FixedBuffer.h"
#include <sys/time.h>

class Impl
{
public:
	Impl(const char *filename, int line);
	void formatTime();
	std::string getBaseName();
	LogStream& stream();
	int getLine();	

private:
	LogStream stream_;
	int line;
	std::string basename;
};

class Logger
{
public:
	Logger(const char *filename, int line);
	~Logger();
	LogStream& stream();
	static std::string getLogFileName();
	static std::string logFileName;

private:
	Impl impl;
};

#define LOG Logger(__FILE__,__LINE__).stream()

