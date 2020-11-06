// qsort1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
bool exchange_int(int* a,int* b)    //int交换函数
{
    int c;
    c = *a;
    *a = *b;
    *b = c;
    return true;
}
*/

bool printf_array_int(int a[], int num /*数组中项的个数*/)  //数组输出函数
{
    for (int i = 0; i < num; i++)
    {
        printf("%6d ", a[i]);
    }
    printf("\n");

    return true;
}

int* quickSort_array_int(int a[], int L, int R)    //int快速排序函数
{
    if (L >= R) return a;

    int i = L; int j = R; int key = a[L];//选择左一为基准值

    while (i < j) {

        while (i < j && a[j] >= key) j--;//从右向左找第一个小于key的值

        if (i < j)
        {
            a[i] = a[j];
            i++;
        }

        while (i < j && a[i] <  key) i++;//从左向右找第一个大于key的值

        if (i < j)
        {
            a[j] = a[i];
            j--;
        }
    }
    
    a[i] = key;

    printf_array_int(a, 20);
    
    quickSort_array_int(a, L, i - 1);//递归调用处理左侧
    quickSort_array_int(a, i + 1, R);//递归调用处理右侧
}

int main()
{
    int a[20];

    srand((unsigned)time(NULL));
    for (int i = 0; i < 20; i++) a[i] = rand();

    for (int i = 0; i < 20; i++)
    {
        printf("%6d ", a[i]);
    }
    printf("\n");
    
    printf_array_int(quickSort_array_int(a, 0, 20 - 1), 20);

    return 0;
}

/*
void quickSort(int a[], int l, int r)
{
    if (l >= r)
        return;

    int i = l; int j = r; int key = a[0];//选择第一个数为key

    while (i < j) {

        while (i < j && a[j] >= key)//从右向左找第一个小于key的值
            j--;
        if (i < j) {
            a[i] = a[j];
            i++;
        }

        while (i < j && a[i] < key)//从左向右找第一个大于key的值
            i++;

        if (i < j) {
            a[j] = a[i];
            j--;
        }
    }
    //i == j
    a[i] = key;
    quickSort(a, l, i - 1);//递归调用
    quickSort(a, i + 1, r);//递归调用
}
*/