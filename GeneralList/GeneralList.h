#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

//广义表
//非线性---线性表的扩展
//n个有限元素
//表中有表 递归

enum Type
{
	HEAD,
	VALUE,
	SUB,
};
struct GeneralLstNode
{
	Type _type;
	GeneralLstNode* _next;
	union
	{
		char _value;//VALUE 用
		GeneralLstNode* _subLink;//SUB 用
	};//size＝4
	GeneralLstNode(Type type, const char value = 0)
		:_type(type)
		,_next(NULL)
	{
		if(type == VALUE)
			_value = value;
		if(type == SUB)
			_subLink = NULL;
	}
};

class GeneralList
{
	typedef GeneralLstNode Node;
public:
	GeneralList(const char* a)
	{
		_head = _Create(a);
	}
	GeneralList(GeneralList& g)
	{
		_head = _Copy(g._head);
	}
	~GeneralList()
	{
		_Destroy(_head);
		_head = NULL;
	}
	//Node* operator=(GeneralList& g)
	//{
	//	if(*this != g._head)
	//	{
	//		GeneralList tmp(g);
	//		_Destroy(_head);
	//		swap()
	//	}
	//	return *this;
	//}
	Node*& operator=(GeneralList g)
	{
		swap(_head,g._head);
		return _head;
	}
	void Print()
	{
		_Print(_head);
		cout<<endl;
	}
	size_t Size()
	{
		return _Size(_head);
	}
	size_t Depth()
	{
		return _Depth(_head);
	}
protected:
	size_t _Depth(Node* head)
	{
		Node* cur = head;
		int Maxdepth = 1;
		int depth = 0;
		while(cur)
		{
			if(cur->_type == SUB)
			{
				depth = _Depth(cur->_subLink);
				if(depth+1 > Maxdepth)
				Maxdepth = depth+1;
			}
			cur = cur->_next;
		}
		return Maxdepth;
	}
	size_t _Size(Node* head)
	{
		Node* cur = head;
		int count = 0;
		while(cur)
		{
			if(cur->_type == VALUE)
			{
				count++;
			}
			else if(cur->_type == SUB)
			{
				count+=_Size(cur->_subLink);
			}

			cur = cur->_next;
		}
		return count;
	}
	void _Destroy(Node* head)
	{
		Node* cur = head;
		while(cur && cur->_next)
		{
			Node* del = cur;
			cur = cur->_next;
			if(cur->_type == SUB)
				_Destroy(cur->_subLink);
			delete del;

		}
	}
	bool IsValue(const char a)
	{
		if((a >= 0 && a <= 9)
			||(a >= 'a' && a <= 'z')
			||(a >= 'A' && a <= 'Z'))
			return true;
		return false;

	}
	Node* _Copy(Node* head)
	{
		Node* newHead = new Node(HEAD);
		Node* cur = head->_next;
		Node* newCur = newHead;
		while(cur)
		{
			if(cur->_type == VALUE)
			{
				newCur->_next = new Node(VALUE,cur->_value);
				newCur = newCur->_next;
			}
			if(cur->_type == SUB)
			{
				newCur->_next = new Node(SUB);
				newCur = newCur->_next;
				newCur->_subLink = _Copy(cur->_subLink);
			}
			cur = cur->_next;
		}
		return newHead;

	}
	Node* _Create(const char*& s)
	{
		assert(*s == '(');
		Node* head = new Node(HEAD);
		Node* cur = head;
		s++;
		//(a,b)
		//(a,b,(c,d),(e,(f),g))
		while(*s)
		{
			if(*s == '(')
			{
				Node* subNode  = new Node(SUB);
				cur->_next = subNode; 
				cur = cur->_next;
				subNode->_subLink = _Create(s);

			}
			else if(IsValue(*s))
			{
				Node* valueNode  = new Node(VALUE,*s);
				cur->_next = valueNode; 
				cur = cur->_next;
				s++;
			}
			else if(*s == ')')
			{
				s++;
				break;
			}
			else
				s++;

		}
		return head;
	}
	void _Print(Node* head)
	{
		assert(head && head->_type == HEAD);
		Node* cur = head;
		while(cur)
		{
			if(cur->_type == HEAD)
				cout<<"(";
			if(cur->_type == VALUE)
			{
				cout<<cur->_value;
				if(cur->_next)
					cout<<",";
			}
			if(cur->_type == SUB)
			{
				_Print(cur->_subLink);
				if(cur->_next)
					cout<<",";
			}
			cur = cur->_next;
		}
		cout<<")";
	}


protected:
	Node* _head;
};

void Test1()
{
	char* a1 = "(a,b)";
	GeneralList g1(a1);
	g1.Print();
	cout<<g1.Size()<<endl;
	cout<<g1.Depth()<<endl;

	char* a2 = "(a,b,(c,d),(e,(f),g))";
	GeneralList g2(a2);
	//GeneralList g2(g1);
	g2.Print();
	cout<<g2.Size()<<endl;
	cout<<g2.Depth()<<endl;

	

	char* a3 = "(a,b,(c,d))";
	GeneralList g3(a3);
	g3.Print();
	cout<<g3.Size()<<endl;
	cout<<g3.Depth()<<endl;
	g2 = g3;
	g2.Print();

}
