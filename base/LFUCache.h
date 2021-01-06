#pragma once

#include "Conf.h"
#include "Mutex.h"
#include "MemoryPool.h"
#include <unordered_map>
#include <string>

using std::string;

template<typename T>
class Node
{
public:
	void setPre(Node *p)
    {
		pre = p;
	}
	void setNext(Node *n)
    {
		next = n;
	}
	Node *getPre()
    {
		return pre;
	}
	Node *getNext()
    {
		return next;
	}
	T& getValue()
    {
		return value;
	}	

private:
	T value;
	Node *pre;
	Node *next;
};

struct Key
{
	string key, value;
};
typedef Node<Key> *key_node;

class KeyList
{
public:
	void init(int fq);
	void destory();
	int getFrequency();
	void add(key_node& node);
	void del(key_node& node);
	bool isEmpty();
	key_node getLast();

private:
	int frequency;
	key_node head;
	key_node last;
};
typedef Node<KeyList> *frequency_node;

class LFUCache
{
public:
	void init();
	~LFUCache();
	bool get(string& key, string& value);   //通过key返回value并进行LFU操作
	void set(string& key, string& value);   //更新LFU缓存

private:
	frequency_node head;
	int capacity;
	MutexLock mutex;	
	std::unordered_map<string, key_node> kmap;  //key到key_node的映射
	std::unordered_map<string, frequency_node> fmap; //key到frequency_node的映射
	
	void addfrequency(key_node& nowk, frequency_node& nowf);	
	void del(frequency_node& node);
};

LFUCache& getCache();

