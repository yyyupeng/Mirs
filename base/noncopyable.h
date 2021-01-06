#pragma once

class noncopyable
{
protected:
	noncopyable() = default;
	~noncopyable() = default;

public:
    //禁止拷贝和赋值
	noncopyable(const noncopyable&) = delete;
	void operator=(const noncopyable&) = delete;
};
