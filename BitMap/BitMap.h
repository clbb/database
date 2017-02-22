#pragma once
#include<iostream>
#include<vector>
using namespace std;

class BitMap
{
public:
	BitMap(size_t N = 1024)
	//	:_size(1024)
	{
		_array.resize((N>>5)+1);//多开一个空间，33/32 应该放在下一个字节处
	}
	void Set(size_t value)//只能表示正整数
	{
		size_t index = value >> 5;
		size_t pos = value % 32;
		
		_array[index] |= (1<<pos);
	}
	void Reset(size_t value)
	{
		size_t index = value >> 5;
		size_t pos = value % 32;
	
		_array[index]  &= ~(1<<pos);	
	}
	bool Test(size_t value)
	{
		size_t index = value >> 5;
		size_t pos = value % 32;
		
		return _array[index]	 &= (1<<pos);//该数存在 返回值非0 该数不存在 返回值0
	}

protected:
	vector<size_t> _array;
	size_t _size;//并不表明Bitmap的大小，只是为了方便标明size_t的范围
};

void Test1()
{
	BitMap bt(1024);
	bt.Set(32);
	bt.Set(2);
	bt.Set(3);
	bt.Set(33);

	cout<<"2 "<<bt.Test(2)<<endl;
	cout<<"3 "<<bt.Test(3)<<endl;
	cout<<"32 "<<bt.Test(32)<<endl;
	cout<<"34 "<<bt.Test(34)<<endl;

	
}
