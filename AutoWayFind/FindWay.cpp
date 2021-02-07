#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"
#include "FindWay.h"

OpenWayPoint* OpenPointListHead = NULL;
CloseWayPoint* ClosePointListHead = NULL;
int OpenPointSum = 0, ClosePointSum = 0;
int Sx, Sy;
int Ex, Ey;

OpenWayPoint* NewOpenPoint(Coordinate FatherPointCoor, Coordinate OwnCoor, int G, OpenWayPoint* Head)
{
	OpenWayPoint* NewPoint = (OpenWayPoint*)malloc(sizeof(OpenWayPoint));
	NewPoint->Data.Father = FatherPointCoor;
	NewPoint->Data.Own = OwnCoor;
	NewPoint->Data.G = G;
	NewPoint->Data.H = abs(NewPoint->Data.Own.x - Ex) + abs(NewPoint->Data.Own.y - Ey);
	NewPoint->Data.F = NewPoint->Data.G + NewPoint->Data.H;

	NewPoint->next = Head;

	OpenPointSum++;
	return NewPoint;
}

OpenWayPoint* DelOpenPoint(OpenWayPoint* PointToDelete)
{
	if (!PointToDelete) return NULL;//避免删除空指针

	OpenWayPoint* NextPoint = PointToDelete->next;

	if (NextPoint)
	{//若存在下一节点，则转移数据、删除下一节点并返回当前指针
		PointToDelete->Data = NextPoint->Data;
		PointToDelete->next = NextPoint->next;
		free(NextPoint);
        OpenPointSum--;
		return PointToDelete;
	}
	else
	{//若不存在下一节点，即删除链表尾
        if (OpenPointSum == 1)
        {//如果仅剩最后一个节点
            free(PointToDelete);
            OpenPointSum--;
            OpenPointListHead = NULL;
            return NULL;
        }
        else
        {//如果还有其他节点
            OpenWayPoint* NowPoint = OpenPointListHead;

            while (NowPoint->next->next)
            {
                NowPoint = NowPoint->next;
            }

            free(NowPoint->next);   //删除最后一个节点
            NowPoint->next = NULL;  //重设最后一个节点的向后指针为空
            OpenPointSum--;
            return NowPoint;
        }
		
	}
    
}

bool CheckWayPoint(int map[MAPx + 2][MAPy + 2], OpenWayPoint* NowPoint, int Direction)
{
    int X, Y;
    //根据方向指示获取待查点的坐标
    switch (Direction)
    {
    case UP://上
        X = NowPoint->Data.Own.x - 1;
        Y = NowPoint->Data.Own.y;
        break;
    case DOWN://下
        X = NowPoint->Data.Own.x + 1;
        Y = NowPoint->Data.Own.y;
        break;
    case LEFT://左
        X = NowPoint->Data.Own.x;
        Y = NowPoint->Data.Own.y - 1;
        break;
    case RIGHT://右
        X = NowPoint->Data.Own.x;
        Y = NowPoint->Data.Own.y + 1;
        break;
    default://异常
        printf("ERROR UNacceptable Direction\n");
        return false;
        break;
    }

    if ((map[X][Y] & map_WALKABLE) && (~map[X][Y] & map_CLOSE))
    {
        OpenWayPoint* Exist = NULL;

        //搜索开放路径点列表，检查该点是否出现过
        OpenWayPoint* NowPoint_S = OpenPointListHead;
        do
        {
            if (NowPoint_S->Data.Own.x == X && NowPoint_S->Data.Own.y == Y)
            {
                Exist = NowPoint_S;
                break;
            }
            NowPoint_S = NowPoint_S->next;
        } while (NowPoint_S);

        if (Exist)
        {//存在，则尝试更新G、F和父节点
            unsigned int NewG = NowPoint->Data.G + 1;
            if (NewG < Exist->Data.G)
            {
                Exist->Data.G = NewG;
                Exist->Data.F = Exist->Data.G + Exist->Data.H;
                Exist->Data.Father = NowPoint->Data.Own;
            }
        }
        else
        {//不存在，则添加
            if (map[X][Y] & map_END)
            {//若是终点，则返回false中止计算
                map[X][Y] |= map_OPEN;
                ClosePointListHead = NewClosePoint(NowPoint->Data.Father, NowPoint->Data.Own, NowPoint->Data.G, ClosePointListHead);//把当前节点存进确定路径点列表
                ClosePointListHead = NewClosePoint(NowPoint->Data.Own, { X, Y }, NowPoint->Data.G + 1, ClosePointListHead);//把终点存进确定路径点列表
                return false;
            }
            else
            {//若不是终点，则将之添加进开放路径点列表中
                map[X][Y] |= map_OPEN;
                OpenPointListHead = NewOpenPoint(NowPoint->Data.Own, { X, Y }, NowPoint->Data.G + 1, OpenPointListHead);
                return true;
            }
        }
    }

    return true;
}

OpenWayPoint* FindSmallist()
{
    unsigned int minF = 4294967295;
    OpenWayPoint* MinPoint = NULL;
    OpenWayPoint* NowPoint = OpenPointListHead;

    while (NowPoint)
    {
        if (NowPoint->Data.F < minF)
        {
            MinPoint = NowPoint;
            minF = NowPoint->Data.F;
        }
        NowPoint = NowPoint->next;
    }

    return MinPoint;
}

CloseWayPoint* NewClosePoint(Coordinate FatherPointCoor, Coordinate OwnCoor, int G, CloseWayPoint* Head)
{
    CloseWayPoint* NewPoint = (CloseWayPoint*)malloc(sizeof(CloseWayPoint));
    CloseWayPoint* FatherPoint = NULL;

    CloseWayPoint* Exist = NULL;

    //搜索确定路径点列表，查找该点的父节点
    CloseWayPoint* NowPoint_S = ClosePointListHead;
    while (NowPoint_S)
    {
        if (NowPoint_S->Own.x == FatherPointCoor.x && NowPoint_S->Own.y == FatherPointCoor.y)
        {
            Exist = NowPoint_S;
            break;
        }
        NowPoint_S = NowPoint_S->next;
    }

    NewPoint->FatherPoint = Exist;
    NewPoint->G = G;
    NewPoint->Own = OwnCoor;

    NewPoint->next = Head;

    ClosePointSum++;
    return NewPoint;
}