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
typedef int Pathmatirx[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
void menu(void);
void CreateMGraph(MGraph * G);
int findVex(MGraph G, char vex[]);
void SelectAllNode(MGraph G);
void ShortestPath_Floyd(MGraph G);
void ShortPath(MGraph G);
