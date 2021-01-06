#include "ContentType.h"

pthread_once_t ContentType::once_control = PTHREAD_ONCE_INIT;
std::map<std::string, std::string> ContentType::mime;

void ContentType::init()
{
    mime[".html"] = "text/html";
    mime[".gif"] = "image/gif";
    mime[".ico"] = "image/x-icon";
    mime[".jpg"] = "image/jpeg";
    mime[".png"] = "image/png";
    mime[".txt"] = "text/plain";
    mime[".mp3"] = "audio/mp3";
    mime["default"] = "text/html";
}

std::string ContentType::getCont(const std::string& suffix)
{
	pthread_once(&once_control, ContentType::init);
	if(mime.find(suffix) == mime.end())
		return mime["default"];
	else
		return mime[suffix];
}
