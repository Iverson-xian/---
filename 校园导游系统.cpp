#include <stdio.h>
#include "graph.h"
int main(void) {
    int x;
    MGraph G;
    GraphAdjList LG;
    CreateMGraph(&G);
    MapToList(G, &LG);
    ShortestPath_Floyd(G);
    do {
    	menu();
        printf("请选择(0~9)：");
        scanf("%d", &x);
        while (x > 9 || x < 0) {
            printf("请输入有效的选项：");
            scanf("%d", &x);
        }
        if (x != 0) {
        	switch (x) {
        		case 1: SelectAllNode(G);
        			getchar();
        			break;
        		case 2:
                        MiniSpanTree(G);
                        break;
                case 6:
                        TowNodeMinNode(LG, G);
                        break;
        		case 7: ShortPath(G);
        			getchar();
        			break;
                case 8: TwoNodeAllPath(LG, G);
                        break;
	        }
	}
    } while (x != 0);

    return 0;
}

