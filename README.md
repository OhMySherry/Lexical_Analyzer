[TOC]

# 词法分析器设计

## 实验环境

- 操作系统：Windows 11

- 编程语言：C++

- 编译器：GCC version 8.1.0

## 实验目的

1. 为初等函数运算语言构造语法分析器。

2. 掌握生成词法分析器的方法，加深对词法分析原理的理解。

3. 掌握设计、编制并调试词法分析程序的思想和方法。

## 实验内容及要求

- 根据下面的要求设计初等函数运算语言的词法模式，并用正则式表达出来

1. 初等函数运算语言的常量为实数类型，其定义方式为实数的最一般书写方式，如：123.321。具体要求：不支持整数部分大于0时首数字为0；不支持小数点后结尾为0；不支持科学记数法；不支持仅为整数时有小数点。

2. 初等函数运算语言的变量采用与C语言的标识符定义一样的方式：首字符为字母或下划线；其他的为字母、数字及下划线的混合串；区分大小写；变量长度不超过32个字符。

3. 初等函数运算语言需要处理的函数仅为下表中所列举的内容。

| 函数类型 |    函数名称     |    参数说明     |
| :------: | :-------------: | :-------------: |
|  sin(x)  |    正弦函数     |        X        |
|  cos(x)  |    余弦函数     |        X        |
|  tg(x)   |    正切函数     |        X        |
|  ctg(x)  |    余切函数     |        X        |
|   x^y    | 幂函数/指数函数 | x: 底数,y: 指数 |
| log(x,y) |      对数       | x: 底数,y: 真数 |
|  lg(x)   | 以10为底的对数  |        X        |
|  ln(x)   |  以e为底的对数  |        X        |
|  log(x)  |  以2为底的对数  |        X        |

4. 初等函数运算语言支持四则运算，其计算的符号与C语言相同，为：+-*/。

5. 初等函数运算语言的合法的分隔符包括：空格、制表符、分行符、圆括号（左、右）、分号。其中空格、制表符、分行符可以出现在任何两个不同的单词中间；圆括号（左、右）用于表达式中，用于改变运算的优先级，以及标识函数的参数；分号用于标识一个语句的结束。

6. 初等函数运算语言支持的常量还包括：PI, E。

## 实验步骤

### 得到正规式

- 常量

![img](https://s2.loli.net/2022/05/17/ksGVN2uWc8iZHl5.png)

- 变量

![img](https://s2.loli.net/2022/05/17/W7TO8R2VjMFgxUB.png)

- 函数名

![img](https://s2.loli.net/2022/05/17/UbLYonh1TpCiQEm.png)

- 运算符

![img](https://s2.loli.net/2022/05/17/a45uxLT7NJtHBdR.png)

- 分隔符

![img](https://s2.loli.net/2022/05/17/HiYuMDr1IzlyJS9.png)

### 从正规式到NFA

- 常量

![img](https://s2.loli.net/2022/05/17/2mZCleiPXY4EQn1.png)

![img](https://s2.loli.net/2022/05/17/thCNzSRqGQLYInx.png)

![img](https://s2.loli.net/2022/05/17/89WisSLtn2UQy7M.jpg)

- 变量

![img](https://s2.loli.net/2022/05/17/nLSPz6osHa9A7Kb.png)

![img](https://s2.loli.net/2022/05/17/djPKZLGiUHcn1u9.jpg)

- 函数名

![img](https://s2.loli.net/2022/05/17/R5F7J1nXvtZbuTO.jpg)

- 运算符

![img](https://s2.loli.net/2022/05/17/mrIA3ki2qceVadj.png)

- 分隔符

![img](https://s2.loli.net/2022/05/17/dSU8kexha6cp72u.png)

### 从NFA到DFA

#### 最小化DFA

- 常量

![img](https://s2.loli.net/2022/05/17/tQzHk648WGpCY3i.jpg)

- 变量

![img](https://s2.loli.net/2022/05/17/JeW8KO7RlTuAvry.jpg)

- 函数名

![img](https://s2.loli.net/2022/05/17/SB9Kjw7tOJdWEnP.jpg)

- 运算符

![img](https://s2.loli.net/2022/05/17/8YVOFQ2gRjX1efz.jpg)

- 分隔符

![img](https://s2.loli.net/2022/05/17/i4OzZaYjTk5yCNt.jpg)

- 合并

![img](https://s2.loli.net/2022/05/17/bSUqv2FfukhYe9w.jpg)

### 由DFA构造词法分析器

|      | -\|+ | *\|/\|^\|= | ;\|(\|)\| ‘space’ |  \   |  P   |  E   |  I   | 0    | No_zero |  .   |  s   |  c   |  t   |  l   |  i   |  o   |  g   |  n   | Char and != P\|E\|s\|c\|t\|l | Char\|Number and != I | Char\|Number != i | Char\|Number != o | Char\|Number !=  t | Char\|Number != g | Char\|Number != n | Char\|Number != s | Char\|Number |
| :--: | :--: | :--------: | :---------------: | :--: | :--: | :--: | :--: | ---- | :-----: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--------------------------: | :-------------------: | :---------------: | :---------------: | :----------------: | :---------------: | :---------------: | :---------------: | :----------: |
|  0   |  1   |     8      |         9         |  18  |  2   |  4   |      | 5    |    6    |      |  10  |  11  |  12  |  13  |      |      |      |      |              17              |                       |                   |                   |                    |                   |                   |                   |              |
|  1   |      |            |                   |      |      |      |      |      |         |      |      |      |      |      |      |      |      |      |                              |                       |                   |                   |                    |                   |                   |                   |              |
|  2   |      |            |                   |      |      |      |  4   |      |         |      |      |      |      |      |      |      |      |      |                              |          17           |                   |                   |                    |                   |                   |                   |              |
|  3   |      |            |                   |      |      |      |      | 3    |    7    |      |      |      |      |      |      |      |      |      |                              |                       |                   |                   |                    |                   |                   |                   |              |
|  4   |      |            |                   |      |      |      |      |      |         |      |      |      |      |      |      |      |      |      |                              |                       |                   |                   |                    |                   |                   |                   |      17      |
|  5   |      |            |                   |      |      |      |      |      |         |  3   |      |      |      |      |      |      |      |      |                              |                       |                   |                   |                    |                   |                   |                   |              |
|  6   |      |            |                   |      |      |      |      | 6    |    6    |  3   |      |      |      |      |      |      |      |      |                              |                       |                   |                   |                    |                   |                   |                   |              |
|  7   |      |            |                   |      |      |      |      | 3    |    7    |      |      |      |      |      |      |      |      |      |                              |                       |                   |                   |                    |                   |                   |                   |              |
|  8   |      |            |                   |      |      |      |      |      |         |      |      |      |      |      |      |      |      |      |                              |                       |                   |                   |                    |                   |                   |                   |              |
|  9   |      |            |                   |      |      |      |      |      |         |      |      |      |      |      |      |      |      |      |                              |                       |                   |                   |                    |                   |                   |                   |              |
|  10  |      |            |                   |      |      |      |      |      |         |      |      |      |      |      |  14  |      |      |      |                              |                       |        17         |                   |                    |                   |                   |                   |              |
|  11  |      |            |                   |      |      |      |      |      |         |      |      |      |  12  |      |      |  15  |      |      |                              |                       |                   |        17         |         17         |                   |                   |                   |              |
|  12  |      |            |                   |      |      |      |      |      |         |      |      |      |      |      |      |      |  16  |      |                              |                       |                   |                   |                    |        17         |                   |                   |              |
|  13  |      |            |                   |      |      |      |      |      |         |      |      |      |      |      |      |  12  |  16  |  16  |                              |                       |                   |        17         |                    |        17         |        17         |                   |              |
|  14  |      |            |                   |      |      |      |      |      |         |      |      |      |      |      |      |      |      |  16  |                              |                       |                   |                   |                    |                   |        17         |                   |              |
|  15  |      |            |                   |      |      |      |      |      |         |      |  16  |      |      |      |      |      |      |      |                              |                       |                   |                   |                    |                   |                   |        17         |              |
|  16  |      |            |                   |      |      |      |      |      |         |      |      |      |      |      |      |      |      |      |                              |                       |                   |                   |                    |                   |                   |                   |      17      |
|  17  |      |            |                   |      |      |      |      |      |         |      |      |      |      |      |      |      |      |      |                              |                       |                   |                   |                    |                   |                   |                   |      17      |
|  18  |      |            |                   |      |      |      |      |      |         |      |      |      |  9   |      |      |      |      |  9   |                              |                       |                   |                   |                    |                   |                   |                   |              |

- 常量终态：4…7
- 变量终态：17
- 函数名终态：16
- 运算符终态：1…8
- 分隔符终态：9

## 结果分析

![img](https://s2.loli.net/2022/05/17/VWSMJjmIG1g3Ur2.jpg)

![img](https://s2.loli.net/2022/05/17/aX5czPC4Y1K6ie9.jpg)

![img](https://s2.loli.net/2022/05/17/3PhMwcnNB7eSZEt.png)

输入一个字符串后，程序对字符串中的字符逐个进行分析，若检测到多个字符组成的函数名，则将整个函数名进行匹配输出；若检测到错误，如小数点后不为数字，则跳过出错的字符，继续检测后面的字符，若检测到空格、换行符、制表符，则跳过，继续检测后面的字符。

## 源代码

- Operate类

```cpp
class Operate
{
private:
    string input;       //输入字符串
    string output[Max]; //输出结果
    int type[Max];      //输出类型
public:
    int startPostion; //字符开始位置
    int nowPostion;   //字符当前位置
    int length;       //结果个数

    Operate(string s)
    {
        input = s;
        startPostion = 0;
        nowPostion = 0;
        length = 0;
    }

    void getType(int n)
    {

        switch (n)
        {
        case 0:
            cout << "ERROR!";
            break;
        case 1:
            cout << "正弦函数";
            break;
        case 2:
            cout << "余弦函数";
            break;
        case 3:
            cout << "正切函数";
            break;
        case 4:
            cout << "余切函数";
            break;
        case 5:
            cout << "对数函数";
            break;
        case 6:
            cout << "以10为底的对数";
            break;
        case 7:
            cout << "以e为底的对数";
            break;
        case 8:
            cout << "常数π";
            break;
        case 9:
            cout << "常数e";
            break;
        case 10:
            cout << "问号";
            break;
        case 11:
            cout << "分号";
            break;
        case 12:
            cout << "左括号";
            break;
        case 13:
            cout << "右括号";
            break;
        case 14:
            cout << "加号";
            break;
        case 15:
            cout << "减号";
            break;
        case 16:
            cout << "乘号";
            break;
        case 17:
            cout << "除号";
            break;
        case 18:
            cout << "等号";
            break;
        case 19:
            cout << "幂函数/指数函数";
            break;
        case 20:
            cout << "变量";
            break;
        case 21:
            cout << "常数";
            break;
        }
    }
    void getOutputAndType()
    { //输出分析结果及其类型
        cout << "Analyzing……" << endl;
        for (int i = 0; i < length; i++)
        {
            cout << output[i] << "\t:\t";
            getType(type[i]);
            cout << endl;
        }

        cout << "Analysis completed." << endl;
    }

    bool isNumber(char c)
    { //判断当前字符是否为数字
        if (c >= '0' && c <= '9')
            return true;
        return false;
    }

    bool isChar(char c)
    { //判断当前字符是否为字母
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            return true;
        return false;
    }

    bool isblank(char c)
    { //判断当前字符是否为空白
        if (c == ' ' || c == '\t' || c == '\n')
            return true;
        return false;
    }

    int isOperaters(char c)
    { //判断当前字符是否为运算符/分隔符/其他符号，是返回序号，否则返回0
        switch (c)
        {
        case '?':
            return 10;
        case ';':
            return 11;
        case '(':
            return 12;
        case ')':
            return 13;
        case '+':
            return 14;
        case '-':
            return 15;
        case '*':
            return 16;
        case '/':
            return 17;
        case '=':
            return 18;
        case '^':
            return 19;
        default:
            return 0;
        }
    }

    bool isUnderline(char c)
    {
        if (c == '_')
            return true;
        return false;
    }

    void outputing(string s, int n)
    { //记入输出的字符、长度length、记号表序号n
        output[length] = s;
        type[length] = n;
        length += 1;
    }

    string getoutput()
    {
        return *output;
    }

    int gettype()
    {
        return *type;
    }
};
```



