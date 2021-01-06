#pragma once

#include "../base/noncopyable.h"
#include "../base/MemoryPool.h"
#include <fstream>
#include <memory>

#define BUFFERSIZE 64*1024

class FileUtil : noncopyable
{
public:
	explicit FileUtil(std::string filename);
	~FileUtil();
	void append(const char *logline, int len);
	void flush();

private:
	FILE *fp;
	char buffer[BUFFERSIZE];	
	
    int write(const char *logline, int len);
};

typedef std::unique_ptr<FileUtil, decltype(deleteElement<FileUtil>)*> UP_FileUtil;


