#include <iostream>

using namespace std;

//三种swap方式

//1.临时量交换
void swap_temp(int& a,int& b)
{
    int temp = a;
    a = b;
    b = temp;
}


//加减运算（注意溢出）
void swap_self(int& a,int& b)
{
    a = a+b;
    b = a-b;
    a = a-b;
}

//异或算法,既不需要临时空间，也不需要考虑溢出问题（需要两个数不相等，否则会导致均为0）
void swap_bit(int& a,int& b)
{
    if(a == b)
        return;
    a = a^b;
    b = a^b;
    a = a^b;
}

int main()
{
    int a = 5;
    int b = 6;
    cout << a << endl << b << endl;

    swap_temp(a,b);
    cout << a << endl << b << endl;

    swap_self(a,b);
    cout << a << endl << b << endl;

    swap_bit(a,b);
    cout << a << endl << b << endl;
    getchar();
}