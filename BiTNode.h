#pragma once
#include <string>
using std::string;

class BiTNode
{
public:
	string data;		//存储的运算符或者是操作数
	BiTNode* left;		//左子树根节点
	BiTNode* right;		//右子树根节点
public:
	BiTNode();
	void print();		//输出结点内容
	double calculate();	//计算结点的结果（即操作数返回自身，运算符递归运算左子树和右子树）
};
