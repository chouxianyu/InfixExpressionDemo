# InfixExpressionDemo

用C++实现中缀表达式的计算

# 1 功能简介

- 给定中序表达式，比如a+b*(c-d)-e/f，要求通过二叉树、栈、递归等计算得到该表达式的值。
- 一些具体要求和细节如下：
  - 运算支持加减乘除
  - 能够处理复杂的表达式（负数、小数、括号等）

# 2 代码实现

## 2.1 符号说明

- 运算符Operator：+-*/，分别对应加减乘除
- 界限符Delimiter：（）#，括号即表示计算中优先，#表示表达式结束
- 算符Functor：算符包括运算符和界限符
- 操作数Operand：操作数
- 二元运算式：一个操作数、一个运算符、一个操作数，如3*2

## 2.2 数据结构设**计**

### **2.2.1 Expression**

```C++
// Expression.h
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
```

### **2.2.2 BiTNode**

```C++
// BiTNode.h
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
```

### **2.2.3 BiTree**

```C++
// BiTree.h
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
```

## 2.3 一些细节实现的说明

### 2.3.1 **如何判断表达式是否合法？**

```C++
// Expression.h
static bool isExpression(string& str);		//判断是否为有效表达式
```

- 没有非法情况就是合法，只需要检验用户输入的表达式是否有非法情况即可
- 非法情况如下：

（1）长度为0

（2）首尾不是数字或括号

（3）小数点前后不是数字

（4）运算符后不是数字或左括号

（5）数字后不是运算符或小数点或右括号

（6）括号不匹配

### 2.3.2 如何处理负数

```C++
// Expression.h
static void format(string& str);			//处理负号
```

- 表达式中出现减号，只有两种情况：减法、负数，其中减法不用处理，把负数处理成减法，即0减去一个数
- 负数只有两种情况：表达式第一个数字就是负数、某个括号里第一个数是负数
  - 表达式第一个数字就是负数的情况：在表达式头部插入数字0，比如-1*3+2 ==》0-1*3+2
  - 括号里第一个数是负数的情况：在左括号后插入数字0

### 2.3.3 **如何处理小数？**

读到第一个数字，如果后边是小数点或数字，连接；否则数字结束

### 2.3.4 **如何根据表达式生成二叉树？**

- 将表达式分解成界限符、运算符、操作数

```C++
// Expression.h
static vector<string> resolveExpression(string& str);			//处理表达式，把表达式分解成操作数、运算符、界限符
```

- 运用栈，根据分解后的表达式生成树

```C++
// BiTree.h
BiTree(string expression);	//用字符串构造二叉树
```

# 3 运行结果

## 3.1 "1+(-1+2)*1.3"

```
先序输出
+1*+-0121.3
中序输出
(1+(((0-1)+2)*1.3)
后序输出
101-2+1.3*+
计算结果
2.3
```

## 3.2 "9+0.5\*8.999+(3-4)\*12894.234"

```
先序输出
++9*0.58.999*-3412894.234
中序输出
（（9+（0.5*8.999))+(（3-4)*12894.234))
后序输出
90.58.999*+34-12894.234*+
计算结果
-12880.7
```

## 3.3 "3.1+9.9*10/10"

```
先序输出
+3.1/*9.91010
中序输出
(3.1+((9.9*10)/10))
后序输出
3.19.910*10/+
计算结果
13
```