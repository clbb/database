#pragma once
#include<iostream>
#include<stack>
#include <assert.h>
using namespace std;

enum Type
{
	OP_SYMBOL,
	OP_NUM,
	ADD,
	SUB,
	DIV,
	MUL,
};

typedef struct Cell
{
	Type _type;
	int _value;
}Cell;

int CountRPN(Cell *RPN,size_t n) // Cell* RPN  sizeof(RPN)/sizeof(RPN[0]) = 4/42亿 ～ 0 loop一次
{
	stack<int> s;
	Cell* cur = RPN;
	int count = 0;
	while(count < n)
	{
		if(cur->_type == OP_NUM)
		{
			s.push(cur->_value);
			cur++;
			count++;
		}
		else if(cur->_type == OP_SYMBOL )
		{
			int right = s.top();
			s.pop();
			int left = s.top();
			s.pop();
			int tmp = 0;
			switch(cur->_value)
			{
			case ADD:
				tmp = left + right;
				break;
			case SUB:
				tmp = left -  right;
				break;
			case DIV:
				tmp = left /  right;
				break;
			case MUL:
				tmp = left *  right;
				break;
			default:
				assert(false);
				throw 
					std::invalid_argument("rpn Error!");
				break;
		}
		s.push(tmp);
		count++;
		cur++;

		}
	}
	return s.top();
}
void TestRPN()
{
	Cell RPN[]={{OP_NUM,12},
				{OP_NUM,3} ,
				{OP_NUM,4},
				{OP_SYMBOL,ADD},
				{OP_SYMBOL,MUL},
				{OP_NUM,6},
				{OP_SYMBOL,SUB},
				{OP_NUM,8},
				{OP_NUM,2},
				{OP_SYMBOL,DIV},
				{OP_SYMBOL,ADD}
				};
	int n = sizeof(RPN)/sizeof(RPN[0]);//这里的才是数组真正的大小
	cout<<CountRPN(RPN,n)<<endl;
}

