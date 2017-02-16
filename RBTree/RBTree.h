#pragma once
#include<iostream>
using namespace std;
enum Color
{
	RED,
	BLANK
};


/*
 *红黑树是平衡树,每个节点上增加一个颜色位来表示节点颜色R／B，通过对任意一条从根到叶子简单路径上的颜色来约束，红黑树保证最长路径不超过最短路径的2倍，因此近似于平衡
红黑性质：
1.每个节点不是红的就是黑的
2.根节点是黑色
3.如果一个节点是红色，则他的两个子节点是黑的（无连续红节点）
4.对每个节点，从该节点到其后所有后代叶子节点的简单路径上，均包含相同数目的黑色节点（每条路径的黑色节点数目均相同）
 * */
template <class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	Color _col;

	RBTreeNode<K,V>* _left;
	RBTreeNode<K,V>* _right;
	RBTreeNode<K,V>* _parent;

	RBTreeNode(const K& key,const V& value,Color col = RED)
		:_key(key)
		,_value(value)
		,_col(col)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};

template <class K, class V>
class RBTree
{
	typedef RBTreeNode<K,V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	bool Insert(const K& key,const V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(key,value,BLANK);
		//	_root->_col = BLANK;
			return true;
		}

		Node* cur = _root;
		Node* parent = NULL;
		while(cur)
		{
			if(key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if(key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key,value,RED);

		//插入
		if(parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		//3种情况
		Node* grandfather = parent->_parent;

		while(parent && parent->_col == RED)
		{
			if(parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//变色
				if(uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLANK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else//旋转
				{
					if(cur ==  parent->_right)
					{
						RotateL(parent);
						swap(parent,cur);
					}
					RotateR( grandfather);
					
					grandfather->_col = RED;
					parent->_col = BLANK;
					break;		

				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				//变色
				if(uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLANK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else//旋转
				{
					if(cur ==  parent->_left)
					{
						RotateR(parent);
						swap(parent,cur);
					}
					RotateL(grandfather);
				
					grandfather->_col = RED;
					parent->_col = BLANK;
					break;	

				}

			}
		}
		_root->_col = BLANK;
		return false;
	}
	bool Isbalance()
	{
		if(_root == NULL)
			return true;
		if(_root && _root->_left == NULL && _root->_right == NULL && _root->_col == BLANK)
			return true;
			
		size_t k = 0;
		size_t num = 0;
		Node* cur = _root;
		while(cur)
		{
			if(cur &&cur->_col == BLANK)
				num++;
			cur = cur->_left;
		}
		return _CheckColor(_root) && _CheckBlankNum(_root,k,num);
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
				 hight(root->_left)+1 : hight(root->_right)+1;
	}

	void print(Node* root,int level)
	{
		int i;
		if(NULL == root)
			return ;
		print(root->_right,level+1);
		for(i=0;i<level;++i)
			cout<<"    ";
		cout<<root->_key<<" "<<root->_col<<endl;
		print(root->_left,level+1);
	}
	
protected:
	//error : 不能调用函数，否则递归时每次都会改变num的标准 导致检查失败
//	size_t IsNum(Node* root)
//	{
//		size_t count = 0;
//		Node* cur = root;
//		while(cur)
//		{
//			cur = cur->_left;
//			if(cur && cur->_col == BLANK)
//				count++;
//		}
//		return count;
//	}
	bool _CheckBlankNum(Node* root,size_t k,const size_t num)
	{
		if(root == NULL)
			return true;
		if(root->_col == BLANK)
			k++;
		if(root->_left == NULL && root->_right == NULL && k != num)
			return false;
		return _CheckBlankNum(root->_left,k,num) && _CheckBlankNum(root->_right,k,num);
	}
	bool _CheckColor(Node* root)
	{
		if(root == NULL)
			return true;
		if(root->_col == RED && root->_parent->_col == RED)
			return false;
		return _CheckColor(root->_left) && _CheckColor(root->_right);
	}
protected:
	void RotateR(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if(subLR)
			subLR->_parent = parent;

		Node* ppNode = parent->_parent;
		subL->_right = parent;
		subL->_parent = ppNode;
		parent->_parent = subL;

		if(subL->_parent == NULL)
			_root = subL;

		else
		{
			if(subL->_key > ppNode->_key)
				ppNode->_right = subL;
			else
				ppNode->_left = subL;
		}
	}

	void RotateL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if(subRL)
			subRL->_parent = parent;

		Node* ppNode = parent->_parent;
		subR->_left = parent;
		subR->_parent = ppNode;
		parent->_parent = subR;

		if(subR->_parent == NULL)
			_root = subR;

		if(subR->_key > ppNode->_key)
			ppNode->_right = subR;
		else
			ppNode->_left = subR;
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
