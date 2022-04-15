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

![img](https://neg5bl8b86.feishu.cn/space/api/box/stream/download/asynccode/?code=MzI0YWZjY2M1MGNmM2Y0MGI2ZDIwNTdlZjlmMmMyM2RfdW5CSTJuTHRBaGphM2xxdXFiSTlpNWRTOVdpUHM2bnBfVG9rZW46Ym94Y250UXhVTmpmZWVVcWRvalQ5SmFJOFFnXzE2NTAwMzYyNzI6MTY1MDAzOTg3Ml9WNA)

### **2.2.2 BiTNode**

![img](https://neg5bl8b86.feishu.cn/space/api/box/stream/download/asynccode/?code=MDQ2MTEzZjIxZDU5ZTdjNjRjMjQ2ZmE3OWRlZjYxZTZfS01MandIa0hTVnVtUzA4U2MwTjA5OGhCdVpudVhBVkxfVG9rZW46Ym94Y24xN0ZVam5yWnZQYW03YUlKaGkza2xmXzE2NTAwMzYyNzI6MTY1MDAzOTg3Ml9WNA)

### **2.2.3 BiTree**

![img](https://neg5bl8b86.feishu.cn/space/api/box/stream/download/asynccode/?code=NmE0MDU2YmE3NTg4NzRiNWQyMTgxZWZlMjc5YWZlMjVfVTBWNGVPTkRoeFBCS1BnQzdGcFVGa3JDVGp0aDN3WUZfVG9rZW46Ym94Y25hMUcyMEc2N2s0N2FJYnQ1eGN3dnVBXzE2NTAwMzYyNzI6MTY1MDAzOTg3Ml9WNA)

## 2.3 一些细节实现的说明

### 2.3.1 **如何判断表达式是否合法？**

![img](https://neg5bl8b86.feishu.cn/space/api/box/stream/download/asynccode/?code=ZmRiOTYwZmNkNjViMmJmNzYyMTViYjAxMzkwMzU3OWNfVXZKU2swOFlSdDBvWEpESHZzcHlTTEpoRWRVdEdXSFlfVG9rZW46Ym94Y25HMHFsUXRMajFuRzZ1MWZXUkhrS0FuXzE2NTAwMzYyNzI6MTY1MDAzOTg3Ml9WNA)

- 没有非法情况就是合法，只需要检验用户输入的表达式是否有非法情况即可
- 非法情况如下：

（1）长度为0

（2）首尾不是数字或括号

（3）小数点前后不是数字

（4）运算符后不是数字或左括号

（5）数字后不是运算符或小数点或右括号

（6）括号不匹配

### 2.3.2 如何处理负数

![img](https://neg5bl8b86.feishu.cn/space/api/box/stream/download/asynccode/?code=NWZhMDE0YTkyYzU2MTM5YWIzNzg4YzJmMWM4ODU3YjFfek1nalQ3WG9HOVRLWDdXUE04NnlZcG9XdGoxdHRjMVdfVG9rZW46Ym94Y242azlpZmdvdVc2UTBiazdua1haN01jXzE2NTAwMzYyNzI6MTY1MDAzOTg3Ml9WNA)

- 表达式中出现减号，只有两种情况：减法、负数，其中减法不用处理，把负数处理成减法，即0减去一个数
- 负数只有两种情况：表达式第一个数字就是负数、某个括号里第一个数是负数
  - 表达式第一个数字就是负数的情况：在表达式头部插入数字0，比如-1*3+2 ==》0-1*3+2
  - 括号里第一个数是负数的情况：在左括号后插入数字0

### 2.3.3 **如何处理小数？**

读到第一个数字，如果后边是小数点或数字，连接；否则数字结束

### 2.3.4 **如何根据表达式生成二叉树？**

- 将表达式分解成界限符、运算符、操作数

![img](https://neg5bl8b86.feishu.cn/space/api/box/stream/download/asynccode/?code=ZmJlZjAxOTY1NDBmMGU3NDQ3Nzg3ZmY2NDFlY2M5MjRfZ0U4ZVNHSlg4ZHFxSFZRSWV4SFc2Q0F6azl3ckE1aVNfVG9rZW46Ym94Y24wYnNYNE5QdlViazRIMnN5Q0RYRXJoXzE2NTAwMzYyNzI6MTY1MDAzOTg3Ml9WNA)

- 运用栈，根据分解后的表达式生成树

![img](https://neg5bl8b86.feishu.cn/space/api/box/stream/download/asynccode/?code=ODVkODQ0MzAyZDdkNzk5NzA1ZTQxNTgwNzUwZTVmZmZfZTZENndPMURoS0Z2Y004cjhaMlhiZVM0c0Y4TkFNTkFfVG9rZW46Ym94Y25CdEFkeUV2ZWJrZ3NEd25VSEhMNlRkXzE2NTAwMzYyNzI6MTY1MDAzOTg3Ml9WNA)

# 3 运行结果

## 3.1 "1+(-1+2)*1.3"

![img](https://neg5bl8b86.feishu.cn/space/api/box/stream/download/asynccode/?code=M2M0ZGVmNDdjNmQwMGNmMjAyYTQ3MjllZTFiMGE3ZDRfbFA3a20zaXV6andYYlhOMWhEVzI2ZElQN2VMWHhkM3pfVG9rZW46Ym94Y254TUY0Mmp2RnhrZks0MFFXRE80czNmXzE2NTAwMzYyNzI6MTY1MDAzOTg3Ml9WNA)

## 3.2 "9+0.5*8.999+(3-4)*12894.234"

![img](https://neg5bl8b86.feishu.cn/space/api/box/stream/download/asynccode/?code=Y2VkOTZlMDE2MTY3NTIzM2YxZGY0YzIyZTA2NmQ1ODVfbTNWd3k0enBUNEV5bmhvZmtGWlVKRksyQjFnVEtJSlpfVG9rZW46Ym94Y25SN0Ixb3NtMGxHS0I2a0pRTzNUWGdmXzE2NTAwMzYyNzI6MTY1MDAzOTg3Ml9WNA)

## 3.3 "3.1+9.9*10/10"

![img](https://neg5bl8b86.feishu.cn/space/api/box/stream/download/asynccode/?code=ZjZlNGI4MDVmMjg4MDA1ZTZmNzE2NWQzNzc1NmFiNTBfTkFqbWJEV3FYY1UzeFZQRVVqSVg4UDFwVExhQ3R2bmlfVG9rZW46Ym94Y25jdUt1c0FLVHo2M25Pak9XZ3RQMWhnXzE2NTAwMzYyNzI6MTY1MDAzOTg3Ml9WNA)
