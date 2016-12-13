#pragma once
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
	size_t GetKlevelSize(size_t K)
	{
		return _GetKlevelSize(_root,K);
	}
	//size_t GetKlevelSize(size_t K)
	//{
	//	int count = 0;
	//	return _GetKlevelSize(_root,K,count);
	//}
	
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
protected:
	//size_t _GetKlevelSize(Node* root,size_t K,size_t count)
	//{
	//	if(root == NULL)
	//		return 0;
	//	
	//	if(root->_left)
	//}
//	size_t _GetleaftSize(Node* root)
//	{
		
//	}
	size_t _GetKlevelSize(Node* root,size_t K)
	{
		assert(K > 0);
		if(root == NULL)
			return 0;
		if(K == 1)
			return 1;
		return _GetKlevelSize(root->_left,K-1)+_GetKlevelSize(root->_right,K-1);
	}
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
	t.InOrder();
	t.PostOrder();
	t.LevelOrder();
	cout<<t.Size()<<endl;
	cout<<t.Depth()<<endl;
	cout<<t.GetKlevelSize(3)<<endl;	
	
}
