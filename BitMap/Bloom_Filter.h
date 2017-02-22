#pragma once
#include<string>
#include"HashFunc.h"
#include"BitMap.h"
//用于字符串的快速查找
template<class K>
struct __HashFunc1
{
	bool operator()(const K& s)
	{
		return BKDRHash(s.c_str());
	}
};
template<class K>
struct __HashFunc2
{
	bool operator()(const K& s)
	{
		return SDBMHash(s.c_str());
	}
};
template<class K>
struct __HashFunc3
{
	bool operator()(const K& s)
	{
		return RSHash(s.c_str());
	}
};
template<class K>
struct __HashFunc4
{
	bool operator()(const K& s)
	{
		return APHash(s.c_str());
	}
};
template<class K>
struct __HashFunc5
{
	bool operator()(const K& s)
	{
		return JSHash(s.c_str());
	}
};

template<class K = string,
class HashFunc1 = __HashFunc1<K>,
class HashFunc2 = __HashFunc2<K>,
class HashFunc3 = __HashFunc3<K>,
class HashFunc4 = __HashFunc4<K>,
class HashFunc5 = __HashFunc5<K> >
class BloomFilter
{
public:
	BloomFilter(size_t num)
		:_bt(num*5*2)//每个字符串用5个值来标记，也就是用5个字符串哈希函数来计算，乘2是为了在数据量小的情况下减少误判（通过空间的增大）
		,_size(num)
	{}
	void Set(const string& s)
	{
		size_t hash1 = HashFunc1()(s);
		size_t hash2 = HashFunc2()(s);
		size_t hash3 = HashFunc3()(s);
		size_t hash4 = HashFunc4()(s);
		size_t hash5 = HashFunc5()(s);
		
		_bt.Set(hash1);
		_bt.Set(hash2);
		_bt.Set(hash3);
		_bt.Set(hash4);
		_bt.Set(hash5);
	}
	bool Test(const string& s)
	{
		size_t hash1 = HashFunc1()(s);
		if(!_bt.Test(hash1))
			return true;
		size_t hash2 = HashFunc2()(s);
		if(_bt.Test(hash2))
			return true;
		size_t hash3 = HashFunc3()(s);
		if(_bt.Test(hash3))
			return true;
		size_t hash4 = HashFunc4()(s);
		if(_bt.Test(hash4))
			return true;
		size_t hash5 = HashFunc5()(s);
		if(_bt.Test(hash5))
			return true;
		return false;
	}
protected:
	BitMap _bt;
	size_t _size;
};

void Test()
{
	BloomFilter<> b1(30);  
    b1.Set("www.baidu.com");  
    b1.Set("www.sina.con");  
    b1.Set("www.taobao.com");  

    cout << b1.Test("www.baidu.com") << endl;  
    cout << b1.Test("dnsjdasjkdsjakdjas") << endl;  
}
