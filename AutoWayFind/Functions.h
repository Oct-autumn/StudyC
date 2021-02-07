#pragma once

#define BLACK   0
#define BLUE    1
#define GREEN   2
#define LLBLUE  3
#define RED     4
#define PURPLE  5
#define YELLOW  6
#define WHITE   7
#define GRAY    8
#define LBLUE   9
#define LGREEN  10
#define LLLBLUE 11
#define LRED    12
#define LPURPLE 13
#define LYELLOW 14
#define LWHITE  15

#define map_WALL        0x00    //0000 0000
#define map_WALKABLE    0x01    //0000 0001
#define map_START       0x02    //0000 0010
#define map_END         0x04    //0000 0100
#define map_OPEN        0x08    //0000 1000
#define map_CLOSE       0x10    //0001 0000
#define map_ROAD        0x20    //0010 0000


void setcolor(unsigned short ForeColor = WHITE, unsigned short BackColor = BLACK);
void printmap();
void cls();

#define MAPx 10
#define MAPy 10

extern int posi[MAPx + 2][MAPy + 2];