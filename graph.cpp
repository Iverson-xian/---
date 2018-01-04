#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
Pathmatirx P;
ShortPathTable D;
int minpath[MAXVEX];
int pathLength;
int visited[MAXVEX];
void menu(void) {
    printf("1. 查询所有节点名称及编号\n");
    printf("2. 最佳布网方案（最小生成树）\n");
    printf("3. 查询两个节点之间的最短简单路径\n");
    printf("4. 查询任意两个地点之间的最佳访问线路\n");
    printf("5. 查询两个地点之间的所有简单路径\n");
    printf("6. 管理\n");
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
    fclose(fp);
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
        while (j < G.numVertexs) {
            if (lowcost[j] != 0 && lowcost[j] < min) {
                min =lowcost[j];
                k = j;
            }
            j++;
        }
        printf("(%s, %s, %d)", G.vex[adjvex[k]].name, G.vex[k].name, G.arc[adjvex[k]][k]);
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
	// printf("%d\n", start);
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
        visited[start] = 0;
        return;
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

void TwoNodeAllPath(GraphAdjList LG, MGraph G){
    int i, j, start, end, count = 0;
    for (i = 0; i < MAXVEX; i++)
        visited[i] = 0;
    InputTwoNode(&start, &end, G);
    printf("%d %d\n", start, end);
    int path[MAXVEX] = {0};
    FindAllPath(LG, start, end, path, -1);
}

void findMinNode(GraphAdjList LG, int start, int end, int path[], int d) {
    int w, i;
    EdgeNode * p;
    visited[start] = 1;
    d++;
    path[d] = start;
    if (start == end && d >= 1) {
        // for (i = 0; i < d; i++) {
        //     printf("%s->", LG.AdjList[path[i]].data.name);
        // }
        // printf("%s", LG.AdjList[path[d]].data.name);
        // printf("\n");
        if (d < pathLength) {
            pathLength = d;
            for (i = 0; i < d; i++) {
                minpath[i] = path[i];
            }
        }
        visited[start] = 0;
        return;
    }
    p = LG.AdjList[start].firstedge;
    while (p != NULL) {
        w = p->adjvex;
//        printf("%daaaa%d\n",visited[w], w);
        if (visited[w] == 0) {
            findMinNode(LG, w, end, path, d);
        }
        p = p->next;
    }
    visited[start] = 0;
}
void TowNodeMinNode(GraphAdjList LG ,MGraph G) {
    int i, j, start, end;
    for (i = 0; i < MAXVEX; i++) {
        visited[i] = 0;
        minpath[i] = 0;
    }
    InputTwoNode(&start, &end, G);
    // printf("%d %d\n", start, end);
    pathLength = INFINITY;
    int path[MAXVEX] = {0};
    findMinNode(LG, start, end, path, -1);
    // printf("%d\n", pathLength);
    for (i = 0; i < pathLength; i++) {
        printf("%s-->", G.vex[minpath[i]].name);
    }
    printf("%s\n", G.vex[end].name);
}

// 队列的操作
int EnQueue(LinkQueue *Q, QElemenType  e) {
    QueuePtr s = (QueuePtr) malloc(sizeof(QNode));
    if (s == NULL) {
        exit(1);
    }
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
    if (Q->front->next != NULL)
        printf("bb\n");
    return 1;
}

int DeQueue(LinkQueue *Q, QElemenType * e) {
    QueuePtr p;
    if (Q->front == Q->rear)
        return 0;
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p) {
        Q->rear = Q->front;
    }
    
    free(p);
    return 1;
}



int InitQueue(LinkQueue * Q)
{
    //构造一个空的对列Q
    Q->front = (QueuePtr)malloc(sizeof(QNode));
    //Q.front = Q.rear;
    if(!Q->front)
        exit(1);
    Q->front->next = NULL;
    Q->rear = Q->front;
    return 1;
}

int QueueEmpty(LinkQueue Q) {
    if(Q.front->next == NULL)
        return 1;
    else
        return 0;
}

void Manager(GraphAdjList * LG, MGraph * G) {
    FILE * fp;
    int count = 1, x;
    char password[100];
    char input_pass[100];
    if ((fp = fopen("password.txt", "r")) == NULL) {
        printf("文件无法打开，授权错误!\n");
        return;
    }
    fscanf(fp, "%s", password);
    printf("请输入密码：");
    scanf("%s", input_pass);
    if (strcmp(password, input_pass) == 0) {
        printf("授权成功！\n");
    } else {
        while (count <= 3) {
            printf("密码错误，请重新出入(3次机会):");
            scanf("%s", input_pass);
            if (strcmp(password, input_pass) == 0) {
                printf("授权成功！\n");
                break;
            } else {
                printf("第%d次错误!\n", count);
                count++;
            }
            if (count > 3) {
                printf("您输入的密码错误超过3次，将自动退出管理!\n");
            }
        }
    }
    do{
        Manager_menu();
        printf("请选择：");
        scanf("%d", &x);
        while (x < 0 || x > 6) {
            printf("请输入有效的选项：");
            scanf("%d", &x);
        }
        switch(x) { 
            case 5:updateNode(LG, G);
                    break;
            case 1:addNode(LG, G);
                    break;
            case 2:deleteNode(LG, G);
                    break;
            case 3:updateEdge(LG, G);
                    break;
            case 4:deleteEdge(LG, G);
                    break;
        }
    } while (x != 0);
}

void Manager_menu() {
    printf("1. 添加节点\n");
    printf("2. 删除节点\n");
    printf("3. 添加或更新线路线路\n");
    printf("4. 删除线路\n");
    printf("5. 更新节点信息\n");
    printf("0. 退出\n\n");
}

void updateNode(GraphAdjList * LG, MGraph * G) {
    int target, i, x;
    char vex[100];
    printf("请输入需要更改的节点的名称或者编号:");
    while (1) {
        scanf("%s", vex);
        if (strlen(vex) <= 2) {
            target = 0;
            for (i = 0; i < strlen(vex); i++) {
                target *= 10;
                target += vex[i] - '0';
            }
            target--; 
        } else
            target = findVex(*G, vex);
        if (target < 0 || target >= G->numVertexs) {
            printf("输入有误，请重新输入：");
            continue;
        } else
            break;
    }
    printf("1. 名称\n2. 介绍\n0. 退出\n");
    printf("请选择你需要更改的名称或者介绍：");
    scanf("%d", &x);
    while (x > 2 || x < 0) {
        printf("请输入有效的选项：");
        scanf("%d", &x);
    }
    if (x == 0)
        return;
    else if (x == 1) {
        printf("请输入新的节点名称:");
        scanf("%s", G->vex[target].name);
    } else if (x == 2) {
        printf("请输入新的节点介绍:");
        scanf("%s", G->vex[target].introducation);
    }
    LG->AdjList[target].data = G->vex[target];
    WriteToFile(*G);
}

void WriteToFile(MGraph G) {
    FILE * fp;
    int i, j;
    if ((fp = fopen("校园导游系统.txt", "w+")) == NULL) {
        printf("文件打开失败!");
        exit(1);
    }
    fprintf(fp, "%d %d\n", G.numVertexs, G.numEdges);
    for (i = 0; i < G.numVertexs; i++) {
        fprintf(fp, "%d %s %s\n", G.vex[i].No, G.vex[i].name, G.vex[i].introducation);
    }
    for (i = 0; i < G.numVertexs; i++) {
        for (j = 0; j <= i; j++) {
            if (G.arc[i][j] == INFINITY || G.arc[i][j] == 0)
                continue;
            fprintf(fp, "%s %s %d\n", G.vex[i].name, G.vex[j].name, G.arc[i][j]);

        }
    }
    fclose(fp);
}

void addNode (GraphAdjList * LG, MGraph * G) {
    VerType vex;
    printf("请输入要添加的节点名称：");
    scanf("%s", vex.name);
    printf("请输入节点的介绍：");
    scanf("%s", vex.introducation);
    vex.No = G->numVertexs + 1;
    // G->numVertexs += 1;
    // printf("%d\n", G->numVertexs);
    // G->vex[G->numVertexs ].No = vex.No;
    // strcpy(G->vex[G->numVertexs].name, vex.name);
    // strcpy(G->vex[G->numVertexs].introducation, vex.introducation);
    // G->vex[G->numVertexs].introducation = vex.introducation;
    // SelectAllNode(*G);
    G->vex[G->numVertexs] = vex;
    G->numVertexs++;
    WriteToFile(*G);
    CreateMGraph(G);
    destoryGraphAdjList(LG);
    MapToList(*G, LG);

}

void destoryGraphAdjList(GraphAdjList * LG) {
    int i;
    EdgeNode * p, *q;
    for (i = 0; i < LG->numVertexs; i++) {
        p = LG->AdjList[i].firstedge;
        while (p != NULL) {
            q = p;
            p = q->next;
            free(q);
        }
        LG->AdjList[i].firstedge = NULL;
    }
}

void updateEdge(GraphAdjList * LG, MGraph * G) {
    int start, end, w;
    InputTwoNode(&start, &end, *G);
    printf("请输入新的权值：");
    scanf("%d", &w);
    G->arc[start][end] = w;
    G->arc[end][start] = w;
    WriteToFile(*G);
    destoryGraphAdjList(LG);
    MapToList(*G, LG);
}

void deleteNode(GraphAdjList * LG, MGraph * G) {
    
    int target, i;
    char vex[100];
    printf("请输入需要删除的节点的名称或者编号:");
    while (1) {
        scanf("%s", vex);
        if (strlen(vex) <= 2) {
            target = 0;
            for (i = 0; i < strlen(vex); i++) {
                target *= 10;
                target += vex[i] - '0';
            }
            target--; 
        } else
            target = findVex(*G, vex);
        if (target < 0 || target >= G->numVertexs) {
            printf("输入有误，请重新输入：");
            continue;
        } else
            break;
    }
    for (i = 0; i < G->numVertexs; i++) {
        if (G->arc[target][i] != INFINITY && G->arc[target][i] != 0) {
            G->arc[target][i] = INFINITY;
            G->arc[i][target] = INFINITY;
        }
    }
    for (i = target; i < G->numVertexs - 1; i++) {
        G->vex[i] = G->vex[i+1];
        G->vex[i].No = i + 1;
        G->numVertexs--;
    }
    WriteToFile(*G);
    CreateMGraph(G);
    destoryGraphAdjList(LG);
    MapToList(*G, LG);
}

void deleteEdge(GraphAdjList * LG, MGraph * G) {
    int start, end, w;
    InputTwoNode(&start, &end, *G);
    if (start != end)
    G->arc[start][end] = INFINITY;
    G->arc[end][start] = INFINITY;
    WriteToFile(*G);
    destoryGraphAdjList(LG);
    MapToList(*G, LG);
}