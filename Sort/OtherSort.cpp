#include <vector>
#include <iostream>

using namespace std;

void swap(int& a, int& b)
{
    if(a == b)
        return;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void Print(vector<int>& array)
{
    for (int i = 0; i < array.size();++i)
    {
        cout << array[i] << ' ';
    }
    cout << endl;
}


//各排序算法默认升序排序
vector<int> Array_1 = {3,2,1,4,7,6,5,8,9};
vector<int> Array_2 = {3,2,1,4,7,6,5,8,9};
vector<int> Array_3 = {3,2,1,4,7,6,5,8,9};
vector<int> Array_4 = {3,2,1,4,7,6,5,8,9};
vector<int> Array_5 = {3,2,1,4,7,6,5,8,9};

//归并排序用来存放临时变量
vector<int> MergeResult(9);

//希尔排序：简单插入排序的改进
//1.简单插入排序对排序程度较高的序列有较高的效率。假设初始序列完全排序，每一轮只需要比较1次，会是O（n）的复杂度，冒泡排序和选择排序做不到这一点，仍需要O（n^2）
//2.但是简单插入排序每次比较最多将数字移动一位，效率较低
//基于此，希尔排序改进第二点，使其成为增量递减排序，不同的算法对应增量序列生成式，复杂度也需要根据不同增量讨论,空间复杂度为O（1），增量序列一般能将n^2优化成n^4/3,n^3/2
//显然不稳定，gap排时肯定不能保证原有顺序了
//最早的突破O（n^2）的算法，利用了长距离交换可能减少多个逆序对的原理，后续快排，堆排也是这个原理
//这里增量先采用Shell增量：N/2^k ，N为数组长度，例如N == 11 ，增量序列为{1,2,5}，即gap用n/2开始，不断除2直到gap==1

void ShellSort(vector<int>& array)
{
    int n = array.size();
    if(n < 2)
        return;
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int start = 0; start < gap;start++)
        {
            for (int i = start + gap; i < n;i += gap)
            {
                int target = array[i];
                int j = i - gap;
                for (; j >= 0;j-=gap)
                {
                    if(target < array[j])
                        array[j + gap] = array[j];
                    else
                        break;
                }
                if(j != i - gap)
                    array[j + gap] = target;
            }
        }
    }
}

//归并排序：分治思想，将原数组递归或迭代的分为左右两半，直至长度为1，然后对左右数组进行合并
//稳定,时间复杂度O（nlogn）,空间复杂度O（n），这里非原地，原地的话应该为O（n）    稳定的
//两种实现方式：自顶向下（不断二分）或自底向上（单个元素不断合并）
//原地归并，创建
class Merge_Sort
{
public:
    static void MergeSort(vector<int>& array,int startIndex,int endIndex)
    {       
        //如果开头大于等于结尾，说明已经分完了，返回
        if(startIndex >= endIndex) 
            return;
        //将中间数求出来，用中间数把数列分为两段
        int mid = startIndex + (endIndex - startIndex) / 2;
        MergeSort(array,startIndex,mid);
        MergeSort(array,mid + 1, endIndex);
        Merge(array, startIndex, mid, endIndex);
    }

    static void Merge(vector<int>& array,int low,int mid,int high)
    {
        int i = low;
        int j = mid + 1;
        int k = i;
        //左右两个数列合并
        while(i <= mid && j <= high)
        {
            if(array[i] < array[j])
            {
                MergeResult[k++] = array[i++];
            }
            else
            {
                MergeResult[k++] = array[j++];
            }
        }
        while (i<=mid)
		    MergeResult[k++]=array[i++];

	    while (j<=high)
		    MergeResult[k++]=array[j++];

        //放回原位
	    for(int i = low;i<=high;i++)
		    array[i]=MergeResult[i];
    }
};

//快速排序:每轮选定一个数，确定其位置，将小于该元素的均放在左边，将大于该元素的均放在右边然后左右再递归使用
//显然不稳定
//时间复杂度：最好为O（nlogn），最差为O（n^2）(即数组已经有序，这样每轮位置不变但是都得遍历一次O(n))
//空间复杂度：原地交换，考虑递归使用的栈空间
//优化：双轴快排，两个基准三个子区间，能将时间复杂度优化为O（nlog3n）3为底数
void QuickSort(vector<int>& array,int start,int end)
{
    if(start >= end)
        return;

    int temp = array[start];

    int low = start;
    int high = end;

    while(low < high)
    {
        while(low < high && array[high] >= temp)
        {
            high--;
        }
        if(low < high)
        {
            array[low++] = array[high];
        }

        while(low < high && array[low] <= temp)
        {
            low++;
        }
        if(low < high)
        {
            array[high--] = array[low];
        }
    }
    array[low] = temp;
    QuickSort(array, start, low-1);
    QuickSort(array, low + 1, end);
}

//堆排序：将输入数组建立为一个大顶堆，之后反复取出堆顶并对剩余元素重建堆，输出的元素逆序排列即可从小到大（C++中priority_queue默认为大顶堆）
//基本步骤：1.将原数组建堆 2.交换堆顶和当前未排序部分最末位元素 3.下溯调整堆
//不稳定
//堆化方法：根据完全二叉树节点特性：i的左儿子为2i+1，右儿子为2i+2，父节点为i/2
//下溯方法为核心，恢复堆序的过程就是将影响排序的元素不断向下层移动
int main()
{
    ShellSort(Array_1);
    Print(Array_1);

    Merge_Sort::MergeSort(Array_2,0,Array_2.size()-1);
    Print(Array_2);

    QuickSort(Array_3,0,Array_3.size()-1);
    Print(Array_3);
    getchar();
}