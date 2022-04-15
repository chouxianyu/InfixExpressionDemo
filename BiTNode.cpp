#include "BiTNode.h"
#include "Expression.h"
#include <iostream>
using namespace std;

BiTNode::BiTNode()
{
	data = "";
	left = nullptr;
	right = nullptr;
}

void BiTNode::print()
{
	cout << data;
}

double BiTNode::calculate()
{
	//是操作数
	if (Expression::isOperand(data[0]) && left == nullptr&&right == nullptr)
		return atof(data.c_str());

	else if (Expression::isOperator(data[0]) && left != nullptr&&right != nullptr)
	{
		switch (data[0])
		{
		case '+':
			return left->calculate() + right->calculate();
		case '-':
			return left->calculate() - right->calculate();
		case '*':
			return left->calculate() * right->calculate();
		case '/':
			double rightResult = right->calculate();
			if (rightResult == 0.0)
			{
				cout << "除数为0！！！" << endl;
				cout << "程序已退出！" << endl;
				exit(-1);
			}
			return left->calculate() / right->calculate();
		}
	}
	else
	{
		cout << "结点存储字符非法！" << endl;
		cout << "程序已退出！" << endl;
		exit(-1);
	}
}
