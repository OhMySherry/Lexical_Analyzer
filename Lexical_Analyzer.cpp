#include "Functions.h"

int main()
{
    cout << "please input the string：";
    string a;
    cin >> a;
    // string test = "x=0.5*PI;y=E;?1/3*(ln(y)+5*sin(x))+(7+z)^2;";
    // string test = "01x;";
    // analyzed(test);
    Analyzer(a);
    system("pause");
}