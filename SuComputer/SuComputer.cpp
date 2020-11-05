// SuComputer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <string.h>

int main()
{
    long M1, M2, R1, R2, R3;
    char command[200+1];

    R1 = R2 = R3 = 0;

    while(scanf_s("%d %d\n", &M1, &M2) != EOF)
    {
        gets_s(command);

        for (int i = 0; i < strlen(command); i++)
        {
            switch (command[i])
            {
            case 'A': R1 = M1; break;
            case 'B': R2 = M2; break;
            case 'C': M1 = R3; break;
            case 'D': M2 = R3; break;
            case 'E': R3 = R1 + R2; break;
            case 'F': R3 = R1 - R2; break;
            default:
                printf("ERROR: BAD COMMAND!");
                break;
            }
        }

        printf("%d %d", M1, M2);
    }

    return 0;
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
