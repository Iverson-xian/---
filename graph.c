#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
Pathmatirx P;
ShortPathTable D;
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
        for (k = 0; k < G.numVertexs; i++) {
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
}

void ShortPath(MGraph G) {
    int i, j, k;
    int start = 0, end = 0;
    char vex1[100], vex2[100];
    printf("请输入起始节点的编号或名称");
    while (1) {
        scanf("%s", vex1);
        if (strlen(vex1)) {
            start = 0;
            for (i = 0; i < strlen(vex1); i++) {
                start *= 10;
                start += vex1[i] - '0';
            }
        } else
            start = findVex(G, vex1);
        if (start < 1 || start >= G.numVertexs) {
            printf("输入有误，请重新输入：");
            continue;
        } else
            break;
    }
    printf("请输入终止节点的编号或者名称：");
    while (1) {
        scanf("%s", vex2);
        if (strlen(vex2)) {
            end = 0;
            for (i = 0; i < strlen(vex2); i++) {
                end *= 10;
                end += vex2[i] - '0';
            }
        } else
            end = findVex(G, vex2);
        if (end < 1 || end >= G.numVertexs) {
            printf("输入有误，请重新输入：");
            continue;
        } else
            break;
    }
    printf("%s-->%s 距离：%d\n", G.vex[start].name, G.vex[i].name, D[start][end]);
    k = P[start][end];
    printf("最短路径：%s", G.vex[start].name);
    while (k != end) {
        printf("-->%s", G.vex[k].name);
        k = P[k][end];
    }
    printf("->%s\n", G.vex[end].name);
}
