#include<iostream>
#include<vector>

using namespace std;

void swap(int& a, int& b)
{
    if(a == b)
        return;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

//各排序算法默认升序排序
vector<int> Array_1 = {3,2,1,4,7,6,5,8,9};
vector<int> Array_2 = {3,2,1,4,7,6,5,8,9};
vector<int> Array_3 = {3,2,1,4,7,6,5,8,9};

//冒泡排序，每轮会把最大的冒泡到最后
//所以，如果两个元素相等，我想你是不会再无聊地把他们俩交换一下的；
//如果两个相等的元素没有相邻，那么即使通过前面的两两交换把两个相邻起来，这时候也不会交换，
//所以相同元素的前后顺序并没有改变
//所以冒泡排序是一种稳定排序算法。

//时间复杂度 O(n^2) ，空间 O(1)， 原地算法，稳定 交换次数O（n^2）
//优化：有一轮没有发生交换时，直接跳出循环
//还有一种冒泡界优化，就是记录下上轮最后交换的index，下一轮只要执行到对应即刻
void BubbleSort(vector<int>& array)
{
    int n = array.size();
    for (int i = n-1; i >= 0;--i)
    {
        bool flag = false;
        for (int j = 0; j < i;++j)
        {
            if(array[j] > array[j+1])
            {
                swap(array[j], array[j + 1]);
                flag = true;
            }
        }
        if(!flag)
            break;
    }
}

//选择排序，对于每一轮，记录一个最小的下标
//时间复杂度 O(n^2) ，空间 O(1)， 不稳定，存在跨越交换 例如：7 7 2
//相比冒泡交换，优势是交换次数为O（n）

//优化：双元选择优化，在每一轮同时维护最大最小值，使遍历次数减少一半，但每轮次的操作变多，少量提升速度
void SelectSort(vector<int>& array)
{
    int n = array.size();
    for (int i = 0; i < n;++i)
    {
        int min = i;
        for (int j = i + 1; j < n;++j)
        {
            if(array[j] < array[min])
            {
                min = j;
            }
        }
        swap(array[i], array[min]);
    }
}


//插入排序，维护一个局部有序，每次将遍历到的元素插入到应该在的位置
//插入的形式：需要把在该元素后的所有元素往后移，不能简单的交换
//时间复杂度 O(n^2) ，空间 O(1)， 稳定
void InsertSort(vector<int>& array)
{
    int n = array.size();
    if( n == 1)
        return;
    for (int i = 1; i < n;++i)
    {
        int temp = array[i];
        
        for (int j = i;j > 0 && array[j-1] > temp;--j)
        {
            array[j] = array[j - 1];
            array[j - 1] = temp;
        }

    }
}

void Print(vector<int>& array)
{
    for (int i = 0; i < array.size();++i)
    {
        cout << array[i] << ' ';
    }
    cout << endl;
}

int main()
{
    BubbleSort(Array_1);
    Print(Array_1);

    SelectSort(Array_2);
    Print(Array_2);

    InsertSort(Array_3);
    Print(Array_3);
    getchar();
}