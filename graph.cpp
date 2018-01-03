#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
Pathmatirx P;
ShortPathTable D;
int visited[MAXVEX];
void menu(void) {
    printf("1. 查询所有节点名称及编号\n");
    printf("2. 增加节点\n");
    printf("3. 增加线路\n");
    printf("4. 删除节点\n");
    printf("5. 删除线路\n");
    printf("6. 查询两个节点之间的最短简单路径\n");
    printf("7. 查询任意两个地点之间的最佳访问线路\n");
    printf("8. 查询两个地点之间的所有简单路径\n");
    printf("0. 退出\n\n");
}

void CreateMGraph(MGraph * G) {
    int i, j, x, y, w;
    char vex1[100], vex2[100];
    FILE * fp;
    if ((fp = fopen("校园导游系统.txt", "r")) == NULL) {
        printf("文件打开失败！");
    }
    fscanf(fp, "%d %d", &G->numVertexs, &G->numEdges);
    for (i = 0; i < G->numVertexs; i++) {
        fscanf(fp, "%d %s %s", &G->vex[i].No, G->vex[i].name, G->vex[i].introducation);
    }
    // 初始化
	for (i = 0; i < G->numVertexs; i++) {
        for (j = 0; j < G->numVertexs; j++)
            G->arc[i][j]  =INFINITY;
        G->arc[i][i] = 0;
    }
    for (i = 0; i < G->numEdges; i++) {
        fscanf(fp, "%s %s %d", vex1, vex2, &w);
        x = findVex(*G, vex1);
        y = findVex(*G, vex2);
        G->arc[x][y] = w;
		G->arc[y][x] = w;
    }
}

int findVex(MGraph G, char vex[]) {
    int i;
    for (i = 0; i < G.numVertexs; i++) {
        if (strcmp(G.vex[i].name, vex) == 0) {
            return i;
        }
    }
    return -1;
}

void SelectAllNode(MGraph G) {
    int i;
    for (i = 0; i < G.numVertexs; i++) {
        printf("编号:%d, 名称:%s, 介绍:%s\n", G.vex[i].No, G.vex[i].name, G.vex[i].introducation);
    }
}

void ShortestPath_Floyd(MGraph G) {
	int v, w, k;
	for (v = 0; v < G.numVertexs; ++v) {
		for (w = 0; w < G.numVertexs; ++w) {
			D[v][w] = G.arc[v][w];
            P[v][w] = w;
		}
	}
    for (k = 0; k < G.numVertexs; k++) {
        for (v = 0; v < G.numVertexs; v++) {
            for (w = 0; w < G.numVertexs; w++) {
                if  (D[v][w] > D[v][k] + D[k][w]) {
                    D[v][w] = D[v][k] + D[k][w];
                    P[v][w] = P[v][k];
                }
            }
        }
    }
}

void InputTwoNode(int * start, int * end, MGraph G) {
    int i;
    *start = 0;
    *end = 0;
    char vex1[100], vex2[100];
    printf("请输入起始节点的编号或名称: ");
    while (1) {
        scanf("%s", vex1);
        if (strlen(vex1) <= 2) {
            *start = 0;
            for (i = 0; i < strlen(vex1); i++) {
                *start *= 10;
                *start += vex1[i] - '0';
            }
            (*start)--; 
        } else
            *start = findVex(G, vex1);
        if (*start < 0 || *start >= G.numVertexs) {
            printf("输入有误，请重新输入：");
            continue;
        } else
            break;
    }
    printf("请输入终止节点的编号或者名称：");
    while (1) {
        scanf("%s", vex2);
        if (strlen(vex2) <= 2) {
            *end = 0;
            for (i = 0; i < strlen(vex2); i++) {
                (*end) *= 10;
                *end += vex2[i] - '0';
            }
            (*end)--;
        } else
            *end = findVex(G, vex2);
        if (*end < 0 || *end >= G.numVertexs) {
            printf("输入有误，请重新输入：");
            continue;
        } else
            break;
    }
}

void ShortPath(MGraph G) {
    int i, j, k;
    int start = 0, end = 0;
    InputTwoNode(&start, &end, G);
    // printf("%d %d\n", start, end);
    printf("%s-->%s 距离：%d\n", G.vex[start].name, G.vex[end].name, D[start][end]);
    k = P[start][end];
    printf("最短路径：%s", G.vex[start].name);
    while (k != end) {
        printf("-->%s", G.vex[k].name);
        k = P[k][end];
    }
    printf("->%s\n", G.vex[end].name);
}
void MiniSpanTree(MGraph G) {
    int min, i, j, k;
    int adjvex[MAXVEX];     // 保存相关顶点的下标
    int lowcost[MAXVEX];    // 保存相关顶点边的权值
    lowcost[0] = 0;     // 初始化第一个权值为0，即v0加入生成树
    adjvex[0] = 0;
    for (i = 1; i < G.numVertexs; i++) {
        lowcost[i] = G.arc[0][i];
        adjvex[i] = 0;
    }
    for (i = 1; i < G.numVertexs; i++) {
        min = INFINITY;
        j = 1;
        k = 0;
        while (j < G.numEdges) {
            if (lowcost[j] != 0 && lowcost[j] < min) {
                min =lowcost[j];
                k = j;
            }
            j++;
        }
        printf("(%d %d)", adjvex[k], k);
        lowcost[k] = 0;
        for (j = 1; j < G.numVertexs; j++) {
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j]) {
                lowcost[j] = G.arc[k][j];
                adjvex[j] = k;
            }
        }
    }
    printf("\n");
}

void MapToList(MGraph G, GraphAdjList * LG) {
    int i, j;
    EdgeNode * p;
    LG->numVertexs = G.numVertexs;
    LG->numEdges = G.numEdges;
    for (i = 0; i < G.numVertexs; i++) {
        LG->AdjList[i].data = G.vex[i];
    }
    for (i = 0; i < G.numVertexs; i++) {
        for (j = G.numVertexs - 1; j >= 0; j--) {
            if (G.arc[i][j] != INFINITY && G.arc[i][j] != 0) {
                p = (EdgeNode *) malloc(sizeof(EdgeNode));
                p->adjvex = j;
                p->weight = G.arc[i][j];
                p->next = LG->AdjList[i].firstedge;
                LG->AdjList[i].firstedge = p;
            }
        }
    }
}

void FindAllPath(GraphAdjList LG, int start, int end, int path[], int d) {
//	printf("%d\n", start);
    int w, i;
    EdgeNode * p;
    visited[start] = 1;
    d++;
    path[d] = start;
    if (start == end && d >= 1) {
        printf("   ");
        for (i = 0; i < d; i++) {
            printf("%s->", LG.AdjList[path[i]].data.name);
        }
        printf("%s", LG.AdjList[path[d]].data.name);
        printf("\n");
    }
    p = LG.AdjList[start].firstedge;
    while (p != NULL) {
        w = p->adjvex;
//        printf("%daaaa%d\n",visited[w], w);
        if (visited[w] == 0) {
            FindAllPath(LG, w, end, path, d);
        }
        p = p->next;
    }
    visited[start] = 0;
}

void TwoNodeAllPath(MGraph G) {
    GraphAdjList LG;
    int i, start, end;
    MapToList(G, &LG);
    for (i = 0; i < G.numVertexs; i++) {
        printf("%s ", LG.AdjList[i].data.name);
        EdgeNode * p = LG.AdjList[i].firstedge;
        while (p != NULL) {
            printf("%d %d\t", p->adjvex, p->weight);
            p = p->next;
        }
        printf("\n");
    }
    for (i = 0; i < MAXVEX; i++)
        visited[i] = 0;
    InputTwoNode(&start, &end, G);
    int path[MAXVEX] = {0};
    FindAllPath(LG, start, end , path, -1);
}

