#include"BinaryTree.h"
#include"ThreadBinaryTree.h"
//方法1:
using namespace BINTREE;
using namespace THREAD;//这句可不要
int main()
{
//使用命名空间方法有两种：1预编译(好处：不必在程序中显示的调用命名空间限定符来访问变量) 2在程序中调用的方式
/*
	using namespace BINTREE;
		Test();
  //整个工程里这个TEST已经可见，如果在下面不加限制，编译器会无法识别是那个命名控件中的变量，即使同样声明里命名空间，还是分不清
	using namespace THREAD;//这句可不要
		THREAD::Test();
*/
//方法2
//	BINTREE::Test();
	THREAD::Test();
	return 0;
}
