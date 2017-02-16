#include"RBTree.h"
#include"SetApply.h"
void TestRB()
{
	RBTree<int,int> t1;
	
	int a[] = {5,3,4,1,7,8,2,6,0,9};
	for(int i = 0; i<sizeof(a)/sizeof(a[0]); ++i)
	{
		t1.Insert(a[i],i);
		cout<<i<<" "<<t1.Isbalance()<<endl;	
	}
	cout<<t1.Isbalance()<<endl;	

	t1.Inorder();
	t1.print();	

}

void Testfruit()
{
	string fruit[] = {"apple","banana","origin","banana","apple_pie","mango","mango","mango"};
	Count1(fruit,10);
}
void Testcount()
{
	string strs[] = {"sort","set","set","hash","sort"};
	Count1(strs,5);
}
int main()
{
	TestRB();
//	TestSet();
//	TestMap();	
	return 0;
}
