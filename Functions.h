#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
const int Max = 100;
const string keyword[] = {"sin", "cos", "tg", "ctg", "log", "lg", "ln", "PI", "E"};

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

int isKeyword(string s)
{ //判断是否为多字母函数,是返回序号，否则返回0
    for (int i = 0; i < 9; i++)
        if (s == keyword[i])
            return i + 1;
    return 0;
}

void Analyzer(string str)
{
    int slength = str.length();
    string isKey;    //判断是否为多字符关键字
    char nowc;       //当前字符
    int state = 0;   //状态
    int type = 0;    //类型
    Operate op(str); //创建并初始化op这个对象
    int num = 0;

    while (true) //读取字符
    {
        if (op.nowPostion >= slength)
        {
            break;
        }
        else
        {
            nowc = str[op.nowPostion];
        }
        switch (state)
        {
        case 0:              //初始状态
            if (nowc == '$') //终结符,到末尾结束不分析
            {
                break;
            }
            //如果是运算符、则保存当前运算符，返回其类型并更新起始字符
            type = op.isOperaters(nowc);
            if (type > 0)
            {
                op.outputing(str.substr(op.startPostion, 1), type);
                op.nowPostion++;
                op.startPostion = op.nowPostion;
                break; // switch
            }
            //空白符判断
            if (op.isblank(nowc))
            {
                op.nowPostion++;
                op.startPostion = op.nowPostion;
                break;
            }
            //字符或者下划线判断,是转状态1判断是否是函数还是变量
            if (op.isChar(nowc) || op.isUnderline(nowc))
            {
                state = 1;
                op.nowPostion++;
                break;
            }
            //判断是否是数字0，转到判断数字正确与否转状态2
            if (nowc == '0')
            {
                state = 2;
                op.nowPostion++;
                break;
            }
            //数字1-9,状态4判断数字是否标准
            if (nowc >= '1' && nowc <= '9')
            {
                state = 4;
                op.nowPostion++;
                break;
            }
            break;
        case 1: //识别字符串(变量名)
            if (op.isNumber(nowc) || op.isUnderline(nowc) || op.isChar(nowc))
            {
                op.nowPostion++;
                break;
            }
            type = 20;
            //识别当前标识符是否为关键字(_下划线bug),若是返回其类型并更新起始字符
            isKey = str.substr(op.startPostion, op.nowPostion - op.startPostion);
            if (isKeyword(isKey) > 0)
            {
                type = isKeyword(isKey);
            }
            op.outputing(isKey, type);
            op.startPostion = op.nowPostion;
            state = 0; //结束判断转0
            break;
        case 2:              //识别0开头
            if (nowc == '.') //小数,转到判断小数的状态3
            {
                state = 3;
                op.nowPostion++;
                break;
            }
            if (op.isOperaters(nowc) > 0) //运算符则转到0
            {
                state = 0;
                // op.outputing('0',21);
                break;
            }
            //若输入有误，转回状态0,更新起始字符
            op.outputing("0开头常数,跳过", 0);
            op.startPostion = op.nowPostion;
            state = 0;
            break;
            //对小数点后的0-9进行识别
        case 3:
            if (op.isNumber(nowc) == false && num == 0)
            {
                op.outputing("小数点后非数字,跳过", 0);
                op.startPostion = op.nowPostion;
                state = 0;
                break;
            }
            if (op.isNumber(nowc))
            {
                num++;
                op.nowPostion++;
                break;
            }
            //识别结束后，返回其数值及类型，重新返回状态0,更新起始字符
            if (op.isNumber(nowc) == false && num == 1)
            {
                op.outputing(str.substr(op.startPostion, op.nowPostion - op.startPostion), 21);
                op.startPostion = op.nowPostion;
                state = 0;
                num = 0;
                break;
            }
            //识别小数点前的整数，首位从1-9开始
        case 4:
            //识别整数部分0-9
            if (op.isNumber(nowc))
            {
                op.nowPostion++;
                break;
            }
            //若当前字符是小数点，则转换到状态3，开始识别小数
            if (nowc == '.')
            {
                state = 3;
                op.nowPostion++;
                break;
            }
            //否则，识别完返回其类型，回到状态0，更新起始字符
            op.outputing(str.substr(op.startPostion, op.nowPostion - op.startPostion), 21);
            op.startPostion = op.nowPostion;
            state = 0;
            break;
        }
    }
    op.getOutputAndType();
}