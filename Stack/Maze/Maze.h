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
	FILE* fout = fopen("MazeMap.txt","r");
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
bool CheckAccess(int* Maze,size_t N,Pos pos)
{
	
	if((pos._col>0 && pos._col<N)
	&& (pos._row>0 && pos._row<N)
	&& (Maze[pos._row*N+pos._col] == 0))
			return true;
	return false;
}
//上下左右
//回溯法 试探
//走过的路要标记
bool GetMazePath(int* Maze,size_t N,stack<Pos>& path,Pos enter)
{
	assert(Maze);
	Pos cur;
	Pos next;
	path.push(enter);
	
	while(!path.empty())
	{			
		cur = path.top();
		Maze[cur._row*N+cur._col] = 2;
		//找到出口
		if(cur._row == N-1)
			return true;
		//探测上下左右四个方向
		next = cur;
		next._col+=1;//右
		if(CheckAccess(Maze,N,next))
		{
			path.push(next);
			continue;
		}
		next = cur;
		next._row-=1;//上
		if(CheckAccess(Maze,N,next))
		{
			path.push(next);
			continue;
		}
		next = cur;
		next._row+=1;//下
		if(CheckAccess(Maze,N,next))
		{
			path.push(next);
			continue;
		}
		next = cur;
		next._col-=1;//左
		if(CheckAccess(Maze,N,next))
		{
			path.push(next);
			continue;
		}
		//四个方向都不同进行回溯
		path.pop();
	}
	return false;
}
void GetMazePathR(int* Maze,size_t N,stack<Pos>& path,Pos enter)
{
	assert(Maze);
	Pos cur;
	Pos next;
	path.push(enter);
	cur = path.top();
	Maze[cur._row*N+cur._col] = 2;

	if(cur._row == N-1)
	   return;

	next = cur;
	next._col+=1;//上
	if(CheckAccess(Maze,N,next))
	{
		GetMazePathR(Maze,N,path,next);
	}
	next = cur;
	next._row-=1;//上
	if(CheckAccess(Maze,N,next))
	{
		GetMazePathR(Maze,N,path,next);
	}
	next = cur;
	next._row+=1;//上
	if(CheckAccess(Maze,N,next))
	{
		GetMazePathR(Maze,N,path,next);
	}
	next = cur;
	next._col-=1;//上
	if(CheckAccess(Maze,N,next))
	{
		GetMazePathR(Maze,N,path,next);
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
	Pos enter = {2,0};
	GetMaze((int *)Maze,N);
	//cout<<"is find Maze out:"<<GetMazePath((int *)Maze,N,s,enter)<<endl;
	GetMazePath((int *)Maze,N,s,enter);
	cout<<"is find Maze out:"<<!s.empty()<<endl;
	PrintMaze((int *)Maze,N);
}

