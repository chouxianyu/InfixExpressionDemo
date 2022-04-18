#include "BiTree.h"
#include <iostream>
using namespace std;

int main()
{
	//第一个树
	BiTree tree1("1+(-1+2)*1.3");

	cout << "先序输出" << endl;
	tree1.preOrderPrint(tree1.root);
	cout << endl;

	cout << "中序输出" << endl;
	tree1.inOrderPrint(tree1.root);
	cout << endl;
	
	cout << "后序输出" << endl;
	tree1.postOrderPrint(tree1.root);
	cout << endl;
	
	cout << "计算结果" << endl;
	cout << tree1.calculate() << endl << endl << endl;

	//第二个树
	BiTree tree2("9+0.5*8.999+(3-4)*12894.234");

	cout << "先序输出" << endl;
	tree2.preOrderPrint(tree2.root);
	cout << endl;

	cout << "中序输出" << endl;
	tree2.inOrderPrint(tree2.root);
	cout << endl;

	cout << "后序输出" << endl;
	tree2.postOrderPrint(tree2.root);
	cout << endl;

	cout << "计算结果" << endl;
	cout << tree2.calculate() << endl << endl << endl;

	//修改第一颗树的表达式
	tree1.setExpression("3.1+9.9*10/10");

	cout << "先序输出" << endl;
	tree1.preOrderPrint(tree1.root);
	cout << endl;

	cout << "中序输出" << endl;
	tree1.inOrderPrint(tree1.root);
	cout << endl;

	cout << "后序输出" << endl;
	tree1.postOrderPrint(tree1.root);
	cout << endl;

	cout << "计算结果" << endl;
	cout << tree1.calculate() << endl << endl << endl;
	
	cin.get();
	return 0;
}
