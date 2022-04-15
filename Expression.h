#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Expression
{
public:
	static char priorityTable[8][8];			//算符优先级表
public:
	static void format(string& str);			//处理负号
	static bool isOperator(char ch);			//判断是否为运算符+-*/
	static vector<string> 
		resolveExpression(string& str);			//处理表达式，把表达式分解成操作数、运算符、界限符
	static char precede(char op1, char op2);	//判断算符优先级
	static bool isExpression(string& str);		//判断是否为有效表达式
	static bool isFunctor( char ch) ;			//判断是否为算符，算符包括运算符和界限符
	static bool isDelimiter( char ch) ;			//判断是否为界限符()
	static bool isOperand(char op);				//判断是否为操作数
};
