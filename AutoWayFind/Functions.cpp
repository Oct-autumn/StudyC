#include <stdio.h>
#include <Windows.h>
#include "Functions.h"

/*地图
      Y 1 2 3 4 5 6 7 8 9 10
    X■■■■■■■■■■■■
    1■□■□□□■□□□□■
    2■□■□■□■□■□□■
    3■□■□■□■□■■□■
    4■□■■■□□□■□□■
    5■□□□□■■□□■□■
    6■□■□□□■□□■□■
    7■□■□■□■■□■□■
    8■□■□■□□□□■■■
    9■□■■■■■□■■□■
   10■□□□□■□□■□□■
     ■■■■■■■■■■■■
*/

int posi[MAPx + 2][MAPy + 2] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0,
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,
    0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0,
    0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0,
    0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0,
    0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0,
    0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
    0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void cls()
{
    printf("\033c");
}

void setcolor(unsigned short ForeColor, unsigned short BackColor)
{
    HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄
    SetConsoleTextAttribute(hdl, ForeColor + BackColor * 0x10);
}

void printmap()
{
    printf("当前地图：\n");

    for (int i = 0; i < MAPx + 2; i++)
    {
        for (int j = 0; j < MAPy + 2; j++)
        {
            if (posi[i][j] & map_START)
            {
                setcolor(WHITE, LBLUE);
                printf("☆");
                continue;
            }
            if (posi[i][j] & map_END)
            {
                setcolor(WHITE, LRED);
                printf("☆");
                continue;
            }
            if (posi[i][j] & map_ROAD)
            {
                setcolor(GREEN, BLACK);
                printf("□");
                continue;
            }
            if (posi[i][j] & map_OPEN)
            {
                setcolor(LBLUE, BLACK);
                printf("□");
                continue;
            }
            if (posi[i][j] & map_CLOSE)
            {
                setcolor(RED, BLACK);
                printf("□");
                continue;
            }
            if (posi[i][j] & map_WALKABLE)
            {
                setcolor(GRAY, BLACK);
                printf("□");
                continue;
            }
            if (posi[i][j] == map_WALL)
            {
                setcolor(LWHITE, BLACK);
                printf("■");
                continue;
            }
        }
        printf("\n");
    }

    setcolor();
}