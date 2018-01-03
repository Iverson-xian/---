#include <stdio.h>
#define MAXVEX 100
#define INFINITY 65535

typedef struct {
    int No;
    char name[100];
    char introducation[1000];
} VerType;

typedef int EdgeType;
typedef struct {
	VerType vex[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexs, numEdges;
}MGraph;


typedef struct EdgeNode {
    int adjvex;
    EdgeType weight;
    struct EdgeNode * next;
} EdgeNode;

typedef struct VertexNode {
    VerType data;
    EdgeNode * firstedge;
} VertexNode, AdjList[MAXVEX];
typedef struct {
    AdjList AdjList;
    int numVertexs, numEdges;
} GraphAdjList;

typedef int Pathmatirx[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

// 队列的定义
typedef int QElemenType;
typedef struct QNode {
    QElemenType data;
    struct QNode * next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front, rear;
} LinkQueue;

void menu(void);
void CreateMGraph(MGraph * G);
int findVex(MGraph G, char vex[]);
void SelectAllNode(MGraph G);
void ShortestPath_Floyd(MGraph G);
void ShortPath(MGraph G);
void MiniSpanTree(MGraph G);
void MapToList(MGraph G, GraphAdjList * LG);
void TwoNodeAllPath(GraphAdjList LG, MGraph G);
void FindAllPath(GraphAdjList LG, int start, int end, int path[], int d);
void InputTwoNode(int * start, int * end, MGraph G);
int InitQueue(LinkQueue * Q);
int QueueEmpty(LinkQueue Q);
int DeQueue(LinkQueue * Q, QElemenType * e);
int EnQueue(LinkQueue * Q, QElemenType e);
void findMinNode(GraphAdjList LG, int start, int end, int path[], int d);
void TowNodeMinNode(GraphAdjList LG ,MGraph G);

