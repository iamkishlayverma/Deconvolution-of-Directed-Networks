#include <stdio.h>
#include <stdlib.h>
//void combinationUtil(struct Graph* graph,int arr[], int data[], int start, int end,
                   //  int index, int r);
// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void printCombination(struct Graph* graph,int arr[], int n, int r)
{
    // A temporary array to store all combination one by one
    int data[r];
    // Print all combination using temprary array 'data[]'
    combinationUtil(graph,arr, data, 0, n-1, 0, r);
}
/* arr[]  ---> Input Array
   data[] ---> Temporary array to store current combination
   start & end ---> Staring and Ending indexes in arr[]
   index  ---> Current index in data[]
   r ---> Size of a combination to be printed */
void combinationUtil(struct Graph* graph,int arr[], int data[], int start, int end,int index, int r)
{
    int j,i;
    // Current combination is ready to be printed, print it
    if (index == r)
    {
        printf("\nSUBGRAPH WITH VERTICES : ");
        for (j=0; j<r; j++)
            printf("%d  ", data[j]);
        printf("\n");
        sub1(graph,data,r);
        return;
    }
    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(graph,arr, data, i+1, end, index+1, r);
    }
}
// Driver program to test above functions
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
// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};
// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =(struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    // Since graph is undirected, add an edge from dest to src also
    /*newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;*/
}
// A utility function to print the adjacenncy list representation of graph
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
                //if(i!=j && (in[data[i]]==1 && out[data[i]]==2 && in[data[j]]==3 && out[data[j]]==0) || (in[data[i]]==0 && out[data[i]]==3 && in[data[j]]==2 && out[data[j]]==1) || (in[data[i]]==0 && out[data[i]]==3 && in[data[j]]==3 && out[data[j]]==0))
                {
                    arr[k]=data[j];
                    brr[k]=data[i];
                    printf("%d-->--%d\t",brr[k],arr[k]);
                    printf("\n");
                    k++;
                }
            }

            /*struct AdjListNode* pCrawl = graph->array[data[i]].head;
            printf("\n Adjacency list of vertex %d\n head ", data[i]);
            while(pCrawl)
            {
                for(k=0;k<4;k++)
                {
                    if(pCrawl->dest==data[0]||pCrawl->dest==data[1]||pCrawl->dest==data[2]||pCrawl->dest==data[3])
                    {
                        if(pCrawl->dest!=arr[k] && arr[k] != -1)
                        {
                            printf("-> %d", pCrawl->dest);
                        }
                    }
                }
                pCrawl = pCrawl->next;
                printf("\n");
            }*/
        }
        printf("\n");
    }

    /*for (i = 0; i < 4; i++)
    {
        if(in[data[i]]+out[data[i]]>1)
        {
            if(edge>4)
        }
    }*/

}
// Driver program to test above functions
int main()
{
    int v,e,src,dest,i;
    // create the graph given in above fugure
    printf("Enter the order and size of the graph:");
    scanf("%d %d",&v,&e);
    struct Graph* graph = createGraph(v);
    for(i=0;i<e;i++)
    {
        printf("Enter source and destination vertices:");
        scanf("%d %d",&src,&dest);
        addEdge(graph,src,dest);
    }
    // print the adjacency list representation of the above graph
    printGraph(graph);

    return 0;
}
