#include "BiTNode.h"
#include "BiTree.h"
#include "Expression.h"
#include <iostream>
using namespace std;

BiTree::BiTree()
{
	root = nullptr;
}

BiTree::BiTree(string expression)
{
	//root置空
	BiTree();

	setExpression(expression);
}

void BiTree::preOrderPrint(BiTNode * rootTemp)
{
	if (rootTemp)
	{
		BiTNode* leftTemp = rootTemp->left;
		BiTNode* rightTemp = rootTemp->right;
		//非叶子节点
		if (leftTemp&&rightTemp)
		{
			//cout << "(";
			//中
			rootTemp->print();
			//左
			if (leftTemp)
				preOrderPrint(leftTemp);
			//右
			if (rightTemp)
				preOrderPrint(rightTemp);
			//cout << ")";
		}
		//叶子结点
		else
		{
			//叶子结点不分中左右...
			rootTemp->print();
		}
	}
}

void BiTree::inOrderPrint(BiTNode* rootTemp)
{
	if (rootTemp)
	{
		BiTNode* leftTemp = rootTemp->left;
		BiTNode* rightTemp = rootTemp->right;
		//非叶子节点
		if (leftTemp && rightTemp)
		{
			cout << "(";
			//左
			if (leftTemp)
				inOrderPrint(leftTemp);
			//中
			rootTemp->print();
			//右
			if (rightTemp)
				inOrderPrint(rightTemp);
			cout << ")";
		}
		//叶子结点
		else
		{
			//叶子结点不分中左右...
			rootTemp->print();
		}
	}
}

void BiTree::postOrderPrint(BiTNode * rootTemp)
{
	if (rootTemp)
	{
		BiTNode* leftTemp = rootTemp->left;
		BiTNode* rightTemp = rootTemp->right;
		//非叶子节点
		if (leftTemp&&rightTemp)
		{
			//cout << "(";
			//左
			if (leftTemp)
				postOrderPrint(leftTemp);
			//右
			if (rightTemp)
				postOrderPrint(rightTemp);
			//中
			rootTemp->print();
			//cout << ")";
		}
		//叶子结点
		else
		{
			//叶子结点不分中左右...
			rootTemp->print();
		}
	}
}

double BiTree::calculate()
{
	if (root)
		return root->calculate();
	else
	{
		cout << "根结点为空，树未建成！" << endl;
		cout << "程序已退出！" << endl;
		exit(-1);
	}
}

void BiTree::preOrderDestruct(BiTNode* rootTemp)
{
	//先序删除结点
	
	if (rootTemp)
	{
		BiTNode* leftTemp = rootTemp->left;
		BiTNode* rightTemp = rootTemp->right;
		
		delete rootTemp;
		if(leftTemp)
			preOrderDestruct(leftTemp);
		if(rightTemp)
			preOrderDestruct(rightTemp);
	}
}

void BiTree::setExpression(string expression)
{
	//先释放原来结点
	preOrderDestruct(root);
	//建树
	//分离表达式的运算符、界限符、操作数
	vector<string> expressions = Expression::resolveExpression(expression);
	//存储结点，可以是运算符、操作数
	vector<BiTNode*> OPND;
	//存储算符：运算符和界限符
	vector<string> OPTR;
	OPTR.push_back("#");
	expressions.push_back("#");
	//遍历表达式，建树
	for (auto iter = expressions.begin(); iter != expressions.end(); iter++)
	{
		//cout << *iter << endl;
		//*iter=="#"并且OPTR.back() == "#" 说明遍历结束，
		if (*iter != "#" || OPTR.back() != "#")
		{
			A:
			char ch = (*iter)[0];
			//是算符
			if (Expression::isFunctor(ch))
			{
				char cc = Expression::precede(OPTR.back()[0], ch);
				//cout << cc << endl;
				switch (cc)
				{
				case '<':	//栈顶元素优先级低
					OPTR.push_back(*iter);
					break;
				case '=':	//脱括号
					OPTR.pop_back();
					break;
				case '>':	//计算，退栈并连接结点，同时存入计算结果
					//运算符
					BiTNode* rootTemp = new BiTNode();
					rootTemp->data = OPTR.back();
					OPTR.pop_back();
					//右操作数
					BiTNode* rightTemp = OPND.back();
					OPND.pop_back();
					//左操作数
					BiTNode* leftTemp = OPND.back();
					OPND.pop_back();
					//连接
					rootTemp->left = leftTemp;
					rootTemp->right = rightTemp;
					OPND.push_back(rootTemp);
					
					//补充部分：存储新来的算符，并判断是否为需要消除界限符
					OPTR.push_back(*iter);
					if (Expression::precede((*(OPTR.end() - 2))[0], (*(OPTR.end() - 1))[0]) == '=')
					{
						OPTR.pop_back();
						OPTR.pop_back();
					}
					else
					{
						OPTR.pop_back();
						goto A;
					}
					break;
					
				}
			}
			//是操作数
			else if (!Expression::isOperator(ch))
			{
				BiTNode* p = new BiTNode();
				p->data = *iter;
				OPND.push_back(p);
			}

		}

	}

	//if (OPND.size() == 1)
	//	cout << "correct!!" << endl;
	root = OPND.back();
}

BiTree::~BiTree()
{
	preOrderDestruct(root);
}
