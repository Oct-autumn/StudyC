// dollar1.cpp 对应书上 S2 的 习题34

#include <stdio.h>

#define scanf scanf_s                       //替换scanf为scanf_s，因为在VS2019里使用scanf会报错。用DEVC++调试时将此行注释掉。

int main()
{
    int amount;

    printf("Enter a dollar amount(Float is not admitted):");  //读取金额
    scanf("%d", &amount);

    printf("$20 bills:%d\n", amount / 20);  //计算并输出20美金钞票数目
    amount = amount - (amount / 20) * 20;

    printf("$10 bills:%d\n", amount / 10);  //计算并输出10金钞票数目
    amount = amount - (amount / 10) * 10;

    printf(" $5 bills:%d\n", amount / 5);   //计算并输出5美金钞票数目
    amount = amount - (amount / 5) * 5;

    printf(" $1 bills:%d\n", amount);       //计算并输出1美金钞票数目

    return 0;
}