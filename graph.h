#include <stdio.h>
#define MAXVEX 100
#define INFINITY 65535
// 邻接矩阵的定义
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

// 邻接表的定义
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


void menu(void);
void CreateMGraph(MGraph * G);
int findVex(MGraph G, char vex[]);
void SelectAllNode(MGraph G);
void ShortestPath_Floyd(MGraph G);
void ShortPath(MGraph G);
void MiniSpanTree(MGraph G);
void MapToList(MGraph G, GraphAdjList * LG);
void TwoNodeAllPath(MGraph G);
void FindAllPath(MGraph G, GraphAdjList LG, int start, int end, int path[], int d);
void InputTwoNode(int * start, int * end, MGraph G)
