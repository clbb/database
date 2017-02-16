#include<iostream>
using namespace std;

#include<set>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
/*
 * set特点：
1.插入无序，遍历有序（中序）具有排序功能
2 0 1 3
0 1 2 3
2.插入重复值 防冗余－－过滤（过滤重复单词）
3.count接口 快速判断key是否存在

*/

//将普通iterator 传给 const iterator 只读 
//const_iterator
void fun(const set<int>::iterator it)
{
	set<int> s1;
	s1.insert(2);
	s1.insert(0);
	s1.insert(1);
	s1.insert(3);
	set<int>::const_iterator constIt = it;
	while(constIt != s1.end())
	{
		cout<<*constIt<<" ";
		constIt++;
	}
	cout<<endl;
	
}

void TestSet()
{
	set<int> s1;
	s1.insert(2);
	s1.insert(0);
	s1.insert(1);
	s1.insert(3);
	s1.insert(3);
	set<int>::iterator it = s1.begin();
	while(it != s1.end())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;

//	fun(it);
}

//map排序
/*
template <class K,class V>
class pair
{
	K first;
	V second;
	pair(const K& key,const V& value)
		:first(key)
		,second(value)
	{}
//就是用临时变量重新构造一下 
//实际：pair<K,V>(x,y) 与 make_pair(x,y) 相同
	template<class K,class V>
	pair<K,V> make_pair(const K& key,const V& value)
	{
		return pair<K,V>(key,value);	
	}
};
*/

void TestMap()
{
	map<string,int> m1;
//	m1.insert(pair<string,int>("string",0));
//	m1.insert(pair<string,int>("sort",1));
	m1.insert(make_pair("b",0));
	m1.insert(make_pair("a",1));
	m1.insert(make_pair("c",1));
	m1.insert(make_pair("e",1));
	
	map<string,int>::iterator it = m1.begin();
	while(it != m1.end())
	{
		cout<<it->first<<" "<<it->second<<endl;
		it++;
	}
}
//template <class K,class V>
void PrintMap(const map<string,int> &m)
{
	map<string,int>::const_iterator it1 = m.begin();
	while(it1 != m.end())
	{
		cout<<it1->first<<" "<<it1->second<<endl;
		it1++;
	}
}

void PrintVector(const vector<map<string,int>::iterator> v)
{
	vector<map<string,int>::iterator>::const_iterator it = v.begin();
	while(it != v.end())
	{
		cout<<(*it)->first<<" "<<(*it)->second<<endl;
		it++;
	}
}
string strs[] = {"sort","set","set","hash","sort"};
//使用map统计每个单词出现的次数
//找出出现次数最多的前3个
	struct Compare//降序
	{
		bool operator()(map<string,int>::iterator l,map<string,int>::iterator r)
		{
			return l->second > r->second;
		}
	};

//看这里
void Count1(string str[],size_t size)
{
	//1
	//思路：查 若在 则插入，不在 则second++
	map<string,int> countMap;
	int count = 0;
	for(int i = 0; i<size; ++i)
	{
		map<string,int>::iterator it = countMap.find(str[i]);
		if(it != countMap.end())//找到了
		{
			it->second++;//(*it).second++;
		}
		else
			countMap.insert(pair<string,int>(str[i],1));//1 表示第一次插入
	}
	//	PrintMap(countMap);
		cout<<endl;

	//2 vector
	//最多前3 vector前三
	vector<map<string,int>::iterator> v;
	map<string,int>::iterator countIt = countMap.begin();
	while(countIt != countMap.end())
	{
		v.push_back(countIt);
		countIt++;
	}
	sort(v.begin(),v.end(),Compare());
	PrintVector(v);
	cout<<endl;
	
//	//3 operator[] 
//	for(int i = 0; i<size; ++i)
//	{
//		countMap[str[i]]++;
//	}
//		PrintMap(countMap);
	//用insert的返回值
	//4	用heap 将map push_heap heap, pop_heap front  
	//string fruit[] = {"apple","banana","origin","origin","banana","apple_pie","mango","mango","mango","mango"};
	//7
	//统计水果出现次数 选出大家最喜爱的前3种
	make_heap(v.begin(),v.end(),Compare());

	cout<<v.size()<<endl;
	while(v.size() > 3)
	{	
		pop_heap(v.begin(),v.end(),Compare());
		v.pop_back();
	}
	cout<<v.size()<<endl;
	
	PrintVector(v);
}
//就是第三种 operator()
void CountPopfruit(string* str,size_t size)
{
	map<string,int> countMap;
	for(int i = 0; i<size; ++i)
	{
		countMap[str[i]]++;
	}
	PrintMap(countMap);
	
}
