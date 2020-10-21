// addfrac.cpp 对应书上 S3.2 的 习题46
//

#include <stdio.h>

#define scanf scanf_s                       //替换scanf为scanf_s，因为在VS2019里使用scanf会报错。用DEVC++调试时将此行注释掉。

int main()
{
    int FU, FD, SU, SD;

    printf("Enter first fraction:");
    scanf("%d/%d", &FU, &FD);
    printf("Enter second fraction:");
    scanf("%d/%d", &SU, &SD);

    printf("The sum is %d/%d", FU * SD + SU * FD, FD * SD);

}