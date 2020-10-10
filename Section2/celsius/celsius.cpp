// celsius.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#define FT_TO_CT ((T-32.0)/1.8)
#define CT_TO_FT (T*1.8+32.0)

int main()
{
    int Func;
    printf("1:C to F\n"); 
    printf("2:F to C\n");
    printf("Please select the Function:");
    scanf_s("%d", &Func);
    
    float T=0.0f,T2=0.0f;

    
    if (Func == 1)
    {
        printf("Please enter Celsius:");
        scanf_s("%f", &T);
        T2 = CT_TO_FT;
    }
    else
    {
        printf("Please enter Fahrenheit:");
        scanf_s("%f", &T);
        T2 = FT_TO_CT;
    }

    printf("%.2f", T2);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
