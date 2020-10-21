// upc.cpp 对应书上 S4.1 的 习题57

#include <stdio.h>

#define scanf scanf_s                       //替换scanf为scanf_s，因为在VS2019里使用scanf会报错。用DEVC++调试时将此行注释掉。

int main()
{
    int num[12];

    printf("Enter the first number:");      //读入第一位数字
    scanf("%d", &num[0]);

    printf("Enter the number2~6:");         //读入第二至六位数字
    for (int i = 1; i <= 5; i++)
    {
        scanf("%1d", &num[i]);
    }

    printf("Enter the number7~11:");        //读入第七至十一位数字
    for (int i = 6; i <= 10; i++)
    {
        scanf("%1d", &num[i]);
    }

    int sum1, sum2;
    sum1 = sum2 = 0;
    
    for (int i = 0; i <= 10; i += 2)        //奇位求和
    {
        sum1 += num[i];
    }
    for (int i = 1; i <= 9; i += 2)         //偶位求和
    {
        sum2 += num[i];
    }

    num[11] = (sum1 * 3 + sum2 - 1) % 10;   //计算验证位

    printf("Check number is:%d\n", num[11]);
}