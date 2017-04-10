#include"SQTest.h"
void TestQ()
{
	queue<int> a;
	a.push(1);	
	a.push(2);	
	a.push(3);	
	a.push(4);
	
	cout<<a.back()<<endl;
	a.pop();
	cout<<a.back()<<endl;
	a.pop();
	cout<<a.back()<<endl;
	a.pop();
	cout<<a.back()<<endl;
	a.pop();
	cout<<a.back()<<endl;

}
int main()
{

//	TestMin();	
//	TestMin2();
//	TestQ();
//	TestDS();	
//	TestQS();
	TestJuge();
//	TestTwoSQ();
	return 0;
}
