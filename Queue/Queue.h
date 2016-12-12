//Queue 链表 FIFO
//
#pragma once
#include<iostream>
using namespace std;

template<class T>
struct QueueNode
{
	T _data;
	QueueNode<T>* _next;
	QueueNode(const T& data)
		:_data(data)
		,_next(NULL)
	{}
};
template<class T>
class Queue
{
public:
	typedef QueueNode<T> Node;
public:
	Queue()
		:_head(NULL)
		,_tail(NULL)
	{
	//	_head = _tail;
	}
	~Queue()
	{
		if(_head != NULL || _tail != NULL)
		{
			delete _head;//delete NULL 也没有关系，因为空也是有内容的，只有释放了非法的空间才会报错
			delete _tail;	
		}
	}
	//没有头节点的单链表分两种情况 空 不空
	void Push(const T& x)
	{
		Node* newNode= new Node(x);
		if(_head == NULL)
		{
			_tail = newNode;//尾叉
			_head = _tail;	
		}

		else
		{
			_tail->_next = newNode;//访问NULL！！SIGSEGV
			_tail = _tail->_next;
		}
	}
	void Pop()
	{
		if(_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else if(_head != NULL)
		{
			Node* del = _head;
			_head = _head->_next;
			delete del;
			del = NULL;
		}
	}
	T& Front()
	{
		return _head->_data;
	}
	T& Back()
	{
		return _tail->_data;
	}
	size_t Size()//遍历
	{
		Node*cur = _head;
		size_t count = 0;
		while(cur)
		{
			count++;
			cur = cur->_next;
		}
		return count;

	}
	bool Empty()
	{
		return (_head == NULL && _tail == NULL);	
		//	_head = _tail = NULL ???
	}
protected:
	Node* _head;
	Node* _tail;
	
};

void TestQueue()
{		
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);

	while(!q.Empty())
	{
		cout<<q.Front()<<"->";
		q.Pop();
	}
	cout<<endl;
}
