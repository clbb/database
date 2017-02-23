#pragma once
#include<string>
#include"HashFunc.h"
#include"BitMap.h"
//用于字符串的快速查找
struct __HashFunc1
{
	size_t operator()(const string& s)
	{
		return BKDRHash(s.c_str());
	}
};
struct __HashFunc2
{
	size_t operator()(const string& s)
	{
		return SDBMHash(s.c_str());
	}
};
struct __HashFunc3
{
	size_t operator()(const string& s)
	{
		return RSHash(s.c_str());
	}
};
struct __HashFunc4
{
	size_t operator()(const string& s)
	{
		return APHash(s.c_str());
	}
};
struct __HashFunc5
{
	size_t  operator()(const string& s)
	{
		return JSHash(s.c_str());
	}
};

template<class K = string,
class HashFunc1 = __HashFunc1,
class HashFunc2 = __HashFunc2,
class HashFunc3 = __HashFunc3,
class HashFunc4 = __HashFunc4,
class HashFunc5 = __HashFunc5 >
class BloomFilter
{
public:
	BloomFilter(size_t num)
		:_bt(num*5*2)//每个字符串用5个值来标记，也就是用5个字符串哈希函数来计算，乘2是为了在数据量小的情况下减少误判（通过空间的增大）
		,_size(num*5*2)
	{}
	void Set(const string& s)
	{
		size_t hash1 = HashFunc1()(s) % _size;
		size_t hash2 = HashFunc2()(s) % _size;
		size_t hash3 = HashFunc3()(s) % _size;
		size_t hash4 = HashFunc4()(s) % _size;
		size_t hash5 = HashFunc5()(s) % _size;
		
		_bt.Set(hash1);
		_bt.Set(hash2);
		_bt.Set(hash3);
		_bt.Set(hash4);
		_bt.Set(hash5);
	}
	bool Test(const string& s)
	{
		size_t hash1 = HashFunc1()(s) % _size;
		if(!_bt.Test(hash1))
			return false;
		size_t hash2 = HashFunc2()(s) % _size;
		if(!_bt.Test(hash2))
			return false;
		size_t hash3 = HashFunc3()(s) % _size;
		if(!_bt.Test(hash3))
			return false;
		size_t hash4 = HashFunc4()(s) % _size;
		if(!_bt.Test(hash4))
			return false;
		size_t hash5 = HashFunc5()(s) % _size;
		if(!_bt.Test(hash5))
			return false;
		return true;
	}
protected:
	BitMap _bt;
	size_t _size;
};

void Test()
{
	BloomFilter<> b1(100);  
    b1.Set("www.baidu.com");  
    b1.Set("www.sina.con");  
    b1.Set("www.taobao.com");  

    cout << b1.Test("www.baidu.com") << endl;  
    cout << b1.Test("dnsjdasjkdsjakdjs") << endl;  
}
