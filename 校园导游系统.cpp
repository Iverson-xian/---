#include "graph.h"




int main(void) {
    int x;
    MGraph G;
    CreateMGraph(&G);
    ShortestPath_Floyd(G);
    do {
    	menu();
        printf("��ѡ��(0~9)��");
        scanf("%d", &x);
        while (x > 9 || x < 0) {
            printf("��������Ч��ѡ�");
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


