#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define INF 32767
int visited[100],password;  //passwordΪ��̨����ĵ�¼����
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
//���ı��ļ��򿪲�����ļ��е�����
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
//���ڽӾ����Ϊ�ڽӱ�
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
//������Ӧ����Ľ���
void FindIntroduction(MGraph &g)
{
    int x,d;
    while(1)
    {
        printf("������Ҫ��ѯ�ľ���ı��:");
        scanf("%d",&x);
        ReadData(g);
        printf("���������:%s\n",g.vex[x].name);
        printf("����ļ��:");
        printf("%s\n",g.vex[x].introduction);
        printf("�Ƿ�Ҫ������ѯ(0.����  1.������):");
        scanf("%d",&d);
        while(1)
        {
            if(d==0||d==1)
                break;
            else
            {
                printf("��������ݲ���������������:");
                scanf("%d",&d);
            }
        }
        if(d==0)
            continue;
        else
            break;
    }
}
//����������������·��
void Dispath(MGraph &g,int A[][100],int path[][100])
{
    int i,j,k,s,u,v;
    printf("������������λ�õı��:");
    scanf("%d",&u);
    printf("��������Ҫȥλ�õı��:");
    scanf("%d",&v);
    int apath[100],d;
    for(i=0; i<g.n; i++)
    {
        for(j=0; j<g.n; j++)
        {
            if(A[i][j]!=INF&&i!=j&&u==i&&v==j)
            {
                printf("  ��%s��%s�����·��Ϊ:",g.vex[i].name,g.vex[j].name);
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
                printf("  ·������Ϊ:%d",A[i][j]);
                printf("\n");
            }
        }
    }
}
//���������������·��
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
//����������������·��
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
//ɾ����������Ϣ
void delete_str(char str1[], char str2[],int len,char str3[])
{
    int num=0,k=0,i=0,j=0;   //num������¼�Ӵ��ĸ��� k������¼�Ӵ���λ��
    char *p=str2;             //ʹ��p��ԭstr����ʼλ��
    while(str1[i]!='\0')
    {
        if(str1[i]!=str2[j])
        {
            str3[k++]=str1[i++];  //��str1�е��ַ���str�����ַ�����ͬʱ
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
                num++;           //�����ظ��Ӵ���num��һ
            }
            else
            {
                //���ַ����д��ں��Ӵ�ǰ�����ַ���ͬ��һ���ַ�
                //�˳�ѭ����������ַ�д���µ��ַ�������
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
//�������뺯��
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
            else if(a[i]=='\b')         //�������˸����������
            {
                printf("\b \b");
                i--;
            }
            else
            {
                pass=0;
                break;   //�˳�forѭ�����ٴν���
            }
        }
        fflush(stdin);  //������̻��������Ѿ��е�����
        printf("\n");
        if(pass==0)    //��������������������������������˷������ַ���ֱ������Ϊ0����6λȫ0�������˳�forѭ��
        {
            printf("����Ҫ��ȫΪ���֣��Ҳ���ȫ0��\n");
            printf("��������������: ");
        }
        else
            break;
    }
    return pass;
}
//��ͼ������һ������
void add_point(MGraph &g)
{
    int i,d;
    N++;
    g.vex[N-1].num=N-1;
    printf("%d\n",N);
    printf("������Ҫ���Ӿ��������:");
    scanf("%s",g.vex[N-1].name);
    printf("%s\n",g.vex[N-1].name);
    printf("������þ���������������·������:");
    for(i=0; i<N; i++)
    {
        scanf("%d",&d);
        g.edges[i][N-1]=g.edges[N-1][i]=d;
    }
    printf("������Ҫ���Ӷ���ļ��:");
    scanf("%s",g.vex[N-1].introduction);
    printf("���ӳɹ�!\n");
}
//��ͼ������һ��·��
void add_path(MGraph &g)
{
    int i,j,length,k;
    do
    {
        printf("������Ҫ����·������ʼ��ı��:");
        scanf("%d",&i);
        printf("������Ҫ����·�����յ�ı��:");
        scanf("%d",&j);
        if(i>=0&&i<=N-1&&j>=0&&j<=N-1&&j>=0)
        {
            if(g.edges[i][j]!=INF&&g.edges[j][i]!=INF)
            {
                printf("������֮���Ѵ���·��,�Ƿ�����޸�(0.�޸� 1.���޸�):");
                scanf("%d",&k);
                if(k==0)
                {
                    printf("������Ҫ�޸ĵ�·���ĳ���:");
                    scanf("%d",&length);
                    g.edges[j][i]=g.edges[i][j]=length;
                    printf("�޸ĳɹ�!");
                }
                else
                    g.edges[j][i]=g.edges[i][j];
            }
            else
            {
                printf("������Ҫ���ӵ�·���ĳ���:");
                scanf("%d",&length);
                g.edges[j][i]=g.edges[i][j]=length;
                printf("��ӳɹ�!\n");
            }
            break;
        }
        else
        {
            printf("����Ķ�����ԭͼ�в�����!\n");
            continue;
        }
    }
    while(1);
}
//ɾ��ͼ�е�һ������
void delete_point(MGraph &g)
{
    int i,j,m;
    printf("%d\n",N);
    printf("������Ҫɾ������ı��:");
    scanf("%d",&m);
    do
    {
        if(m>=0&&m<=N-1)
            break;
        else
        {
            printf("������Ҫɾ������ı��:");
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
    printf("ɾ���ɹ�!\n");
}
//ɾ��ͼ�е�һ��·��
void delete_path(MGraph &g)
{
    int i,j;
    do
    {
        printf("������Ҫɾ��·������ʼ��ı��:");
        scanf("%d",&i);
        printf("������Ҫɾ��·�����յ�ı��:");
        scanf("%d",&j);
        if(g.edges[i][j]==INF)
            printf("������䲻����·��!\n");
        else
        {
            g.edges[i][j]=g.edges[j][i]=INF;
            break;
        }
    }
    while(1);
    printf("ɾ���ɹ�!\n");
}
//�������������
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
    printf("\t\t     *       1.�û�                *\n");
    printf("\t\t     *       2.������Ա            *\n");
    printf("\t\t     *******************************\n");
    printf("��ѡ����Ӧ�ı�Ž�����һ������:");
    scanf("%d",&k);
    do
    {
        if(k==1||k==2)
            break;
        else
        {
            printf("�������ݲ�����,����������:");
            scanf("%d",&k);
        }
    }
    while(1);
    if(k==1)
    {
        system("title У԰������ܼ�·����ѯϵͳ");
        system("color F0");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t��ӭ����У԰������ܼ�·����ѯϵͳ!\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("���ڽ���,���Ժ�...\n");
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
            printf("\t\t     *       1.������            *\n");
            printf("\t\t     *       2.����������·��    *\n");
            printf("\t\t     *       3.�����������·��    *\n");
            printf("\t\t     *       4.�˳�ϵͳ            *\n");
            printf("\t\t     *******************************\n");
            printf("������Ҫ���еĲ����ı��:");
            scanf("%d",&x);
            do
            {
                if(x>=1&&x<=4)
                    break;
                else
                {
                    printf("�������ݲ�����,����������:");
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
                    printf("�Ƿ�������иò���(0.���� 1.������):");
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
                    printf("���������λ�õı��:");
                    scanf("%d",&u);
                    printf("�������յ�λ�õı��:");
                    scanf("%d",&v);
                    printf("��%s��%s������·��Ϊ:\n",g.vex[u].name,g.vex[v].name);
                    FindaPath(g,G,u,v,path,-1);
                    printf("�Ƿ�������иò���(0.���� 1.������):");
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
                printf("ȷ���˳���?(0.�˳� 1.���˳�):");
                scanf("%d",&ch);
                while(1)
                {
                    if(ch==0||ch==1)
                        break;
                    else
                    {
                        printf("��������ݲ���������������:");
                        scanf("%d",&ch);
                    }
                }
                if(ch==0)
                {
                    x=0;
                    printf("ллʹ�ñ�ϵͳ����ӭ�´ι���!");
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
        printf("������������:");
        scanf("%s",na);
        printf("����������¼����:");
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
                    printf("���Ѿ������������,ϵͳ����10���ر�!");
                    Sleep(10000);
                    break;
                }
                printf("������������!�㻹��%d�λ���,����������:",t);
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
                printf("\t\t     *     1.���Ӿ�������Ϣ      *\n");
                printf("\t\t     *     2.ɾ����������Ϣ      *\n");
                printf("\t\t     *     3.���¾�������Ϣ      *\n");
                printf("\t\t     *     4.���Ӿ���              *\n");
                printf("\t\t     *     5.����·��              *\n");
                printf("\t\t     *     6.ɾ������              *\n");
                printf("\t\t     *     7.ɾ��·��              *\n");
                printf("\t\t     *     8.�˳�ϵͳ              *\n");
                printf("\t\t     *******************************\n");
                printf("��ѡ��Ҫ���еĲ���:");
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
                        printf("������ҪҪ������Ϣ�ľ���ı��:");
                        scanf("%d",&d);
                        ReadData(g);
                        printf("%s\n",g.vex[d].introduction);
                        printf("������Ҫ���ӵ���Ϣ:");
                        scanf("%s",str2);
                        strcat(g.vex[d].introduction,str2);
                        printf("���ӳɹ�!\n");
                        WriteData(g);
                        printf("�Ƿ�������иò���(0.���� 1.������):");
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
                        printf("������Ҫɾ����Ϣ�ľ���ı��:");
                        scanf("%d",&d);
                        ReadData(g);
                        strcpy(str1,g.vex[d].introduction);
                        printf("%s\n",str1);
                        printf("������Ҫɾ������Ϣ:");
                        scanf("%s",str2);
                        printf("%d\n",N);
                        delete_str(str1,str2,strlen(str2),str3);
                        printf("%s\n",str3);
                        strcpy(g.vex[d].introduction,str3);
                        printf("%s\n",g.vex[d].introduction);
                        WriteData(g);
                        printf("ɾ���ɹ�!\n");
                        printf("�Ƿ�������иò���(0.���� 1.������):");
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
                        printf("������Ҫ������Ϣ�ľ���ı��:");
                        scanf("%d",&d);
                        ReadData(g);
                        printf("������Ҫ���µ���Ϣ:");
                        scanf("%s",str2);
                        strcpy(g.vex[d].introduction,str2);
                        WriteData(g);
                        printf("�Ƿ�������иò���(0.���� 1.������):");
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
                    printf("ȷ���˳���?(0.�˳� 1.���˳�):");
                    scanf("%d",&ch);
                    while(1)
                    {
                        if(ch==0||ch==1)
                            break;
                        else
                        {
                            printf("��������ݲ���������������:");
                            scanf("%d",&ch);
                        }
                    }
                    if(ch==0)
                    {
                        x=0;
                        printf("�����˳�....");
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


