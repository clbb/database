#pragma once
#include<iostream>
using namespace std;

//线索化二叉树
//特点：将叶子节点的空指针充分利用，_left->前驱 _right—>后继
//1.构建树，递归方式
//2.采用中序方式线索化二叉树，由于中序的特殊性（左中右）
//3.线索化中序也采用递归的方式，只递归一次让他生成一颗特殊的树，以后遍历就不需要递归
//4.遍历二叉树，采用中序线索化后的二叉树进行遍历
//线索化优点：无空间复杂度开销
namespace THREAD
{
	enum PointType
	{
		THREAD,
		LINK
	};
	
	template <class T>
	struct BinaryTreeNode
	{
		T _data;
		BinaryTreeNode<T>* _left;
		BinaryTreeNode<T>* _right;
	
		PointType _leftTag;
		PointType _rightTag;
		BinaryTreeNode(const T& x)
			:_data(x)
			,_left(NULL)
			,_right(NULL)
			,_leftTag(LINK)
			,_rightTag(LINK)
		{}
	};
	
	template <class T>
	class BinaryTree
	{
		typedef BinaryTreeNode<T> Node;
	public:
	BinaryTree(T* a,size_t size,const T& invalid)
	{
		assert(a);
		int index = 0;
		_root = _Create(a,size,invalid,index);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PrevOrderThreading()
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root,prev);
		if(prev->_right == NULL)
			prev->_rightTag = THREAD;
	}
	
	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root,prev);
		if(prev->_right == NULL)
			prev->_rightTag = THREAD;
	}
	void PrevOrderThd()
	{
		Node* cur = _root;
		while(cur)
		{
			while(cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			if(cur)
				cout<<cur->_data<<" ";
			while(cur && cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				if(cur)
					cout<<cur->_data<<" ";
			}
			if(cur)
				cur = cur->_right;
		}
		cout<<endl;
	}
	void InOrderThd()
	{
		Node* cur = _root;
		while(cur)
		{	
			//找最左节点
			while(cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			cout<<cur->_data<<" ";
			//后继则直接访问
			while(cur && cur->_rightTag == THREAD)
			{
				cur = cur->_right; 
				cout<<cur->_data<<" ";
			}
			cur = cur->_right;
			//子问题 右树是子数，子问题处理
		}
			cout<<endl;
	}
	protected:
	//前序线索化和前序也很像
	void _PrevOrderThreading(Node* cur,Node*& prev)
	{
		if(cur == NULL || cur->_leftTag == THREAD)
			return;
		
		if(cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}
		if(prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}
		prev = cur;
		if(cur->_leftTag == LINK)
			_PrevOrderThreading(cur->_left,prev);
		if(cur->_rightTag == LINK)
			_PrevOrderThreading(cur->_left,prev);
		
	}
	//中序线索化和中序遍历很像
	void _InOrderThreading(Node* cur,Node*& prev)
	{
		if(cur == NULL)
			return;

		_InOrderThreading(cur->_left,prev);

		if(cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}
		if(prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}
		prev = cur;

		_InOrderThreading(cur->_right,prev);
		
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);

	}
	Node* _Create(T* a,size_t size,const T& invalid,T& index)
	{
		Node* root = NULL;
		if(index < size && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _Create(a,size,invalid,++index);
			root->_right= _Create(a,size,invalid,++index);
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
	//	t.InOrder();
	//	t.InOrderThreading();
	//	t.InOrderThd();
	//	所有树只能被线索化一次
		
		t.PrevOrderThreading();
		t.PrevOrderThd();
	}	
	
}
