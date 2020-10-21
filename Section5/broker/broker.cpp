// broker.cpp 对应书上 S5.2 的 习题81

#include <stdio.h>

#define scanf scanf_s                       //替换scanf为scanf_s，因为在VS2019里使用scanf会报错。用DEVC++调试时将此行注释掉。

int main()
{
    int Money = 0;
    float commi = 0.0f;

    printf("Enter value of trade:");
    scanf("%d", &Money);

    if (Money < 2500){commi = 30.0f + Money * 0.017f;}
    else if (Money>=2500 && Money<6250)         {commi = 56.0f + Money * 0.0066f;}   //else if进行选择判断
    else if (Money >= 6250 && Money < 20000)    {commi = 76.0f + Money * 0.0034f;}
    else if (Money >= 20000 && Money < 50000)   {commi = 100.0f + Money * 0.0022f;}
    else if (Money >= 50000 && Money <= 500000) {commi = 155.0f + Money * 0.0011f;}
    else{commi = 255.0f + Money * 0.0009f;}

    if (commi < 39.0f) commi = 39.0f;

    printf("%.2f", commi);
}
