#pragma once
#include<assert.h>
#include<iostream>
using namespace std;

void Print(int a[],size_t size)
{
	for(size_t i = 0; i<size; ++i)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

template <class T>
struct Less
{
	bool operator()(const T& l,const T& r)
	{
		return l<r;
	}
};
template <class T>
struct Greater
{
	bool operator()(const T& l,const T& r)
	{
		return l>r;
	}
};
template<class T,class Compare = Less<T> >
void InsertSort(T a[],size_t size)
{
	assert(a);

	for(size_t i = 1; i<size; ++i)
	{
		int end = i-1;
		T tmp = a[i];
		while(end >= 0)
		{
			if(Compare()(tmp,a[end]))//升序 
			{
				a[end+1] = a[end];
				end--;
			}
			else
				break;
		}
		a[end+1] = tmp;
	}
}

void Test1()
{
	int a[] = {5,2,7,1,3,8,4,9,0,6};
	InsertSort(a,10);
	Print(a,10);
}

void ShellSort(int *a,size_t size)
{
	assert(a);

	int gap = size;
	while(gap > 1)
	{
		gap = gap / 3 + 1; 
		for(size_t i = gap; i<size; ++i)
		{
			int end = i-gap;
			int tmp = a[i];
			while(end >= 0)
			{
				if(a[end] > tmp)
				{
					a[end+gap] = a[end];
					end-=gap;
				}
				else
					break;
			}
			a[end+gap] = tmp;
		}
	}
	
}

void Test2()
{
	int a[] = {5,2,7,1,3,8,4,9,0,6};
	ShellSort(a,10);
	Print(a,10);
}
