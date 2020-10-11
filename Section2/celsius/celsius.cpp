// celsius.cpp 对应书上 S2.6 的 习题24

#include <stdio.h>

#define scanf scanf_s                       //替换scanf为scanf_s，因为在VS2019里使用scanf会报错。用DEVC++调试时将此行注释掉。

#define FT_TO_CT ((T-32.0)/1.8)     /*宏定义，封装F到C的转换*/
#define CT_TO_FT (T*1.8+32.0)       /*宏定义，封装C到F的转换*/

int main()
{
    int Func;
    {/*该块为实现功能选择*/
    printf("1:C to F\n"); 
    printf("2:F to C\n");
    printf("Please select the Function:");
    scanf("%d", &Func);
    }

    float T=0.0f,T2=0.0f;

    
    if (Func == 1)
    {
        printf("Please enter Celsius:");
        scanf("%f", &T);                    //读取温度
        T2 = CT_TO_FT;
        printf("%.2fC = %.2fF", T, T2);
    }
    else
    {
        printf("Please enter Fahrenheit:");
        scanf("%f", &T);                    //读取温度
        T2 = FT_TO_CT;
        printf("%.2fF= %.2fC", T, T2);
    }

    
}
