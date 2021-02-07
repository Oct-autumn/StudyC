#pragma once

#define UP      1
#define DOWN    2
#define LEFT    3
#define RIGHT   4

typedef struct Coordinate
{
	int x;
	int y;
};

typedef struct OpenPointData
{
	Coordinate Father, Own;
	unsigned int G;
	unsigned int H;
	unsigned int F;
};

typedef struct OpenWayPoint
{
	OpenPointData Data;
	OpenWayPoint* next;
};

typedef struct CloseWayPoint
{
	Coordinate Own;
	unsigned G;
	CloseWayPoint* FatherPoint;
	CloseWayPoint* next;
};

extern OpenWayPoint* OpenPointListHead;
extern CloseWayPoint* ClosePointListHead;
extern int OpenPointSum, ClosePointSum;
extern int Sx, Sy;
extern int Ex, Ey;

OpenWayPoint* NewOpenPoint(Coordinate FatherPointCoor, Coordinate OwnCoor, int G, OpenWayPoint* Head);
OpenWayPoint* DelOpenPoint(OpenWayPoint* PointToDelete);
bool CheckWayPoint(int map[MAPx + 2][MAPy + 2], OpenWayPoint* NowPoint, int Direction);
OpenWayPoint* FindSmallist();
CloseWayPoint* NewClosePoint(Coordinate FatherPointCoor, Coordinate OwnCoor, int G, CloseWayPoint* Head);