// MagicSquare.cpp 对应书上 S3 的 习题50
//

#include <stdio.h>

#define scanf scanf_s

int main()
{
    printf("Enter the numbers frm 1 to 16 in any order:\n");
    int num[4][4];

    for (int i = 0; i <= 3; i++)
    {
        for (int j = 0; j <= 3;j++)
        {
            scanf("%d", &num[i][j]);            //矩阵式读入十六个数字
        }
    }

    for (int i = 0; i <= 3; i++)
    {
        for (int j = 0; j <= 3; j++)
        {
            printf("%2d ", num[i][j]);          //矩阵型输出十六个数字
        }
        printf("\n");
    }

    printf("Row sums:");                        //列求和
    for (int i = 0; i <= 3; i++)
    {
        int Rsum = 0;
        for (int j = 0; j <= 3; j++)
        {
            Rsum += num[i][j];
        }
        printf("%d ", Rsum);
    }

    printf("\n");

    printf("Column sums:");                     //行求和
    for (int j = 0; j <= 3; j++)
    {
        int Csum = 0;
        for (int i = 0; i <= 3; i++)
        {
            Csum += num[i][j];
        }
        printf("%d ", Csum);
    }

    printf("\n");

    printf("diagonal sums:");
    printf("%d ", num[0][0] + num[1][1] + num[2][2] + num[3][3]);       //对角线求和
    printf("%d\n", num[0][3] + num[1][2] + num[2][1] + num[3][0]);
}