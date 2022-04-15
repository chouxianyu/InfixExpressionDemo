#include "Expression.h"
#include <iostream>
using namespace std;

char Expression::priorityTable[8][8]=
{
	{' ','+','-','*','/','(',')','#'},
	{'+','>','>','<','<','<','>','>'},
 	{'-','>','>','<','<','<','>','>'},
	{'*','>','>','>','>','<','>','>'},
	{'/','>','>','>','>','<','>','>'},
	{'(','<','<','<','<','<','=',' '},
	{')','>','>','>','>',' ','>','>'},
	{'#','<','<','<','<','<',' ','='}
};

void Expression::format(string& str)
{
	//处理负数
	for (int i = 0; i < str.length(); i++) {
		//出现减号，只有两种情况：减法或者负数
		//减法不用处理，把负数处理成减法，即0减去一个数
		if (str[i] == '-') {	//发现负号:负数或减法
			//负数只有两种情况
			if (i == 0) {	//第一个数就是负数
				str.insert(0, 1, '0');
			}
			else if (str[i - 1] == '(') {	//括号里第一个数是负数
				str.insert(i, 1, '0');
			}
			//其余的是减法，不用处理
		}
	}
}

bool Expression::isOperator(char ch)
{
	string operators = "+-*/";
	if (operators.find(ch)!=operators.npos)	//找到，说明是运算符
	{
		return true;
	}
	return false;
}

vector<string> Expression::resolveExpression(string& str)
{
	if (isExpression(str) == false)	//判断字符串是否合法
	{
		cout << "表达式不合法！！" << endl;
		cout << "程序已退出！！" << endl;
		exit(-1);
	}

	vector<string> list;
	string temp = "";
	for (int i = 0; i < str.length(); i++) {
		const char ch = str[i];

		if (isdigit(ch) || ch == '.')			//数字或小数点
		{	
			temp += ch;	//连接每位数字
		}
		else if (isOperator(ch) || ch == ')')	//运算符或右括号
		{	
			if (temp!="") {	//遇到运算符，temp非空，则temp是操作数，要存起来
				list.push_back(temp);
			}
			temp = "";	//temp中的操作数已存入，置空，下次使用
			list.push_back(string(1, ch));	//把运算符或右括号存起来
		}
		else if (ch == '(')						//左括号
		{	
			list.push_back(string(1,ch));	
		}
		else	//非法字符,因为程序直接退出，当前的str也就不用存储了
		{
			cout << "表达式中含非法字符！！" << endl;
			cout << "程序已退出！！" << endl;
			exit(-1);
		}
		if (i == str.length() - 1&&temp!="") {
			list.push_back(temp);
		}
	}
	return list;
}

char Expression::precede(char op1, char op2)
{
		int i, j;
		for (i = 0; i < 8; i++)	//寻找运算符op1
			if (priorityTable[i][0] == op1)  
				break;
		for (j = 0; j < 8; j++) //寻找运算符op2
			if (priorityTable[0][j] == op2)
			    break;
		return priorityTable[i][j];
		cout << "优先级比较字符非法！！" << endl;
		cout << "程序已退出！！" << endl;
		exit(-1);
}

bool Expression::isExpression(string& str)
{
	if (str.length() == 0)	//空表达式
	{
		cout << "空表达式！！" << endl;
		return false;
	}
	format(str);	//处理负号，要先处理负数 比如 -2应是合法表达式 
	int flag = 0;
	for (int i = 0; i < str.length() - 1; i++)
	{
		const char ch = str[i];
		const char chb = str[i + 1];
		if ((!isdigit(ch) && i == 0) && ch != '(' ||	//首
			!isdigit(chb) && (i == str.length() - 2) && chb != ')')	//尾
		{
			cout << "首尾不是数字或括号---->" << ch << chb << endl;
			return false;
		}
		if ((ch == '.' && !isdigit(chb)) || (!isdigit(ch) && chb == '.'))	//.连接非数字 或 非数字连接.
		{
			cout << "小数点前或后不是数字--->" << ch << chb << endl;
			return false;
		}
		if (isOperator(ch) && !isdigit(chb) && chb != '(')	//运算符连接非数字左括号
		{
			cout << "运算符后不是数字或左括号--->" << ch << chb << endl;
			return false;
		}
		if (isdigit(ch) && !isOperator(chb) && chb != '.' && chb != ')'	//数字连接非运算符非小数点非右括号
			&& !isdigit(chb))
		{
			cout << "数字后不是运算符或小数点或右括号--->" << ch << chb << endl;
			return false;
		}
		if (ch == '(')
		{
			flag++;
		}
		if (chb == ')')
		{
			flag--;
		}
	}
	if (flag != 0)
	{
		cout << "括号不匹配--->" << endl;
		return false;
	}
	return true;
}

bool Expression::isFunctor(char ch)
{
	if (isOperator(ch) || isDelimiter(ch))
		return true;
	return false;
}

bool Expression::isDelimiter(char ch)
{
	if (ch == '(' || ch == ')'|| ch == '#')
		return true;
	return false;
}

bool Expression::isOperand(char ch)
{
	if (!isOperator(ch) && !isDelimiter(ch))
	{
		//不是运算符也不是括号
		return true;
	}
	return false;
}
