#pragma once
#include<stack>
#include<iostream>
#include<assert.h>
#include<queue>
using namespace std;

template <class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree(T* a,size_t size,const T& invalid )//先序
	{
		int index = 0;
		_root = _Create(a,invalid,size,index);
	}
	
	BinaryTree(BinaryTree<T>& t);
	BinaryTree<T>& operator=(BinaryTree<T>& t);
	//~BinaryTree();

	size_t Size()
	{
		return _Size(_root);
	}
	size_t Depth()
	{
		return _Depth(_root);
	}
	size_t GetleaftSize()
	{
		return _GetleaftSize(_root);
	}
//	size_t GetKlevelSize(size_t K)
//	{
//		return _GetKlevelSize(_root,K);
//	}
	size_t GetKlevelSize(size_t K)
	{
		assert(K>0);
		int count = 0;
		int level = 1;
		return _GetKlevelSize(_root,count,K,level);
		
	}
	
	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void LevelOrder()
	{
		_LevelOrder(_root);
		cout<<endl;
	}

	
	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}
public:
	void PrevOrderNonR()
	{
		_PrevOrderNonR(_root);
		cout<<endl;
	}
	void InorderNonR()
	{
		_InorderNonR(_root);
		cout<<endl;
	}
	void PostOrderNonR()
	{
		_PostOrderNonR(_root);
		cout<<endl;
	}
	Node* Find(const T& x)
	{
		return _Find(_root,x);
	}
protected:
	void _PostOrderNonR(Node* root)
	{
		stack<Node*> s;
		Node* cur = root;
		Node* prev = NULL;
		while(!s.empty() || cur)
		{
			while(cur)
			{
			//遇到树根压入栈中 
				s.push(cur); 
				cur = cur->_left;
			}
			//从栈中取出一个节点 表示这个节点的根
			//该节点的左子树已经访问过
			//取出栈顶元素 判断是否为已经访问过的根 不是 打印 是的话转化为子问题
			//用子问题的方式去访问右子树
			Node* top = s.top();
			if(top->_right == prev || top->_right == NULL)//这里的top不可能为NULL
			{
				cout<<top->_data<<" ";
				prev = top;
				s.pop();
			}
			else
			//子问题（循环＋栈）
				cur = top->_right;
		}
		
	}
	void _InorderNonR(Node*root)
	{
		stack<Node*> s;
		Node* cur = root;
		while(!s.empty() || cur)
		{
			while(cur)
			{
			//遇到树根直接访问 并压入栈中 
				s.push(cur);
				cur = cur->_left;
			}
			//从栈中取出一个节点 表示这个节点的根
			//该节点的左子树已经访问过
			//访问该节点
			//用子问题的方式去访问右子树
			Node* top = s.top();
			cout<<top->_data<<" ";
			s.pop();

			//子问题（循环＋栈）
			cur = top->_right;
		}
		
	}
	void _PrevOrderNonR(Node* root)
	{
		stack<Node*> s;
		Node* cur = root;
		while(!s.empty() || cur)
		{
			while(cur)
			{
			//前序遍历 遇到树根直接访问 并压入栈中 
				cout<<cur->_data<<" ";
				s.push(cur);
				cur = cur->_left;
			}
			//从栈中取出一个节点 表示这个节点的根
			//该节点和左子树已经访问过
			//用子问题的方式去访问右子树
			Node* top = s.top();
			s.pop();

			//子问题（循环＋栈）
			cur = top->_right;
		}
	}
protected:
	//size_t _GetKlevelSize(Node* root,size_t K,size_t count)
	//{
	//	if(root == NULL)
	//		return 0;
	//	
	//	if(root->_left)
	//}
//	size_t _GetleaftSize(Node* root,size_t count,int K,size_t level)
//	{
//		assert(K>0);
//		if()
//	}
	Node* _Find(Node* root,const T& x)
	{
		if(root == NULL)
			return NULL;
		if(root->_data == x)
			return root;
		Node* ret = _Find(root->_left,x);
		if(ret == NULL)
			ret = _Find(root->_right,x);

		return ret;
	}
	size_t _GetKlevelSize(Node* root,int& count,const size_t K,int level)
	{
		if(root == NULL)
			return 0;
		if(level == K)
			count++;

		_GetKlevelSize(root->_left,count,K,level+1);
		_GetKlevelSize(root->_right,count,K,level+1);
		return count;
	}

//	size_t _GetKlevelSize(Node* root,size_t K)
//	{
//		assert(K > 0);
//		if(root == NULL)
//			return 0;
//		if(K == 1)
//			return 1;
//		return _GetKlevelSize(root->_left,K-1)+_GetKlevelSize(root->_right,K-1);
//	}

	size_t _Size(Node* root)
	{
		if(root == NULL)
			return 0;
		return _Size(root->_left)+_Size(root->_right)+1;
	}
	size_t _Depth(Node* root)
	{
		if(root == NULL)
			return 0;
		int leftDepth = _Depth(root->_left);
		int rightDepth = _Depth(root->_right);	
		return leftDepth > rightDepth ? leftDepth+1 : rightDepth+1; 
	}
	void _LevelOrder(Node* root)
	{
		queue<Node*> q;
		if(root == NULL)
			return;
		q.push(root);
		while(!q.empty())
		{
			Node* del = q.front();
			cout<<del->_data<<" ";  
			q.pop();

			if(del->_left != NULL)
				q.push(del->_left);
			if(del->_right != NULL)
				q.push(del->_right);
		}
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}
	void _PostOrder(Node* root)
	{
		if(root == NULL)
			return;
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}
	void _PrevOrder(Node* root)
	{
		if(root == NULL)
			return;
		cout<<root->_data<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	Node* _Create(T* a,const T& invalid,size_t size,int& index)
	{
		assert(a);
		Node* root = NULL;
		if((index < size)&& (a[index] != invalid))
		{
			root = new Node(a[index]);//
			root->_left = _Create(a,invalid,size,++index);
			root->_right = _Create(a,invalid,size,++index);
		}
		return root;
			
	}
protected:
	Node* _root;
};

void Test()
{
	int a[] = {1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> t(a,10,'#');
	t.PrevOrder();
	t.PrevOrderNonR();
	t.InOrder();
	t.InorderNonR();
	t.PostOrder();
	t.PostOrderNonR();

	cout<<t.GetKlevelSize(1)<<endl;
	cout<<t.GetKlevelSize(2)<<endl;
	cout<<t.GetKlevelSize(3)<<endl;
	cout<<t.Find(5)->_data<<endl;
//	t.LevelOrder();
//	cout<<t.Size()<<endl;
//	cout<<t.Depth()<<endl;
//	cout<<t.GetKlevelSize(3)<<endl;	
	
}
