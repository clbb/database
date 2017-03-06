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
//template<class T,class Compare = Less<T> >
template<class T, template<class> class Compare = Less >
void InsertSort(T a[],size_t size)
{
	assert(a);

	for(size_t i = 1; i<size; ++i)
	{
		int end = i-1;
		T tmp = a[i];
		while(end >= 0)
		{
			if(Compare<T>()(tmp,a[end]))//升序 
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


void AdjustDown(int* a,size_t n,int parent)
{
	int child = 2*parent+1;
	while(child < n)
	{
		if(child+1 < n && a[child+1] > a[child])
			child++;
		if(a[child] > a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = parent*2+1;
		}
		else
			break;
	}
}


void HeapSort(int *a,size_t size)
{	
	assert(a);

	for(int i = (size-1-1)/2; i>=0; --i)
	{
		AdjustDown(a,size,i);
	}

	int end = size-1;
	while(end > 0)
	{
		swap(a[end],a[0]);
		AdjustDown(a,end,0);
		--end;
	}
}

void Test3()
{
	int a[] = {9,5,4,9,3,6,8,7,1,0};
//	int a[] = {5,2,7,1,3,8,4,9,0,6};
	HeapSort(a,10);
	Print(a,10);
}

void SelectSort(int* a,size_t n)
{
	assert(a);
	int begin = 0;
	int minIndex;
	while(begin < n)
	{
		minIndex = begin;
		for(int i = begin+1; i<n; ++i)
		{
			if(a[minIndex] > a[i])//找最小的
				minIndex = i;
		}
		if(minIndex != begin)
			swap(a[minIndex],a[begin]);
		begin++;
	}
	
}
void SelectSortOP(int* a,size_t n)
{
	assert(a);

	int left = 0;
	int right = n-1;
	int minIndex;
	int maxIndex;
	while(left < right)
	{
		minIndex = left;
		maxIndex = left;
		for(int i = left; i <= right; ++i)
		{
			if(a[minIndex] > a[i])
				minIndex = i;
			if(a[maxIndex] < a[i])
				maxIndex = i;
		}
		swap(a[minIndex],a[left]);
		if(maxIndex == left)
			maxIndex = minIndex;
		swap(a[maxIndex],a[right]);
		++left;
		--right;
	}	
	
}

void Test5()
{
	int a[] = {5,2,7,1,0,8,4,9,0,6};
	SelectSort(a,sizeof(a)/sizeof(a[0]));
	Print(a,sizeof(a)/sizeof(a[0]));
}

//左右指针法
int Partion(int *a,int left,int right)
{
	
	int key = right;
	while(left < right)
	{
		while(left < right && a[left] <= a[key])//
		{
			++left;
		}
		while(left < right && a[right] >= a[key])
		{
			right--;
		}
		swap(a[left],a[right]);
	}
//	a[left] = a[key];
	swap(a[left],a[key]);
	return left;
}

//三数取中法
int GetMid(int* a,int left,int right)
{
	int mid = left + ((right-left)>>1);
	//left mid right
	if(left < right)
	{
		if(left < mid)
			return mid;
		else if(mid < left)
			return left;
		else
			return right;
	}
	// mid left right
	if(mid < right)
	{
		if(mid < left)
			return left;
		else if(left < mid)
			return mid;
		else
			return right;
	}
	// right mid left 
	if(right < left)
	{
		if(right < mid)
			return mid;
		else if(mid <right)
			return right;
		else
			return left;
	}
	return -1;
}

//挖坑法
int Partion1(int* a,int left,int right)
{
	int mid = GetMid(a,left,right);
	swap(a[mid],a[right]);
	
	int key = a[right];
	while(left < right)
	{
		while(left < right && a[left] <= key)
			++left;
		swap(a[left],a[right]);
		while(left <right && a[right] >= key)
			--right;
		swap(a[right],a[left]);
	}
	swap(a[right],key);
	return left;
}
//前后指针法 适用于链表
int Partion2(int* a,int left,int right)
{
	int key = a[right];
	int cur = left;
	int prev = cur-1;
	while(cur < right)
	{
//		if(a[cur] <= key && ++prev != cur)
//			swap(a[cur],a[prev]);
		if(a[cur] <= key)
		{
			++prev;
			if(prev != cur)
				swap(a[cur],a[prev]);
		}
		++cur;
	}
	swap(a[++prev],a[right]);
	return prev;
}

void QuickSort(int *a,int left,int right)
{
	assert(a);

	if(left < right)
	{
		int div = Partion2(a,left,right);
		QuickSort(a,left,div-1);
		QuickSort(a,div+1,right);
	}
}

//小区间优化：由于递归会压栈 为了提高效率 减少递归次数 当数组接近有序 用插入排序
void QuickSortOP(int *a,int left,int right)
{
	assert(a);
	if(right - left < 13)
	{
		InsertSort(a+left,right-left+1);
	}
	else
	{
		int div = Partion2(a,left,right);
		QuickSortOP(a,left,div-1);
		QuickSortOP(a,div+1,right);
	}
}
//非递归
#include<stack>
void QuickSortNonR(int* a,int left,int right)
{
	stack<int> s;
	s.push(right);
	s.push(left);
	int begin;
	int end;
	int div;
	while(!s.empty())
	{
		begin = s.top();
		s.pop();
		end = s.top();
		s.pop();
		div = Partion(a,begin,end);
		//注意压栈先后顺序right在栈底，left在栈顶	
		if(begin < div-1)
		{
			s.push(div-1);
			s.push(begin);
		}
		if(div+1 < end)
		{
			s.push(end);
			s.push(div+1);
		}
	}
}
void Test4()
{
	int a[] = {5,2,7,1,3,0,4,9,0,6};
//	QuickSortNonR(a,0,sizeof(a)/sizeof(a[0])-1);
	QuickSortOP(a,0,sizeof(a)/sizeof(a[0])-1);
//	QuickSort(a,0,sizeof(a)/sizeof(a[0])-1);
	Print(a,sizeof(a)/sizeof(a[0]));
}

void _MergeSort(int* a,int* tmp,int left,int right)
{
	if(left >= right)
		return;
	
	int mid = left + ((right-left)>>1);

	_MergeSort(a,tmp,left,mid);
	_MergeSort(a,tmp,mid+1,right);

	//Mergr(a,tmp,left,mid,right)
	
	int begin1 = left;
	int end1 = mid;
	int begin2 = mid+1;
	int end2 = right;
	int index = begin1;

	while(begin1 <= end1 && begin2 <= end2)
	{
		if(a[begin1] < a[begin2])
			tmp[index++] = a[begin1++];
		else
			tmp[index++] = a[begin2++];
	}

	while(begin1 <= end1)
		tmp[index++] = a[begin1++];
	while(begin2 <= end2)
		tmp[index++] = a[begin2++];

	while(left <= right)
	{
		a[left] = tmp[left];
		left++;
	}
}
void MergeSort(int* a,size_t n)
{
	assert(a);

	int* tmp = new int[n];
	_MergeSort(a,tmp,0,n-1);
	delete []tmp;
}

void Test7()
{
	int a[] = {5,2,7,1,3,8,4,9,0,6};
	MergeSort(a,sizeof(a)/sizeof(a[0]));
	Print(a,sizeof(a)/sizeof(a[0]));
}

void BubSort(int* a,size_t n)
{
	assert(a);
	for(int i = 0; i<n-1;++i)
		for(int j = 0; j<n-i-1; ++j)
			if(a[j] > a[j+1])
				swap(a[j],a[j+1]);
//	for(int i = 1; i<n; ++i)
//		for(int j = 0; j < n-i; ++j)
//			if(a[j] > a[j+1])
//				swap(a[j],a[j+1]);
}

void BubSortOP(int* a,size_t n)
{
	assert(a);

	int flag = 0;
	for(int i = 1; i<n; ++i)
	{
		for(int j = 0; j<n-i; ++j)
			if(a[j] > a[j+1])
			{
				swap(a[j],a[j+1]);
				flag = 1;
			}
		if(flag == 0)
			break;	
	}

	
}

void Test6()
{
	int a[] = {5,2,7,1,3,8,4,9,0,6};
	BubSortOP(a,sizeof(a)/sizeof(a[0]));
	Print(a,sizeof(a)/sizeof(a[0]));
}

int GetMidDigist(int* a,size_t n)
{
	int base = 1;
	int max = 10;
	for(int i = 0; i<n; ++i)
	{
		if(a[i] > max)
		{
			++base;
			max*= 10;
		}
	}
	return base;
}

void LSDSort(int* a,size_t n)
{
	assert(a);
	
	int midDigist = GetMidDigist(a,n);
	int* bucket = new int[n];
	int count[10] = {0};
	int start[10] = {0};
	int numbit = 1;
	int digit = 1;
	while(numbit  <= midDigist)
	{
		for(int i = 0; i<n; ++i)
		{
			int num = (a[i]/digit) % 10;
			count[num]++;
		}
		start[0] = 0;
		for(int i = 1; i<n; ++i)
		{
			start[i] = start[i-1] + count[i-1];
		}
		for(int i = 0; i<n; ++i)
		{
			int num = (a[i]/digit) % 10;
			bucket[start[num]++] = a[i];
		}
		memcpy(a,bucket,sizeof(int)*n);
		digit *= 10;
		++numbit;
	}
}
void Test8()
{
	int a[] = {5,2,7,1,3,8,4,9,0,6};
	LSDSort(a,sizeof(a)/sizeof(a[0]));
	Print(a,sizeof(a)/sizeof(a[0]));
}

void CountSort(int *a, size_t size)
{
	assert(a);
	int max = a[0];
	int min = a[0];
	for (int i = 0; i < size; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
		else if (a[i] < min)
		{
			min = a[i];
		}
	}
	int len = max - min + 1;
	int *countArr = new int[len];
	memset(countArr, 0, sizeof(int)*len);
	for (int i = 0; i < size; i++)
	{
		countArr[a[i] - min]++;
	}
	int tmp = 0;
	for (int i = 0; i < len; i++)
	{
		while (countArr[i]--)
		{
			a[tmp++] = i + min;
		}
	}
}
void Test9()
{
	int a[] = {5,2,7,1,3,8,4,9,0,6};
	CountSort(a,sizeof(a)/sizeof(a[0]));
	Print(a,sizeof(a)/sizeof(a[0]));
}

