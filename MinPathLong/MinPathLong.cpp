// MinPathLong.cpp : 最短路径问题，Dijkstra(迪杰斯特拉)算法 实践

#include <stdio.h>
#include <stdlib.h>

#define PointSum_Max 8

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
int* KnownPoint = NULL;     //已经确定的点
int *UnKnownPoint = NULL;   //尚未确定的点
int *LastRound = NULL; //上一次被查找的点
PathLength* Head = NULL;//距离链表 头指针
PathLength* NowNode = NULL;//当前节点

int main()
{
    int BeginPoint, EndPoint, PointSum, PointLengthSum;
    
    scanf_s("%d %d %d %d", &BeginPoint, &EndPoint, &PointSum, &PointLengthSum);

    //分配数组内存
    KnownPoint = (int*)malloc(PointSum * sizeof(int));
    UnKnownPoint = (int*)malloc(PointSum * sizeof(int));
    LastRound = (int*)malloc(PointSum * sizeof(int));

    //初始化已经确定的点 为-1
    for (int i = 0; i < PointSum_Max; i++)
    {
        KnownPoint[i] = -1;
    }
    //初始化尚未确定的点 为65535
    for (int i = 0; i < PointSum_Max; i++)
    {
        UnKnownPoint[i] = 65535; 
    }
    //初始化上一次被查找的点 为1
    for (int i = 0; i < PointSum_Max; i++)
    {
        LastRound[i] = 1; 
    }

    UnKnownPoint[BeginPoint - 1] = 0;
    LastRound[BeginPoint - 1] = 0;

    //读取点间距离
    for (int i = 0; i < PointLengthSum; i++)
    {
        int Point1, Point2, Length;
        scanf_s("%d %d %d", &Point1, &Point2, &Length);

        NowNode = NewNode(Point1-1, Point2-1, Length, NowNode);
        if (i == 0) Head = NowNode;
    }


    int MinPoint = 0;//到起点距离最小的节点
    
    //遍历查找最小值
    int ContunueFlag = 1;//是否继续搜索
    while (ContunueFlag)
    {
        MinPoint = FindMin(UnKnownPoint, PointSum);
        KnownPoint[MinPoint] = UnKnownPoint[MinPoint];//确定一个点

        TravelFind(MinPoint);

        ContunueFlag = 0;
        for (int i = 0; i < PointSum; i++)
        {
            if (UnKnownPoint[i] == 65535)
            {
                ContunueFlag = 1;
                break;
            }
        }

        //调试信息
        for (int i = 0; i < PointSum; i++)
        {
            printf("%d ", UnKnownPoint[i]);
        }
        printf("\n");
    }

    for (int i = 0; i < PointSum; i++)
    {
        printf("%d ", UnKnownPoint[i]);
    }
    printf("\n");

    return 0;
}

int FindMin(int* Array, int Sum)
{
    int MinData = 0, Min = 65535;
    for (int i = 0; i < Sum; i++)
    {
        if ((UnKnownPoint[i] < Min)&&(KnownPoint[i] == -1))
        {
            MinData = i;
            Min = UnKnownPoint[i];
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
    if (beforeNode)
    {
        beforeNode->next = nextNode;
    }
    else {
        Head = nextNode;
    }
    if (nextNode) nextNode->before = beforeNode;

    //删除节点释放内存
    free(Node_todelete);

    Node_todelete = nextNode;

    return;
}

int TravelFind(int PointToFind)//寻找相关节点函数
{
    NowNode = Head;//将当前指针移至链表头
    while (NowNode)//开始遍历
    {
        if ((NowNode->point1 == PointToFind)&&(KnownPoint[NowNode->point2] == -1))
        {
            if (UnKnownPoint[PointToFind] + NowNode->length < UnKnownPoint[NowNode->point2])
            {
                UnKnownPoint[NowNode->point2] = UnKnownPoint[PointToFind] + NowNode->length;
            }
            
            PathLength* temporary = NowNode->next;//临时寄存变量
            DeleteNode(NowNode);
            NowNode = temporary;//下一数据
            continue;
        }
        if ((NowNode->point2 == PointToFind) && (KnownPoint[NowNode->point1] == -1))
        {
            if (UnKnownPoint[PointToFind] + NowNode->length < UnKnownPoint[NowNode->point1])
            {
                UnKnownPoint[NowNode->point1] = UnKnownPoint[PointToFind] + NowNode->length;
            }
            
            PathLength* temporary = NowNode->next;//临时寄存变量
            DeleteNode(NowNode);
            NowNode = temporary;//下一数据
            continue;
        }
        NowNode = NowNode->next;//下一数据
    }

    return 0;
}