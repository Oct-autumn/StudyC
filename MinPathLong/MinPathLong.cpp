// MinPathLong.cpp : 最短路径问题，Dijkstra(迪杰斯特拉)算法 实践

#include <stdio.h>
#include <stdlib.h>

#define PointSum_Max 128

typedef struct PathLength
{
    PathLength* before;

    int point1;
    int point2;
    int length;

    PathLength* next;
};

int FindMin(int Array[], int Sum);
PathLength* NewNode(int Point1, int Point2, int Length, PathLength* BeforeNode);    //创建新节点函数
void DeleteNode(PathLength* Node_todelete); //删除节点函数
int TravelFind(int PointToFind);//寻找相关节点函数

//定义全局变量
int UnKnownPoint[PointSum_Max], KnownPoint[PointSum_Max];   //两个全局数组
PathLength* Head = NULL;//距离链表 头指针
PathLength* NowNode = NULL;//当前节点

int main()
{
    int BeginPoint, EndPoint, PointSum, PointLengthSum;
    
    scanf_s("%d %d %d %d", &BeginPoint, &EndPoint, &PointSum, &PointLengthSum);

    //初始化已知最短路径数组
    for (int i = 0; i < PointSum_Max; i++)
    {
        KnownPoint[i] = 0; 
    }
    //初始化未知最短路径数组
    for (int i = 0; i < PointSum_Max; i++)
    {
        UnKnownPoint[i] = 1; 
    }

    //读取点间距离
    for (int i = 0; i < PointLengthSum; i++)
    {
        int Point1, Point2, Length;
        scanf_s("%d %d %d", &Point1, &Point2, &Length);

        NowNode = NewNode(Point1, Point2, Length, NowNode);
        if (i == 0) Head = NowNode;
    }

    //记录与起点直连的点到起点的距离
    TravelFind(BeginPoint);

    int MinPoint = FindMin(KnownPoint, PointSum);//到起点距离最小的节点
    
    TravelFind(MinPoint);
}

//寻找最小量(上限65535)
int FindMin(int Array[], int Sum)
{
    int MinData = 0, Min = 65535;
    for (int i = 0; i < Sum; i++)
    {
        if ((Array[i] < Min)&&(Array[i] != -1))
        {
            MinData = i;
            Min = Array[i];
        }
    }
    return MinData;
}

PathLength* NewNode(int Point1, int Point2, int Length, PathLength* BeforeNode) //创建新节点函数
{
    PathLength* p = (PathLength*)malloc(sizeof(PathLength));				//新建节点并为之分配内存空间

    if (p == NULL) exit(-1);								//检查是否创建成功

    //将内容存储到新节点里
    p->point1 = Point1;
    p->point2 = Point2;
    p->length = Length;

    //进行索引
    if (BeforeNode) BeforeNode->next = p;					//若前一项存在，则向前一项添加索引
    p->before = BeforeNode;									//新节点的前索引
    p->next = NULL;											//新节点的后索引
    
    return p;												//返回新节点的内存指针
}

void DeleteNode(PathLength* Node_todelete)	//删除节点函数
{
    PathLength* beforeNode = Node_todelete->before;	//找到上一节点
    PathLength* nextNode = Node_todelete->next;		//找到下一节点

    //进行索引
    beforeNode->next = nextNode;
    nextNode->before = beforeNode;

    //删除节点释放内存
    free(Node_todelete);

    return;
}

int TravelFind(int PointToFind)//寻找相关节点函数
{
    NowNode = Head;//将当前指针移至链表头
    while (NowNode)//开始遍历
    {
        if (NowNode->point1 == PointToFind)
        {
            KnownPoint[NowNode->point2] = NowNode->length;
            UnKnownPoint[NowNode->point2] = 0;
            DeleteNode(NowNode);
            continue;
        }
        if (NowNode->point2 == PointToFind)
        {
            KnownPoint[NowNode->point1] = NowNode->length;
            UnKnownPoint[NowNode->point1] = 0;
            DeleteNode(NowNode);
            continue;
        }
        NowNode = NowNode->next;//下一数据
    }
}