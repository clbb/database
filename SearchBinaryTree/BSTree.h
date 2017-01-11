#pragma once
#include<iostream>
using namespace std;

template <class K>
struct BSTreeNode
{
	K _key;
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right; 
	BSTreeNode(const K& key)
		:_key(key)
		,_left(NULL)
		,_right(NULL)
	{}
};


template <class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	BSTree()
		:_root(NULL)
	{}
	~BSTree()
	{}
	bool Insert(const K& key)
	{
		if(_root == NULL)	
		{
			_root = new Node(key);
			return true;
		}
		Node *cur = _root;
		Node* parent = NULL;
		while(cur)
		{
			if(cur->_key > key)
			{
				parent = cur; 
				cur = cur->_left;
				if(cur == NULL)
				{
					cur = new Node(key);
					parent->_left = cur;
					return true;
				}
				
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
				if(cur == NULL)
				{
					cur = new Node(key);
					parent->_right = cur;
					return true;
				}
			}
			else
			{
				break;
			}
		}
		return false;
	}
	bool remove(const K& key)
	{
		if(_root == NULL)
			exit(1);

		Node* cur = _root;
		Node* parent = NULL;
		Node* del = cur;
		while(cur)
		{
			if(key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(key > cur->_key)
			{
 				parent = cur;
				cur = cur->_right;
			}
			else//rm this node
			{
			//	if() //one son
				if(cur->_left && cur->_right) //two son
				{	
	 			  	Node* subLeaft = cur->_right;
					parent = subLeaft;
					while(subLeaft->_left ||  subLeaft->_right)
					{
	 			 		while(subLeaft->_left)
							subLeaft = subLeaft->_left;
						while(subLeaft->_right)
 							subLeaft = subLeaft->_right;
					}
					while(parent->_left != subLeaft &&  parent->_right != subLeaft)
					{
	 			  		while(parent->_left)
							parent = parent->_left;
						while(parent->_right)
 							parent = parent->_right;
					}
					cur->_key = subLeaft->_key;
					if(parent->_left == subLeaft)
						parent->_left = NULL;
					else
						parent->_right = NULL;
 					del = subLeaft; 
					
				}
				else//one son or no son
				{
	 			 	if(cur->_left == NULL)
					{
						parent->_right = cur->_right;
					}
					else if(cur->_right == NULL)
					{
						parent->_left = cur->_left;
 				 	}
						
				}
				delete del;
				del = NULL;
 				return true;
			}
		}
		return false;
	}
	bool remove_(const K& key)
	{
		Node* cur = Find(key);
		Node* parent = NULL;
		
		//has two son
		if(cur->_right && cur->_left)
		{
			Node* subLeaft = cur->_right;
			while(subLeaft->_left ||  subLeaft->_right)
			{
	 			while(subLeaft->_left)
					subLeaft = subLeaft->_left;
				while(subLeaft->_right)
					subLeaft = subLeaft->_right;
			}
			cur->_key = subLeaft->_key;

			//tmp is a leafNode
			delete subLeaft;
			return true;
		}
		else	//has one son or not has son
		{	
			Node* tmp = cur;
			if(cur->_left == NULL)
				cur=cur->_right;
			else if(cur->_right == NULL)
				cur=cur->_left;

			delete tmp;
			tmp = NULL;
			return true;
		}
		return false;
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while(cur)
		{
			if(cur->_key > key)
				cur = cur->_left;
			else if(cur->_key < key)
				cur = cur->_right;
			else
				return cur;
		}
		cout<<"no find"<<endl;
		exit(1);
	}

	void Inorder()
	{
		_Inorder(_root);
		cout<<endl;
	} 


	void print()
	{
		print(_root,hight(_root));
		cout<<endl<<endl;
	}

	
protected:
	int hight(Node* root)
	{
		if(root == NULL)
			return 0;
		return hight(root->_left) > hight(root->_right) ?
				 hight(root->_left) +1 : hight(root->_right)+1;
	}

	void print(Node* root,int level)
	{
		int i;
		if(NULL == root)
			return ;
		print(root->_right,level+1);
		for(i=0;i<level;++i)
			cout<<"    ";
		cout<<root->_key<<endl;
		print(root->_left,level+1);
	}
	void _Inorder(Node* root)
	{
		if(root == NULL)
			return;
		_Inorder(root->_left);
		cout<<root->_key<<" ";
		_Inorder(root->_right);
	}
private:
	Node* _root;
};

void Test1()
{
	BSTree<int> b;
	b.Insert(5);
	b.Insert(3);
	b.Insert(7);
	b.Insert(4);
	b.Insert(1);
	b.Insert(0);
	b.Insert(2);
	b.Insert(6);
	b.Insert(10);
	b.Insert(11);
	b.Insert(8);

	b.print();
	b.remove(7);
//	b.remove_(7);
	b.print();
}


void testNode()
{

	typedef BSTreeNode<int> Node;
	Node* p = new Node(4);
	free(p);
	p=NULL;
	cout<<p->_key<<endl;
}
