#include <stdio.h>
#include <stdlib.h>

struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =(struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void sub1(struct Graph* graph,int *data,int r)
{
    int i,j,edge=0,count=0;
    int in[50]={0}, out[50]={0};
    for (i = 0; i < r; i++)
    {
        struct AdjListNode* pCrawl = graph->array[data[i]].head;
        printf("\nAdjacency list of vertex %d\nhead ", data[i]);
        while (pCrawl)
        {
            if(pCrawl->dest==data[0]||pCrawl->dest==data[1]||pCrawl->dest==data[2]||pCrawl->dest==data[3])
            {
                printf("--->%d", pCrawl->dest);
                out[data[i]]++;
                in[pCrawl->dest]++;
            }
            pCrawl = pCrawl->next;
        }
        if(out[data[i]]+in[data[i]] > 1)
        {
            count++;
        }
        printf("\n");
    }
    printf("\n\n");
    for(i=0;i<graph->V;i++)
    {
        printf("out[%d]=%d   in[%d]=%d",i,out[i],i,in[i]);
        edge=edge+in[i];
        printf("\n");
    }
    printf("\nTotal number of Edges=%d\n\n",edge);
    int arr[40]={-1},brr[40]={-1};
    if(count==4 && edge > 4)
    {
        printf("Edges to be removed:\n");
        for(i=0;i<4;i++)
        {
            int k=0;
            for(j=0;j<4;j++)
            {
                if(i != j && out[data[i]]>=2 && in[data[j]]>=2)
                {
                    arr[k]=data[j];
                    brr[k]=data[i];
                    printf("%d-->--%d\t",brr[k],arr[k]);
                    printf("\n");
                    k++;
                }
            }
        }
        printf("\n");
    }
}

void combinationUtil(struct Graph* graph,int arr[], int data[], int start, int end,int index, int r)
{
    int j,i;
    if (index == r)
    {
        printf("\nSUBGRAPH WITH VERTICES : ");
        for (j=0; j<r; j++)
            printf("%d  ", data[j]);
        printf("\n");
        sub1(graph,data,r);
        return;
    }
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(graph,arr, data, i+1, end, index+1, r);
    }
}

void printCombination(struct Graph* graph,int arr[], int n, int r)
{
    int data[r];
    combinationUtil(graph,arr, data, 0, n-1, 0, r);
}

void newOne(struct Graph* graph,int v)
{
    int i,arr[v];
    for(i=0;i<v;i++)
    {
        arr[i]=i;
    }
    int r = 4;
    printCombination(graph,arr, v, r);
}

void printGraph(struct Graph* graph)
{
    int v,i;
    printf("\nMAIN GRAPH WITH VERTICES : ");
    for(i=0;i<graph->V;i++)
    {
        printf("%d  ",i);
    }
    printf("\n");
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\nAdjacency list of vertex %d\nhead ", v);
        while (pCrawl)
        {
            printf("--->%d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
    printf("\n");
    newOne(graph,graph->V);
}

void removeGraph(struct Graph* graph,int src,int destin)
{
    int i;
    for(i = 0; i < graph->V; i++)
    {
        if(graph->array[i].head == src)
        {
            struct AdjListNode* pCrawl = graph->array[i].head;
            struct AdjListNode* tmp = graph->array[i].head;
            if(pCrawl->dest==destin)
            {
                pCrawl=tmp->next;
                tmp->next=NULL;
                free(tmp);
                break;
            }
            else
            {
                tmp=tmp->next;
                while(tmp->dest != NULL)
                {
                    if(tmp->dest==destin)
                    {
                        pCrawl->next=tmp->next;
                        tmp->next=NULL;
                        free(tmp);
                        break;
                    }
                    pCrawl=pCrawl->next;
                    tmp=tmp->next;
                }
                break;
            }
        }
    }
    printGraph(graph);
}

int main()
{
    int v,e,src,dest,i;
    printf("Enter the order and size of the graph:");
    scanf("%d %d",&v,&e);
    struct Graph* graph = createGraph(v);
    for(i=0;i<e;i++)
    {
        printf("Enter source and destination vertices:");
        scanf("%d %d",&src,&dest);
        addEdge(graph,src,dest);
    }
    printGraph(graph);
    //removeGraph(graph,0,3);
    return 0;
}
