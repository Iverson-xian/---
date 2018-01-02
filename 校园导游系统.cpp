#include "graph.h"




int main(void) {
    int x;
    MGraph G;
    CreateMGraph(&G);
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
        				break;
        		case 2: ShortPath(G);
			}
		}
    } while (x != 0);

    return 0;
}


