#pragma once
#include<iostream>
using namespace std;
#include<stack>
#include<queue>
#include<assert.h>
//实现一个栈，要求实现Push(入栈),Pop(出栈),Min(返回最小值的操作)的时间复杂度为O(1)

template <class T>
class Stack
{
public:
	void Push(const T& x)
	{
		sOne.push(x);
	}
	void Pop()
	{
		sOne.pop();
	}
	T& Min()
	{
		T min = sOne.top();
		sOne.pop();
		T cur = sOne.top();
		while(!sOne.empty())
		{
			if(min > cur)
				swap(cur,min);

			sMin.push(cur);
			
			sOne.pop();
			if(!sOne.empty())
			cur = sOne.top();
		}
		sMin.push(min);
		return sMin.top();
	}
	T& Top()
	{	
		if(sOne.empty())
		{
			cout<<"已经找过最小元素，请重新插入";
			exit(1);
		}
		return sOne.top();
	}
private:
	stack<T> sOne;
	stack<T> sMin;
	
};

void TestMin()
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	
	cout<<"sMin.Top: "<<s.Min()<<endl;
//	s.Min();
	s.Top();
//	s.Pop();
//	cout<<"sOne.Top: "<<s.Top()<<endl;
//	s.Pop();
//	cout<<"sOne.Top: "<<s.Top()<<endl;
//	s.Pop();
//	cout<<"sOne.Top: "<<s.Top()<<endl;
//	s.Pop();
	
	
}
//2
//思路：用两个栈
//由于栈只能访问栈顶的特性，最小值栈的栈顶用来存放min，为了统一插入与删除
//插入：比较插入元素与现有数据栈顶的大小，value > data.top 重复插入小的 也就是data.top
//删除：非空，统一删除
//即便minstack中有重复的数据，也可保障push pop操作统一 取完最小值后还可访问top 
template<class T>
class MinStack
{
public:
	void Push(const T& x)
	{	
		datastack.push(x);
		if(minstack.empty() || x < minstack.top())
		{
			minstack.push(x);
		}
		minstack.push(minstack.top());
	}
	void Pop()
	{	
		if(!datastack.empty() && !minstack.empty())
		{
			datastack.pop();
			minstack.pop();
		}
	}
	T& Min()
	{
		assert(!minstack.empty());
		return minstack.top();
	}
	T& Top()
	{
		assert(!datastack.empty());
		return datastack.top();
	}
private:
	stack<T> datastack;
	stack<T> minstack;
};
void TestMin2()
{
	MinStack<int> m;
	m.Push(1);
	m.Push(2);
	m.Push(3);
	m.Push(4);
	cout<<"MIN: "<<m.Min()<<endl;
	cout<<"Top: "<<m.Top()<<endl;
	
	m.Pop();
	cout<<"MIN: "<<m.Min()<<endl;
	cout<<"Top: "<<m.Top()<<endl;
}
//使用两个栈实现一个队列
//思路：一个存数 一个作为临时容器
//插入：直接插
//删除：由于队列头删尾插 将数据倒入临时容器，再删除tmp.top
template<class T>
class Queue
{
public:
	void Push(const T& x)
	{
		datastack.push(x);
	}
	void Pop()
	{
		if(tmpstack.empty())
		{
			while(!datastack.empty())
			{
				T tmp = datastack.top();
				tmpstack.push(tmp);
				datastack.pop();
			}
		}
		tmpstack.pop();
		
		
	}
	T& Front()
	{
		if(tmpstack.empty())
		{
			while(!datastack.empty())
			{
				T tmp = datastack.top();
				tmpstack.push(tmp);
				datastack.pop();
			}
		}
		return tmpstack.top();
	}
	T& Back()
	{
		if(datastack.empty())
		{
			while(!tmpstack.empty())
			{
				T tmp = tmpstack.top();
				datastack.push(tmp);
				tmpstack.pop();
			}
		}
		return datastack.top();
	}
	bool Empty()
	{
		return tmpstack.empty() && datastack.empty();	
	}
	size_t Size()
	{
		if(!tmpstack.empty())
			return tmpstack.size();
		return datastack.size();
	}
private:
	stack<T> datastack;
	stack<T> tmpstack;
};
void TestTwoSQ()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	
	cout<<"b "<<q.Back()<<endl;
	cout<<"f "<<q.Front()<<endl;
	q.Pop();
	cout<<"b "<<q.Back()<<endl;
	cout<<"f "<<q.Front()<<endl;
	q.Push(5);
	cout<<"b "<<q.Back()<<endl;
	cout<<"f "<<q.Front()<<endl;
		
	cout<<"size: "<<q.Size()<<endl; 
	
}
//使用两个队列实现一个栈
//思路：一个存数 一个作为临时容器
//插入：直接插
//删除：由于栈只能删除栈顶元素，将数据插入临时容器在，剩下一个出队data.pop
template<class T>
class QStack
{
public:
	void Push(const T& x)
	{
		if(dataqueue.empty() && dataqueue.empty())
			dataqueue.push(x);
		else if(!tmpqueue.empty())
			dataqueue.push(x);
		else
			dataqueue.push(x);
	}
	void Pop()
	{
		assert(!tmpqueue.empty() || !dataqueue.empty());
		if(!dataqueue.empty())
		{
			while(dataqueue.size() > 1)
			{
				T tmp = dataqueue.front();
				tmpqueue.push(tmp);
				dataqueue.pop();
			}
			dataqueue.pop();
		}
		else
		{
			while(tmpqueue.size() > 1)
			{
				T tmp = tmpqueue.front();
				dataqueue.push(tmp);
				tmpqueue.pop();
			}
			tmpqueue.pop();
		}
	}
	size_t Size()
	{
		return tmpqueue.size() + dataqueue.size();
	}
	T& Top()
	{
		assert(!dataqueue.empty() || !tmpqueue.empty());
		if(!tmpqueue.empty())
			return tmpqueue.back();
		else
			return dataqueue.back();
	}
	bool Empty()
	{
		return tmpqueue.empty() && dataqueue.empty();
	}
private:
	queue<T> dataqueue;
	queue<T> tmpqueue;
};

void TestQS()
{
	QStack<int> qs;
	qs.Push(1);
	qs.Push(2);
	cout<<qs.Top()<<endl;
	qs.Pop();
	cout<<qs.Top()<<endl;
	qs.Pop();
}
//元素岀栈，入栈顺序的合法性,如入栈的序列(1,2,3,4,5),岀栈序列为(4,5,3,1)
template<class T>
bool IsInStackRigthOrder(vector<T> in,vector<T> out)
{
	assert(in.size() && out.size());

	stack<T> s;
	int j = 0;
	for(int i = 0; i<in.size(); ++i)
	{
		s.push(in[i]);
	
		while(!s.empty() && s.top() == out[j])
		{
			s.pop();
			j++;
		}
	}
	return s.empty();
}

void TestJuge()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	vector<int> v2;
//	v2.push_back(5);
//	v2.push_back(4);
//	v2.push_back(3);
//	v2.push_back(2);
//	v2.push_back(1);
	v2.push_back(4);
	v2.push_back(5);
	v2.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	cout<<IsInStackRigthOrder(v1,v2)<<endl;
}

//一个数组实现两个栈
//思路：以中间为界限，从两边向中间增长，优点：比下面👇 两种节省空间 避免反复增容
//相当于给stack1 stack2预留空间
//别的思路：从中间开始，向两头增长;还有奇数放stack1,偶数放stack2 这两种思路都有不同程度空间的浪费
//size1 size2 分别指向栈顶元素的下一个位置
//
template<class T>
class DoubleStack
{
public:
	DoubleStack()
		:v(new T[2])
		,size1(0)
		,size2(1)
		,capacity(2)
	{}

	void PushStack1(const T& x)
	{
		Capacity();
		v[size1++] = x;
	}
	void PushStack2(const T& x)
	{
		Capacity();
		v[size2--] = x;	
	}
	void PopStack1()
	{   //size > 0 代表栈为空吗 ??? 
		assert(size1 > 0);
		size1--;
	}
	void PopStack2()
	{
		assert (size2 < capacity - 1);
		size2++;
	}
	void DisplayStack1()
	{
		if(size1 > 0)
		{
			//拿size当top用
			for(int i = size1 - 1; i>=0; --i)
			{
				cout<<"Stack1 "<<v[i]<<" ";
			}
			cout<<endl;
		}
		//	cout<<size1<<endl;
	}
	void DisplayStack2()
	{
		for(int i = size2 + 1; i < capacity; ++i)
		{
			cout<<"Stack2 "<<v[i]<<" ";
		}
		cout<<endl;
	//	cout<<size2<<endl;
	}
	T& Top1()
	{	
		return size1;
	}
	T& Top2()
	{
		return size2;
	}
private:
	void Capacity()
	{
		if(size1 == size2)
		{
			size_t new_capacity = capacity*2+3;
			cout<<"newC:"<<new_capacity<<endl;
			T* tmp = new T [new_capacity];
			int k = capacity - 1;
			for(int i = 0; i<size1; ++i)
			{
				tmp[i] = v[i];
			}

			for(int i = capacity-1; i>size2; --i)
			{
				tmp[k] = v[i];
				k--;
			}
			delete []v;
			
		//	size2 = k+1;
			size2 = new_capacity - (capacity - size2);//?	
			cout<<"C:"<<capacity<<endl;
			capacity = new_capacity;
			v = tmp;
		}
	}

private:
	T* v;
	size_t size1;
	size_t size2;
	size_t capacity;
};

void TestDS()
{
	DoubleStack<int> s;
	s.PushStack1(1);
	s.PushStack1(2);
	s.PopStack1();
	s.PopStack1();
	s.PushStack2(3);
	s.PushStack2(4);
	s.PopStack2();
	s.PopStack2();
	s.DisplayStack1();
	s.DisplayStack2();
}
