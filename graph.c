#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

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
			
		}
	}
}

