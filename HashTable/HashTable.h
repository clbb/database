#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<assert.h>
//const size_t EXIT = 0;
enum Statue
{
	EMPTY,
	DELETE,
	EXIST
};

template <class K,class V>
struct HashNode
{
	K _key;
	V _value;
	Statue _statue;

	HashNode(const K& key = K(),const V& value = V())
		:_key(key)
		,_value(value)
		,_statue(EMPTY)	
	{}
};

template<class K>
struct __HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};
template<>
struct __HashFunc<string>
{
	size_t BKDRHash(const char* str)
	{
		register size_t hash = 0;
		while(*str)
		{
			hash = hash * 131 +*str;
			++str;
		}
		return hash;
	}
	size_t operator()(const string& s)
	{
		return BKDRHash(s.c_str());
	}
};

template<class K,class V,class HashFunc = __HashFunc<K> >
class HashTable
{
	typedef HashNode<K,V> Node;
public:
	HashTable(size_t size)
		:_size(0)
	{
		assert(size>0);
		_table.resize(size);
	}
	pair<Node*,bool> Insert(const K& key,const V& value)//返回值为了方便重载（）
	{
		_CheckCapacity();
		//插满了
		//if(_size == _table.size())
		//{
		//	_table.resize(_size);
		//	return make_pair((Node*)NULL,false);
		//}
				
		//未满 线性探测
		//看status=EXIST 存下一位
		//剩下状态直接插入 
		int index = _HashFunc(key);//除留余数
		while(_table[index]._statue == EXIST)
		{
			//线性探测
			if(index == _table.size())
			{
				index = 0;
			}
			index++;
		}	
		_table[index]._statue = EXIST;
		_table[index]._key = key;
		_table[index]._value = value;
		_size++;
		return make_pair(&_table[index],true);
	}

	Node* Find(const K& key)
	{
		size_t index = _HashFunc(key);
		//status = EXIST时  的要跳过
		while(_table[index]._statue == EXIST)
		{
			if(index == _table.size())
			{
				index = 0;
			}
			if(_table[index]._key == key)
				return &_table[index];
			else if(_table[index]._key != key)
			{
				index++;
			}
			cout<<"已经删除或没插入"<<endl;
			return NULL;
		}
		cout<<"没有插入这个值"<<endl;
		return NULL;
	}

	bool Remote(const K& key)
	{
		if(_table.empty())
			return false;

		Node* pos = Find(key);

		_table[pos->_statue] = DELETE;
		_size--;
		return true;
	}
	
protected:
	void Swap(HashTable<K,V,HashFunc> t)
	{
		_table.swap(t._table);
	}
	size_t _HashFunc(const K& key)
	{
		return key % _table.size();
	}
	void _CheckCapacity()
	{
		if(_table.empty())
		{
			_table.resize(7);
			return;
		}
		//载荷因子 < 0.7
		//现代写法
		if(_size*10 / _table.size() >= 7)
		{
			size_t newSize = _table.size() *2;
			HashTable<K,V,HashFunc> tmp(newSize);
			for(size_t i = 0; i<_table.size(); ++i)
			{
				if(_table[i]._statue == EXIST)
				{
					tmp.Insert(_table[i]._key,_table[i]._value);
				}
			}
			this->Swap(tmp);
		}
		
	}
protected:
	vector<Node> _table;
	size_t _size;
};

void Test()
{
	HashTable<int,int> ht(10);
	ht.Insert(89,0);
	ht.Insert(18,0);
	ht.Insert(49,0);
	ht.Insert(58,0);
	ht.Insert(9,0);
	ht.Remote(58);

	ht.Find(9);
	
	
}
