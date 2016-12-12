#pragma once
#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;
//const size_t N = 10;
//读二维数组 file

struct Pos
{
	int _row;//行
	int _col;//列
};
void GetMaze(int *maze,int N)
{
	FILE* fout = fopen("MazeMapM.txt","r");
	for(int i = 0; i<N; ++i)
	{
		for(int j = 0; j<N;)
		{
			int value = fgetc(fout);
			if(value == '1' || value == '0')
			{
				maze[i*N+j] = value - '0';
				++j;
			}
			else if(value == EOF)//防止没有把迷宫写完整(不满10*10)
			{
				cout<<"Maze Error!"<<endl;
				return;
			}
		}
	}
}
//三个情况 ==1 不合法
//		   ==0 合法
//cur+1 > next return if
bool CheckAccess(int* Maze,size_t N,Pos cur,Pos next)
{
	
	if((cur._col>0 || cur._col<N)
	|| (cur._row>0 || cur._row<N)
	|| (next._col>0 || next._col<N)
	|| (next._row>0 || next._col <N)
	|| (Maze[next._row*N+next._col] == 1))
			return false;

	if(Maze[next._row*N+next._col] == 0)
		return true;
	
	return Maze[cur._row*N+cur._col]+1 > Maze[next._row*N+next._col];
}
/*
 * 以递归的方式探测 tip:递归不走回头路
 * 转换标记方式 以递增的方式标记 确保不走回头路
 * 规则：cur+1 > next 
 * 用两个栈 path:放当前第一次走通的路 Minpath:最短的路
 * 将入口直接标记为2
 */
void GetMazePathR(int* Maze,size_t N,stack<Pos>& path,stack<Pos>& Minpath,Pos enter)
{
	assert(Maze);
	Pos cur;
	Pos next;
	path.push(enter);
	cur = path.top();

	if(!Minpath.empty()|| path.size() < Minpath.size())
	{
		Minpath = path;
		return;
	}	

	next = cur;
	next._col+=1;//上
	if(CheckAccess(Maze,N,cur,next))
	{
		Maze[next._row*N+next._col] = Maze[cur._row*N+cur._col]+1;
		GetMazePathR(Maze,N,path,Minpath,next);
	}
	next = cur;
	next._row-=1;//上
	if(CheckAccess(Maze,N,cur,next))
	{
		Maze[next._row*N+next._col] = Maze[cur._row*N+cur._col]+1;
		GetMazePathR(Maze,N,path,Minpath,next);
	}
	next = cur;
	next._row+=1;//上
	if(CheckAccess(Maze,N,cur,next))
	{
		Maze[next._row*N+next._col] = Maze[cur._row*N+cur._col]+1;
		GetMazePathR(Maze,N,path,Minpath,next);
	}
	next = cur;
	next._col-=1;//上
	if(CheckAccess(Maze,N,cur,next))
	{
		Maze[next._row*N+next._col] = Maze[cur._row*N+cur._col]+1;
		GetMazePathR(Maze,N,path,Minpath,next);
	}
	path.pop();
}
void PrintMaze(int *maze,int N)
{
	for(int i = 0; i<N; ++i)
	{
		for(int j = 0; j<N; ++j)
		{
			cout<<maze[i*N+j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
void TestMaze()
{
	//cin>>N
	const size_t N = 10;
	//?
	int Maze[N][N];
	stack<Pos> s;
	stack<Pos> m;
	Pos enter = {2,0};
	GetMaze((int *)Maze,N);
	//cout<<"is find Maze out:"<<GetMazePath((int *)Maze,N,s,enter)<<endl;
	Maze[enter._row][enter._col] = 2;
	GetMazePathR((int *)Maze,N,s,m,enter);
//	cout<<"is find Maze out:"<<!s.empty()<<endl;
	PrintMaze((int *)Maze,N);
}

