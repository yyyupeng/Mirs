#include "LFUCache.h"

void KeyList::init(int fq)
{
	frequency = fq;
	head = last = newElement<Node<Key>>();
	head->setNext(NULL);
}

void KeyList::destory()
{
	while(head)
    {
		key_node pre = head;
		head = head->getNext();
		deleteElement(pre);
	}
}

int KeyList::getFrequency()
{
	return frequency;
}

void KeyList::add(key_node& node)
{
	if(head->getNext())
    {
		head->getNext()->setPre(node);
	}
	else
		last = node;
	node->setNext(head->getNext());
	node->setPre(head);
	head->setNext(node);
}

void KeyList::del(key_node& node)
{
	node->getPre()->setNext(node->getNext());
    if(node->getNext())
        node->getNext()->setPre(node->getPre());
    else
        last = node->getPre();
}

bool KeyList::isEmpty()
{
	return head == last;
}

key_node KeyList::getLast()
{
	return last;
}

void LFUCache::init()
{
	capacity = getconf().getcapacity();
	head = newElement<Node<KeyList>>();
	head->getValue().init(0);
	head->setNext(NULL);
}

LFUCache::~LFUCache()
{
	while(head)
    {
		frequency_node pre = head;
		head = head->getNext();
		pre->getValue().destory();
		deleteElement(pre);
	}
}

void LFUCache::addfrequency(key_node& nowk, frequency_node& nowf)
{
	frequency_node next_;
    //特殊情况判断
	if(!nowf->getNext() || nowf->getNext()->getValue().getFrequency() != nowf->getValue().getFrequency() + 1)
    {
		next_ = newElement<Node<KeyList>>();
		next_->getValue().init(nowf->getValue().getFrequency() + 1);
		if(nowf->getNext())
			nowf->getNext()->setPre(next_);
		next_->setNext(nowf->getNext());
		nowf->setNext(next_);
		next_->setPre(nowf);
	}
	else
		next_ = nowf->getNext();
	fmap[nowk->getValue().key] = next_;
	if(nowf != head)
    {
		nowf->getValue().del(nowk);
	}
	next_->getValue().add(nowk);
    if(nowf != head && nowf->getValue().isEmpty())
		del(nowf);
}

void LFUCache::del(frequency_node& node)
{
	node->getPre()->setNext(node->getNext());
	if(node->getNext())
    	node->getNext()->setPre(node->getPre());
    node->getValue().destory();
	deleteElement(node);
}

bool LFUCache::get(string& key, string& value)
{
	if(!capacity)
		return false;
	MutexLockGuard lock(mutex);
	if(fmap.find(key) != fmap.end())
    {
		//命中
		key_node nowk = kmap[key];
		frequency_node nowf = fmap[key];
		value += nowk->getValue().value;
		addfrequency(nowk, nowf);   //更新节点频率
		return true;
	}
	return false;
}

void LFUCache::set(string& key, string& value)
{
	if(!capacity)
		return;
	MutexLockGuard lock(mutex);
    //容量满了-->删除频率最小且最久未使用的节点
	if(kmap.size() == capacity)
    {
		frequency_node headnxt = head->getNext();
		key_node last = headnxt->getValue().getLast();
		headnxt->getValue().del(last);
		kmap.erase(last->getValue().key);
		fmap.erase(last->getValue().key);
		deleteElement(last);
		if(headnxt->getValue().isEmpty())
			del(headnxt);
	}
    //添加该节点到相应频率的链中
	key_node nowk = newElement<Node<Key>>();
	nowk->getValue().key = key;
	nowk->getValue().value = value;
	addfrequency(nowk, head);
	kmap[key] = nowk;
}

LFUCache& getCache()
{
	static LFUCache cache;
	return cache;
}
