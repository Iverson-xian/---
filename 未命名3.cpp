#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define INF 32767
int visited[100],password;  //password为后台管理的登录密码
FILE *fp;
char na[100];
char str1[100],str3[100];
int N,M;
int a[100][100];
using namespace std;
typedef struct
{
    int num;
    char name[100];
    char introduction[100];
} VertexType;
typedef struct
{
    int edges[100][100];
    int n,e;
    VertexType vex[100];
} MGraph;
typedef struct ANode
{
    int adjvex;
    struct ANode *nextarc;
} ArcNode;
typedef struct Vnode
{
    ArcNode *firstarc;
} VNode;
typedef VNode AdjList[100];
typedef struct
{
    AdjList adjlist;
    int n,e;
} ALGraph;
MGraph g;
//将文本文件打开并输出文件中的内容
void ReadData1(MGraph &g)
{
    M=N;
    FILE *fp;
    int i = 0,j;
    if ((fp=fopen("path.txt", "r"))==NULL)
    {
        printf("error open!");
        exit(0);
    }
    for(i=0; i<M; i++)
    {
        for(j=0; j<M; j++)
        {
            fscanf(fp,"%d",&g.edges[i][j]);
        }
    }
    fclose(fp);
}
void WriteData1(MGraph &g)
{
    FILE *fp;
    int i = 0,j;
    if ((fp=fopen("path.txt", "w"))==NULL)
    {
        printf("error open!");
        exit(0);
    }
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            printf("%d ",g.edges[i][j]);
            fprintf(fp,"%d ",g.edges[i][j]);
        }
        printf("\n");
    }
    fclose(fp);
}
void ReadData(MGraph &g)
{
    FILE *fp;
    int i = 0;
    if ((fp=fopen("data.txt", "r"))==NULL)
    {
        printf("error open!");
        exit(0);
    }
    while(fscanf(fp,"%d %s %s",&g.vex[i].num,g.vex[i].name,g.vex[i].introduction)!= EOF)
    {
        i++;
    }
    N = i;
    fclose(fp);
    return;
}
void WriteData(MGraph &g)
{
    FILE *fp;
    int i=0;
    if ((fp=fopen("data.txt", "w"))==NULL)
    {
        printf("error open!");
        exit(0);
    }
    for(i=0; i<N; i++)
        fprintf(fp,"%d %s %s\n",g.vex[i].num,g.vex[i].name,g.vex[i].introduction);
    fclose(fp);
}
//将邻接矩阵改为邻接表
void MatToList(MGraph g,ALGraph *&G)
{
    int i,j;
    ArcNode *p;
    G=(ALGraph *)malloc(sizeof(ALGraph));
    for(i=0; i<g.n; i++)
        G->adjlist[i].firstarc=NULL;
    for(i=0; i<g.n; i++)
        for(j=g.n-1; j>=0; j--)
        {
            if(g.edges[i][j]!=INF)
            {
                p=(ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex=j;
                p->nextarc=G->adjlist[i].firstarc;
                G->adjlist[i].firstarc=p;
            }
        }
    G->n=g.n;
    G->e=g.e;
}
//查找相应景点的介绍
void FindIntroduction(MGraph &g)
{
    int x,d;
    while(1)
    {
        printf("请输入要查询的景点的编号:");
        scanf("%d",&x);
        ReadData(g);
        printf("景点的名称:%s\n",g.vex[x].name);
        printf("景点的简介:");
        printf("%s\n",g.vex[x].introduction);
        printf("是否要继续查询(0.继续  1.不继续):");
        scanf("%d",&d);
        while(1)
        {
            if(d==0||d==1)
                break;
            else
            {
                printf("输入的数据不合理，请重新输入:");
                scanf("%d",&d);
            }
        }
        if(d==0)
            continue;
        else
            break;
    }
}
//输出两个顶点间的最短路径
void Dispath(MGraph &g,int A[][100],int path[][100])
{
    int i,j,k,s,u,v;
    printf("请输入你所在位置的编号:");
    scanf("%d",&u);
    printf("请输入你要去位置的编号:");
    scanf("%d",&v);
    int apath[100],d;
    for(i=0; i<g.n; i++)
    {
        for(j=0; j<g.n; j++)
        {
            if(A[i][j]!=INF&&i!=j&&u==i&&v==j)
            {
                printf("  从%s到%s的最短路径为:",g.vex[i].name,g.vex[j].name);
                k=path[i][j];
                d=0;
                apath[d]=j;
                while(k!=-1&&k!=i)
                {
                    d++;
                    apath[d]=k;
                    k=path[i][k];
                }
                d++;
                apath[d]=i;
                printf("%s",g.vex[apath[d]].name);
                for(s=d-1; s>=0; s--)
                    printf("->%s",g.vex[apath[s]].name);
                printf("\n");
                printf("  路径长度为:%d",A[i][j]);
                printf("\n");
            }
        }
    }
}
//查找两顶点间的最短路径
void FindMinPath(MGraph &g)
{
    int A[100][100],path[100][100];
    int i,j,k;
    for(i=0; i<g.n; i++)
    {
        for(j=0; j<g.n; j++)
        {
            A[i][j]=g.edges[i][j];
            if(i!=j&&g.edges[i][j]<INF)
                path[i][j]=i;
            else
                path[i][j]=-1;
        }
    }
    for(k=0; k<g.n; k++)
    {
        for(i=0; i<g.n; i++)
        {
            for(j=0; j<g.n; j++)
            {
                if(A[i][j]>A[k][j]+A[i][k])
                {
                    A[i][j]=A[k][j]+A[i][k];
                    path[i][j]=path[k][j];
                }
            }
        }
    }
    Dispath(g,A,path);
}
//查找两顶点间的所有路径
void FindaPath(MGraph &g,ALGraph *G,int u,int v,int path[],int d)
{
    int w,i;
    ArcNode *p;
    visited[u]=1;
    d++;
    path[d]=u;
    if(u==v&&d>=1)
    {
        printf(" ");
        for(i=0; i<d; i++)
            printf("%s->",g.vex[path[i]].name);
        printf("%s",g.vex[path[d]].name);
        printf("\n");
    }
    p=G->adjlist[u].firstarc;
    while(p!=NULL)
    {
        w=p->adjvex;
        if(visited[w]==0)
            FindaPath(g,G,w,v,path,d);
        p=p->nextarc;
    }
    visited[u]=0;
}
//删除景点简介信息
void delete_str(char str1[], char str2[],int len,char str3[])
{
    int num=0,k=0,i=0,j=0;   //num用来记录子串的个数 k用来记录子串的位置
    char *p=str2;             //使用p还原str到初始位置
    while(str1[i]!='\0')
    {
        if(str1[i]!=str2[j])
        {
            str3[k++]=str1[i++];  //当str1中的字符与str的首字符不相同时
        }
        else
        {
            char *temp=str2;
            for(; (str1[i]==str2[j])&&str2[j]!='\0'; j++)
            {
                i++;
            }
            if(j==len)
            {
                num++;           //出现重复子串，num加一
            }
            else
            {
                //主字符串中存在和子串前几个字符相同的一段字符
                //退出循环并将这段字符写进新的字符数组中
                for(int m=0; m<j; m++)
                {
                    str3[k++]=temp[m];
                }
            }
            str2=p;
            j=0;
        }
    }
}
//密码输入函数
int inputpassword()
{
    char a[10];
    int pass=0;
    int i;
    while(1)
    {
        for(i=0; i<6; i++)
        {
            a[i]=getch();
            putchar('*');
            if(a[i]>='0'&&a[i]<='9')
                pass=pass*10+a[i]-'0';
            else if(a[i]=='\b')         //当遇到退格键不做处理
            {
                printf("\b \b");
                i--;
            }
            else
            {
                pass=0;
                break;   //退出for循环后，再次接受
            }
        }
        fflush(stdin);  //清除键盘缓存区中已经有的输入
        printf("\n");
        if(pass==0)    //此条件成立可能由两种情况引起：输入了非数字字符被直接重置为0，或6位全0后正常退出for循环
        {
            printf("密码要求全为数字，且不能全0！\n");
            printf("请重新输入密码: ");
        }
        else
            break;
    }
    return pass;
}
//在图中增减一个顶点
void add_point(MGraph &g)
{
    int i,d;
    N++;
    g.vex[N-1].num=N-1;
    printf("%d\n",N);
    printf("请输入要增加景点的名称:");
    scanf("%s",g.vex[N-1].name);
    printf("%s\n",g.vex[N-1].name);
    printf("请输入该景点与其它景点间的路径长度:");
    for(i=0; i<N; i++)
    {
        scanf("%d",&d);
        g.edges[i][N-1]=g.edges[N-1][i]=d;
    }
    printf("请输入要增加顶点的简介:");
    scanf("%s",g.vex[N-1].introduction);
    printf("增加成功!\n");
}
//在图中增加一条路径
void add_path(MGraph &g)
{
    int i,j,length,k;
    do
    {
        printf("请输入要增加路径的起始点的编号:");
        scanf("%d",&i);
        printf("请输入要增加路径的终点的编号:");
        scanf("%d",&j);
        if(i>=0&&i<=N-1&&j>=0&&j<=N-1&&j>=0)
        {
            if(g.edges[i][j]!=INF&&g.edges[j][i]!=INF)
            {
                printf("该两点之间已存在路径,是否进行修改(0.修改 1.不修改):");
                scanf("%d",&k);
                if(k==0)
                {
                    printf("请输入要修改的路径的长度:");
                    scanf("%d",&length);
                    g.edges[j][i]=g.edges[i][j]=length;
                    printf("修改成功!");
                }
                else
                    g.edges[j][i]=g.edges[i][j];
            }
            else
            {
                printf("请输入要增加的路径的长度:");
                scanf("%d",&length);
                g.edges[j][i]=g.edges[i][j]=length;
                printf("添加成功!\n");
            }
            break;
        }
        else
        {
            printf("输入的顶点在原图中不存在!\n");
            continue;
        }
    }
    while(1);
}
//删除图中的一个顶点
void delete_point(MGraph &g)
{
    int i,j,m;
    printf("%d\n",N);
    printf("请输入要删除景点的编号:");
    scanf("%d",&m);
    do
    {
        if(m>=0&&m<=N-1)
            break;
        else
        {
            printf("请输入要删除景点的编号:");
            scanf("%d",&m);
        }
    }
    while(1);
    for(i=0; i<M; i++)
    {
        for(j=0; j<M; j++)
        {
            if(g.edges[m][j]!=INF&&g.edges[i][m]!=INF)
                g.edges[m][j]=g.edges[i][m]=INF;
        }
    }
    g.vex[m].num=INF;
    strcpy(g.vex[m].name,"F");
    printf("删除成功!\n");
}
//删除图中的一条路径
void delete_path(MGraph &g)
{
    int i,j;
    do
    {
        printf("请输入要删除路径的起始点的编号:");
        scanf("%d",&i);
        printf("请输入要删除路径的终点的编号:");
        scanf("%d",&j);
        if(g.edges[i][j]==INF)
            printf("这两点间不存在路径!\n");
        else
        {
            g.edges[i][j]=g.edges[j][i]=INF;
            break;
        }
    }
    while(1);
    printf("删除成功!\n");
}
//整个程序的驱动
void function()
{
    ALGraph *G;
    int i,j,u,v,path[100],x,k,l,d,y;
    int ch,pass;
    char str2[500],nam[100];
    g.n=10;
    g.e=18;
    ReadData(g);
    ReadData1(g);
    MatToList(g,G);
    for(i=0; i<G->n; i++)
        visited[i]=0;
    system("color F0");
    printf("\t\t     *******************************\n");
    printf("\t\t     *       1.用户                *\n");
    printf("\t\t     *       2.管理人员            *\n");
    printf("\t\t     *******************************\n");
    printf("请选择相应的编号进行下一步操作:");
    scanf("%d",&k);
    do
    {
        if(k==1||k==2)
            break;
        else
        {
            printf("输入数据不合理,请重新输入:");
            scanf("%d",&k);
        }
    }
    while(1);
    if(k==1)
    {
        system("title 校园景点介绍及路径查询系统");
        system("color F0");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t欢迎进入校园景点介绍及路径查询系统!\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("正在进入,请稍后...\n");
        printf("===============================================================================\r");
        for(j=0; j<80; j++)
        {
            Sleep(50);
            printf(">");
        }
        system("cls");
        do
        {
            printf("\t\t     *******************************\n");
            printf("\t\t     *       1.景点简介            *\n");
            printf("\t\t     *       2.两景点间最短路径    *\n");
            printf("\t\t     *       3.两景点间所有路径    *\n");
            printf("\t\t     *       4.退出系统            *\n");
            printf("\t\t     *******************************\n");
            printf("请输入要进行的操作的编号:");
            scanf("%d",&x);
            do
            {
                if(x>=1&&x<=4)
                    break;
                else
                {
                    printf("输入数据不合理,请重新输入:");
                    scanf("%d",&x);
                }
            }
            while(1);
            if(x>=1&&x<=3)
            {
                printf("\t\t     *******************************\n");
                if(N%2!=0)
                {
                    for(i=0; i<N-1; i+=2)
                    {
                         printf("\t\t          %d.%s  \t%d.%s  \n",g.vex[i].num,g.vex[i].name,g.vex[i+1].num,g.vex[i+1].name);
                    }
                     printf("\t\t          %d.%s       \n",g.vex[i].num,g.vex[i+1].name);

                }
                else
                {
                    for(i=0; i<N; i+=2)
                    {
                         printf("\t\t          %d.%s  \t%d.%s  \n",g.vex[i].num,g.vex[i].name,g.vex[i+1].num,g.vex[i+1].name);
                    }
                }

                printf("\t\t     *******************************\n");
            }
            switch(x)
            {
            case 1:
                ReadData(g);
                FindIntroduction(g);
                system("cls");
                break;
            case 2:
                ReadData(g);
                do
                {
                    FindMinPath(g);
                    printf("是否继续进行该操作(0.继续 1.不继续):");
                    scanf("%d",&y);
                    if(y==1)
                        break;
                    else
                        continue;
                }
                while(1);
                system("pause");
                system("cls");
                break;
            case 3:
                ReadData(g);
                do
                {
                    printf("请输入起点位置的编号:");
                    scanf("%d",&u);
                    printf("请输入终点位置的编号:");
                    scanf("%d",&v);
                    printf("从%s到%s的所有路径为:\n",g.vex[u].name,g.vex[v].name);
                    FindaPath(g,G,u,v,path,-1);
                    printf("是否继续进行该操作(0.继续 1.不继续):");
                    scanf("%d",&y);
                    if(y==1)
                        break;
                    else
                        continue;
                }
                while(1);
                system("pause");
                system("cls");
                break;
            case 4:
                printf("确认退出吗?(0.退出 1.不退出):");
                scanf("%d",&ch);
                while(1)
                {
                    if(ch==0||ch==1)
                        break;
                    else
                    {
                        printf("输入的数据不合理，请重新输入:");
                        scanf("%d",&ch);
                    }
                }
                if(ch==0)
                {
                    x=0;
                    printf("谢谢使用本系统，欢迎下次光临!");
                }
                else
                {
                    continue;
                }
            }
        }
        while(x!=0);
    }
    else
    {
        printf("请输入管理代号:");
        scanf("%s",na);
        printf("请输入管理登录密码:");
        password=inputpassword();
        FILE *fp1;
        if((fp1=fopen("password.txt","r"))==NULL)
        {
            printf("Cannot open the file!");
            exit(0);
        }
        fscanf(fp1,"%s %d",nam,&pass);
        fclose(fp1);
        int t=3;
        do
        {
            if(password!=pass)
            {
                t--;
                if(t==0)
                {
                    printf("你已经输错三次密码,系统将于10秒后关闭!");
                    Sleep(10000);
                    break;
                }
                printf("输入的密码错误!你还有%d次机会,请重新输入:",t);
                password=inputpassword();
            }
            else
                break;
        }
        while(t!=0);
        system("cls");
        if(password==pass&&strcmp(nam,na)==0)
        {
            do
            {
                printf("\t\t     *******************************\n");
                printf("\t\t     *     1.增加景点简介信息      *\n");
                printf("\t\t     *     2.删除景点简介信息      *\n");
                printf("\t\t     *     3.更新景点简介信息      *\n");
                printf("\t\t     *     4.增加景点              *\n");
                printf("\t\t     *     5.增加路径              *\n");
                printf("\t\t     *     6.删除景点              *\n");
                printf("\t\t     *     7.删除路径              *\n");
                printf("\t\t     *     8.退出系统              *\n");
                printf("\t\t     *******************************\n");
                printf("请选择要进行的操作:");
                scanf("%d",&l);
                printf("\t\t     *******************************\n");
                if(N%2!=0)
                {
                    for(i=0; i<N-1; i+=2)
                    {
                         printf("\t\t          %d.%s  \t%d.%s  \n",g.vex[i].num,g.vex[i].name,g.vex[i+1].num,g.vex[i+1].name);
                    }
                     printf("\t\t          %d.%s       \n",g.vex[i].num,g.vex[i+1].name);

                }
                else
                {
                    for(i=0; i<N; i+=2)
                    {
                         printf("\t\t          %d.%s  \t%d.%s  \n",g.vex[i].num,g.vex[i].name,g.vex[i+1].num,g.vex[i+1].name);
                    }
                }

                printf("\t\t     *******************************\n");
                if(l==1)
                {
                    do
                    {
                        printf("请输入要要增加信息的景点的编号:");
                        scanf("%d",&d);
                        ReadData(g);
                        printf("%s\n",g.vex[d].introduction);
                        printf("请输入要增加的信息:");
                        scanf("%s",str2);
                        strcat(g.vex[d].introduction,str2);
                        printf("增加成功!\n");
                        WriteData(g);
                        printf("是否继续进行该操作(0.继续 1.不继续):");
                        scanf("%d",&y);
                        if(y==1)
                            break;
                        else
                            continue;
                    }
                    while(1);
                    system("cls");
                }
                if(l==2)
                {
                    do
                    {
                        printf("请输入要删除信息的景点的编号:");
                        scanf("%d",&d);
                        ReadData(g);
                        strcpy(str1,g.vex[d].introduction);
                        printf("%s\n",str1);
                        printf("请输入要删除的信息:");
                        scanf("%s",str2);
                        printf("%d\n",N);
                        delete_str(str1,str2,strlen(str2),str3);
                        printf("%s\n",str3);
                        strcpy(g.vex[d].introduction,str3);
                        printf("%s\n",g.vex[d].introduction);
                        WriteData(g);
                        printf("删除成功!\n");
                        printf("是否继续进行该操作(0.继续 1.不继续):");
                        scanf("%d",&y);
                        if(y==1)
                            break;
                        else
                            continue;
                    }
                    while(1);
                    system("cls");
                }
                if(l==3)
                {
                    do
                    {
                        printf("请输入要更新信息的景点的编号:");
                        scanf("%d",&d);
                        ReadData(g);
                        printf("请输入要更新的信息:");
                        scanf("%s",str2);
                        strcpy(g.vex[d].introduction,str2);
                        WriteData(g);
                        printf("是否继续进行该操作(0.继续 1.不继续):");
                        scanf("%d",&y);
                        if(y==1)
                            break;
                        else
                            continue;
                    }
                    while(1);
                    system("cls");
                }
                if(l==4)
                {
                    ReadData(g);
                    ReadData1(g);
                    for(i=0; i<N; i++)
                    {
                        for(j=0; j<N; j++)
                        {
                            printf("%d ",g.edges[i][j]);
                        }
                        printf("\n");
                    }
                    add_point(g);
                    WriteData1(g);
                    WriteData(g);
                }
                if(l==5)
                {
                    ReadData1(g);
                    for(i=0; i<M; i++)
                    {
                        for(j=0; j<M; j++)
                        {
                            printf("%d ",g.edges[i][j]);
                        }
                        printf("\n");
                    }
                    add_path(g);
                    WriteData1(g);
                }
                if(l==6)
                {
                    ReadData(g);
                    ReadData1(g);
                    for(i=0; i<M; i++)
                    {
                        for(j=0; j<M; j++)
                        {
                            printf("%d ",g.edges[i][j]);
                        }
                        printf("\n");
                    }
                    delete_point(g);
                    WriteData1(g);
                    WriteData(g);
                }
                if(l==7)
                {
                    ReadData1(g);
                    for(i=0; i<M; i++)
                    {
                        for(j=0; j<M; j++)
                        {
                            printf("%d ",g.edges[i][j]);
                        }
                        printf("\n");
                    }
                    delete_path(g);
                    WriteData1(g);
                }
                if(l==8)
                {
                    printf("确认退出吗?(0.退出 1.不退出):");
                    scanf("%d",&ch);
                    while(1)
                    {
                        if(ch==0||ch==1)
                            break;
                        else
                        {
                            printf("输入的数据不合理，请重新输入:");
                            scanf("%d",&ch);
                        }
                    }
                    if(ch==0)
                    {
                        x=0;
                        printf("正在退出....");
                        Sleep(5000);
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            while(1);
        }
    }
}
int main()
{
    function();
    return 0;
}


