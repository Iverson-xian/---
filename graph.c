#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
Pathmatirx P;
ShortPathTable D;
void menu(void) {
    printf("1. ��ѯ���нڵ����Ƽ����\n");
    printf("2. ���ӽڵ�\n");
    printf("3. ������·\n");
    printf("4. ɾ���ڵ�\n");
    printf("5. ɾ����·\n");
    printf("6. ��ѯ�����ڵ�֮�����̼�·��\n");
    printf("7. ��ѯ���������ص�֮�����ѷ�����·\n");
    printf("8. ��ѯ�����ص�֮������м�·��\n");
    printf("0. �˳�\n\n");
}

void CreateMGraph(MGraph * G) {
    int i, j, x, y, w;
    char vex1[100], vex2[100];
    FILE * fp;
    if ((fp = fopen("У԰����ϵͳ.txt", "r")) == NULL) {
        printf("�ļ���ʧ�ܣ�");
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
        printf("���:%d, ����:%s, ����:%s\n", G.vex[i].No, G.vex[i].name, G.vex[i].introducation);
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
    printf("��������ʼ�ڵ�ı�Ż�����");
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
            printf("�����������������룺");
            continue;
        } else
            break;
    }
    printf("��������ֹ�ڵ�ı�Ż������ƣ�");
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
            printf("�����������������룺");
            continue;
        } else
            break;
    }
    printf("%s-->%s ���룺%d\n", G.vex[start].name, G.vex[i].name, D[start][end]);
    k = P[start][end];
    printf("���·����%s", G.vex[start].name);
    while (k != end) {
        printf("-->%s", G.vex[k].name);
        k = P[k][end];
    }
    printf("->%s\n", G.vex[end].name);
}
