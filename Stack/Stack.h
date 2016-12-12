//stack 顺序表 LIFO
//静态 动态
//模版实现
/*
//静态
const size_t N = 10;
//#define N 7
template<class T>
class Stack
{
protected:
	int a[N];
};
//缺陷：
//stack s1 size = 10;
//stack s2 size = 20;
//不能同时满足
//优化->
template<class T,size_t N>
class Stack
{
protected:
	int a[N];
};
//知识点：这里模版的运用N叫做非类型模版参数，T是类型模版参数，并且满足数组在编译前已知数组大小的规定

*/
//动态  动态增容
#pragma once
#include<assert.h>
#include<iostream>
using namespace std;
template<class T>
class Stack
{
public:
	Stack()
		:_a(NULL)
		,_size(0)
		,_capacity(0)
	{}
	~Stack()
	{
		if(_size == 0)
			//delete[] _a;
			_a = NULL;
			_size = 0;
			_capacity = 0;
	}
	
	void Push(const T& x)
	{
		_CheakCapacity();
		_a[_size++] = x;
	}
	void Pop()
	{
		assert(_size);//防御式编程  如果用if返回值是个问题
		--_size;//懒删除 数组特有的性质
	}
	T& Top()//返回值可以被修改
	{
		return _a[_size-1];  //开区间  begin _size=1  push(1) _size=1 下标却是0
	}
	//何时使用传值 何时使用传引用
	//当该变量为作用域内临时变量 用传值 如果出了作用域（函数调用堆栈）访问会造成该变量已经释放，值被丢失
	//出作用域该变量还存在 用传引用
//	const T& Top()//返回值bu可以被修改
//	{
//		return _a[_size];
//	}
	const T& Top() const//返回值bu可以被修改 并且this指针所指向对象也不能被修改  ？
	{
		return _a[_size];
	}
	size_t Size()
	{
		return _size;
	}
	bool Empty()
	{
		return _size == 0;
	}
protected:
	void _CheakCapacity()
	{
		if( _size >= _capacity)
		{
			size_t newcapacity = _capacity*2+3;
			T* _tmp = new T[newcapacity];
			if(_a)
			{
			//类型萃取？？？？不会
			//	memcpy(_tmp,_a,_capacity);
			//	如果拷贝对象是string时会出现垂悬指针的问题->野指针
				for(int i = 0; i < _size;++i)
				{
					_tmp[i] = _a[i];
				}
				delete[] _a;
			}
				_a = _tmp;
				_capacity = newcapacity;
		}
	}

protected:
	T* _a;
	size_t _size;//top
	size_t _capacity;

};

void TestStack()
{
	Stack<int> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);

	while(!s1.Empty())
	{
		cout<<s1.Top()<<" ";
		s1.Pop();
	}
	cout<<endl;
	
}
