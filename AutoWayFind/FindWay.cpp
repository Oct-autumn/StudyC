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
	if (!PointToDelete) return NULL;//����ɾ����ָ��

	OpenWayPoint* NextPoint = PointToDelete->next;

	if (NextPoint)
	{//��������һ�ڵ㣬��ת�����ݡ�ɾ����һ�ڵ㲢���ص�ǰָ��
		PointToDelete->Data = NextPoint->Data;
		PointToDelete->next = NextPoint->next;
		free(NextPoint);
        OpenPointSum--;
		return PointToDelete;
	}
	else
	{//����������һ�ڵ㣬��ɾ������β
        if (OpenPointSum == 1)
        {//�����ʣ���һ���ڵ�
            free(PointToDelete);
            OpenPointSum--;
            OpenPointListHead = NULL;
            return NULL;
        }
        else
        {//������������ڵ�
            OpenWayPoint* NowPoint = OpenPointListHead;

            while (NowPoint->next->next)
            {
                NowPoint = NowPoint->next;
            }

            free(NowPoint->next);   //ɾ�����һ���ڵ�
            NowPoint->next = NULL;  //�������һ���ڵ�����ָ��Ϊ��
            OpenPointSum--;
            return NowPoint;
        }
		
	}
    
}

bool CheckWayPoint(int map[MAPx + 2][MAPy + 2], OpenWayPoint* NowPoint, int Direction)
{
    int X, Y;
    //���ݷ���ָʾ��ȡ����������
    switch (Direction)
    {
    case UP://��
        X = NowPoint->Data.Own.x - 1;
        Y = NowPoint->Data.Own.y;
        break;
    case DOWN://��
        X = NowPoint->Data.Own.x + 1;
        Y = NowPoint->Data.Own.y;
        break;
    case LEFT://��
        X = NowPoint->Data.Own.x;
        Y = NowPoint->Data.Own.y - 1;
        break;
    case RIGHT://��
        X = NowPoint->Data.Own.x;
        Y = NowPoint->Data.Own.y + 1;
        break;
    default://�쳣
        printf("ERROR UNacceptable Direction\n");
        return false;
        break;
    }

    if ((map[X][Y] & map_WALKABLE) && (~map[X][Y] & map_CLOSE))
    {
        OpenWayPoint* Exist = NULL;

        //��������·�����б����õ��Ƿ���ֹ�
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
        {//���ڣ����Ը���G��F�͸��ڵ�
            unsigned int NewG = NowPoint->Data.G + 1;
            if (NewG < Exist->Data.G)
            {
                Exist->Data.G = NewG;
                Exist->Data.F = Exist->Data.G + Exist->Data.H;
                Exist->Data.Father = NowPoint->Data.Own;
            }
        }
        else
        {//�����ڣ������
            if (map[X][Y] & map_END)
            {//�����յ㣬�򷵻�false��ֹ����
                map[X][Y] |= map_OPEN;
                ClosePointListHead = NewClosePoint(NowPoint->Data.Father, NowPoint->Data.Own, NowPoint->Data.G, ClosePointListHead);//�ѵ�ǰ�ڵ���ȷ��·�����б�
                ClosePointListHead = NewClosePoint(NowPoint->Data.Own, { X, Y }, NowPoint->Data.G + 1, ClosePointListHead);//���յ���ȷ��·�����б�
                return false;
            }
            else
            {//�������յ㣬��֮��ӽ�����·�����б���
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

    //����ȷ��·�����б����Ҹõ�ĸ��ڵ�
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