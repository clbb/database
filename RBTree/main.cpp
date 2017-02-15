#include"RBTree.h"
int main()
{
	RBTree<int,int> t1;
	
	int a[] = {5,3,4,1,7,8,2,6,0,9};
	for(int i = 0; i<sizeof(a)/sizeof(a[0]); ++i)
	{
		t1.Insert(a[i],i);
	}

	t1.Inorder();
		
	cout<<t1.Isbalance()<<endl;	
	
	return 0;
}
