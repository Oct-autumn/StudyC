// AutoWayFind.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdlib.h>
#include <Windows.h>

#include "Functions.h"
#include "FindWay.h"



int main()
{
    printmap();

    do
    {
        printf("请输入起点坐标：");
        scanf_s("%d %d", &Sx, &Sy);
        if (posi[Sx][Sy] == map_WALKABLE)
        {
            posi[Sx][Sy] |= map_START;
            printf("起点已设定\n");
            break;
        }
        printf("该点不是可行走点\n");
    } while (1);

    cls();
    printmap();
    do
    {
        printf("请输入终点坐标：");
        scanf_s("%d %d", &Ex, &Ey);
        if (posi[Ex][Ey] & map_WALKABLE)
        {
            posi[Ex][Ey] |= map_END;
            printf("终点已设定\n");
            break;
        }        
        if (posi[Ex][Ey] & map_START)
            printf("该点与起点重合了\n");
        else if (~posi[Ex][Ey] & map_WALKABLE)
            printf("该点不是可行走点\n");
    } while (1);

    cls();
    printmap();
    printf("稍等，进行数据预处理...\n");

    int WayPointSum = 0;

    for (int i = 1; i <= MAPx; i++)
        for (int j = 1; j <= MAPx; j++)
        {
            if (posi[i][j] & map_WALKABLE) WayPointSum++;
        }
    
    OpenPointListHead = NewOpenPoint({ -1, -1 }, { Sx, Sy }, 0, OpenPointListHead);

    cls();
    printmap();
    printf("正在计算路径...\n");

    OpenWayPoint* NowPoint = OpenPointListHead;
    
    
    while (1)
    {
        //检查上下左右的格子
        if (!CheckWayPoint(posi, NowPoint, DOWN))   break;
        if (!CheckWayPoint(posi, NowPoint, UP))     break;
        if (!CheckWayPoint(posi, NowPoint, LEFT))   break;
        if (!CheckWayPoint(posi, NowPoint, RIGHT))  break;

        cls();
        printmap();
        printf("正在计算路径...\n");

        
        ClosePointListHead = NewClosePoint(NowPoint->Data.Father, NowPoint->Data.Own, NowPoint->Data.G, ClosePointListHead);
        posi[NowPoint->Data.Own.x][NowPoint->Data.Own.y] ^= map_OPEN;
        posi[NowPoint->Data.Own.x][NowPoint->Data.Own.y] |= map_CLOSE;
        DelOpenPoint(NowPoint);

        NowPoint = FindSmallist();
        
        cls();
        printmap();
        if (!OpenPointSum)
        {
            
            setcolor(LWHITE, LRED);
            printf("终点不可抵达\n");
            setcolor();
            return 0;
        }
        else
        {
            printf("正在计算路径...\n");
            Sleep(10);
        }
    }

    CloseWayPoint* NowPoint_S = ClosePointListHead;
    while (NowPoint_S)
    {
        posi[NowPoint_S->Own.x][NowPoint_S->Own.y] |= map_ROAD;
        NowPoint_S = NowPoint_S->FatherPoint;
    }
    
    cls();
    printmap();
    setcolor(LWHITE, LGREEN);
    printf("路线规划完毕，共%d步\n", ClosePointListHead->G);
    setcolor();

return 0;
}