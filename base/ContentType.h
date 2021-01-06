#pragma once

#include <map>
#include <pthread.h>

class ContentType
{
public:
	ContentType() = default;
	static std::string getCont(const std::string&);

private:
	static pthread_once_t once_control;
	static std::map<std::string, std::string> mime;
	static void init();	
};
