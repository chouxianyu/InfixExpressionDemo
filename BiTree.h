#pragma once
class BiTNode;
#include <string>
using std::string;

class BiTree
{
public:
	BiTNode* root;				//根节点

public:
	BiTree();					//建空树
	BiTree(string expression);	//用字符串构造二叉树
	void preOrderPrint(BiTNode* rootTemp);	//先序输出二叉树
	void inOrderPrint(BiTNode* rootTemp);	//中序输出二叉树
	void postOrderPrint(BiTNode* rootTemp);	//后序输出二叉树
	double calculate();						//计算表达式的结果
	void preOrderDestruct(BiTNode* rootTemp);	//先序析构，也可以写中、后序析构，本质上无差别
	void setExpression(string expression);
	~BiTree();					//析构函数，调用preOrderDestruct
};
