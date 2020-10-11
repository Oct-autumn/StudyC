// dweight2.cpp 对应书上 S2.5 的 习题22

#include <stdio.h>

#define scanf scanf_s                  //替换scanf为scanf_s，因为在VS2019里使用scanf会报错。用DEVC++调试时将此行注释掉。

int main()
{
    float a = 0.0f, b = 0.0f, c = 0.0f;
    float MV = 0.0f;

    printf("Please enter the length:"); //取长
    scanf("%f", &a);
    printf("Please enter the width:");  //取宽
    scanf("%f", &b);
    printf("Please enter the height:"); //取高
    scanf("%f", &c);

    MV = (a * b * c) / 166;

    printf("\nV=%.0f\n", a * b * c);
    printf("Cost %.2f\n", MV);
}