#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

using namespace std;

class HeapItem
{
public:
    int data; //actual data that is stored
    float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
    int heapLength;
    int * map;

    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength=0;
    }

    ~MinHeap() //destructor
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0; //set to NULL after deletion
        A = 0; //set to NULL after deletion
    }
    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
    }
    //this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int data, float key)
    {
        int sz,i;
        if( sz==MAX_HEAP_SIZE )
        {
            printf("not enough space.\n");
            return;
        }
        heapLength++;
        i=heapLength;
        A[i].data=data;
        A[i].key=key;
        map[A[i].data]=i;

        buHeapify(i);
    }

    //this function removes (and returns) the node which contains the minimum key value
    HeapItem removeMin()
    {
        HeapItem temp;
        temp=A[1];
        A[1]=A[heapLength];
        heapLength--;
        heapify(1);
        return temp;

    }
    //The function updates the key value of an existing data
    //stored in the heap
    //Note that updates can result in an increase or decrease of key value
    //Call to heapify or buheapify is required
    void updateKey(int data, float key)
    {
        int i=map[data];
        if(key>A[i].key)
        {
            A[i].key=key;
            heapify(i);
        }
        else if(key<A[i].key)
        {
            A[i].key=key;
            buHeapify(i);
        }
    }
    //This function returns the key value of a data stored in heap
    float getKey(int data)
    {
        int i = map[data];
        return A[i].key;
    }
    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;      //left child index
            r=2*i+1;    //right child index
            smallest=i;

            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( A[l].key < A[r].key )
                smallest = l;
            else
                smallest = r;

            if(A[i].key <= A[smallest].key)
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].data]=i;
                A[smallest]=t;
                map[A[smallest].data]=smallest;
                i=smallest;
            }
        }
    }
    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
    void buHeapify(int i)
    {
        HeapItem temp;

        if(i==NULL|| i==1)
        {
            return ;
        }
        else if( A[i].key>=A[i/2].key )
        {
            return ;
        }
        else if(A[i].key<A[i/2].key)
        {
            temp=A[i];
            A[i]=A[i/2];
            map[A[i].data]=i;
            A[i/2]=temp;
            map[A[i/2].data]=i/2;
        }
        i=i/2;
        buHeapify(i);
    }

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }
};


class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}

void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}

bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}

int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}

Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}
//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int  weight;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getweight(int position);
    int getLength();
    bool empty();
    void printList();
} ;

ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    weight = 0;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ;//copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ;//make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}

int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    int **matrix;
    bool directed ;
    ArrayList  * adjList ;
    int *color;
    int *parent;
    int *dist;
    int time;
    int *fin;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(); //will run dfs in the graph
    void dfsvisit(int i);
    bool tree();
    bool connected();
    void mst(int source);
    int shortestpath(int source);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix=0;
    adjList = 0 ;
    directed = dir ;
    color=0;
    dist=0;
    parent=0; //set direction of the graph
    //define other variables to be initialized
    time=0;
    fin=0;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
    color=new int [nVertices];
    parent=new int [nVertices];
    dist= new int [nVertices];
    fin = new int[nVertices];
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
}

void Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    matrix[u][v]=w;
    if(!directed)
    {
        adjList[v].insertItem(u) ;
        matrix[v][u]=w;
    }
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    if(adjList[u].searchItem(v)!=NULL_VALUE && adjList[v].searchItem(u)!=NULL_VALUE)
    {
        adjList[u].removeItem(v);
        adjList[v].removeItem(u);
        this->nEdges--;
    }
    else
    {
        adjList[u].removeItem(v);
    }
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    if( adjList[u].searchItem(v)!=NULL_VALUE && adjList[v].searchItem(u)!=NULL_VALUE )
    {
        //  printf("is edge.\n");
        return true;
    }
    else
    {
        //printf("not edge. \n");
        return false;
    }
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices) return 0;
    int cont=0;
    for(int i=0; i<nVertices; i++)
    {
        if(adjList[u].searchItem(i)!=NULL_VALUE && adjList[i].searchItem(u)!=NULL_VALUE )
        {
            cont++;
        }
    }
    printf("degree: %d\n",cont);
    return 0;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    int len=adjList[u].getLength();
    int l=adjList[v].getLength();
    for(int i=0; i<len; i++)
    {
        for(int j=0; j<l; j++)
        {
            if(adjList[u].getItem(i)==adjList[v].getItem(j))
            {
                printf("true\n");
                return true;
            }

        }
    }
    printf("false\n");
    return false;
}

void Graph::bfs(int source)
{
    int u;
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        u=q.dequeue();
        int len=adjList[u].getLength();
        for(int j=0; j<len; j++)
        {
            if( color[adjList[u].getItem(j)]==WHITE )
            {
                color[adjList[u].getItem(j)]=GREY;
                dist[adjList[u].getItem(j)]=dist[u]+1;
                parent[adjList[u].getItem(j)]=parent[u];
                q.enqueue(adjList[u].getItem(j));
            }
        }
        color[u]=BLACK;
    }
}

void Graph::dfs()
{

    for(int i=0; i<nVertices; i++)
    {
        color[i]=WHITE;
        parent[i]=-1;
    }
    time=0;
    for(int i=0; i<nVertices; i++)
    {
        if(color[i]==WHITE)
        {
            dfsvisit(i);
        }
    }
}

void Graph::dfsvisit(int u)
{
    color[u]=GREY;
    time=time+1;
    dist[u]=time;
    int len=adjList[u].getLength();
    for(int j=0; j<len; j++)
    {
        if(color[adjList[u].getItem(j)]==WHITE)
        {
            parent[adjList[u].getItem(j)]=u;
            dfsvisit(adjList[u].getItem(j));
        }
    }
    color[u]=BLACK;
    time=time+1;
    fin[u]=time;
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return 0;
    if(u==v)   return 0;
    // if(u!=parent[v])  return 0;
    bfs(u);
    dist[v];
    printf("distance is: %d\n",dist[v]);
    return INFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

bool Graph::connected()
{
    int source=adjList[0].getItem(0);
    cout<<source<<endl;
    bfs(source);
    int flag=1;
    for(int i=0; i<nVertices; i++)
    {
        if(color[i]==WHITE)
        {
            flag=0;
            break;
        }
    }
    if(flag==1) return true;
    return false;
}

bool Graph::tree()
{

    bool f=connected();
    if(f && nEdges==(nVertices-1) )
    {
        return true;
    }
    return false;
}

void Graph:: mst(int source)
{
    int *arr;
    arr = new int[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        arr[i]=0;
    }
    MinHeap heap;
    for(int i=0; i<nVertices; i++)
    {
        heap.insertItem(i,INFINITY);
        arr[i]=1;
        parent[i]=0;
    }
    heap.updateKey(source,0);
    while(!heap.Empty())
    {
        int u;
        u=heap.removeMin().data;
        arr[u]=0;
        for(int i=0; i<adjList[u].getLength(); i++)
        {
            int v;
            v=adjList[u].getItem(i);
            if(arr[v]==1 && matrix[u][v]< heap.getKey(v))
            {
                parent[v]=u;
                heap.updateKey(v,matrix[u][v]);
            }
        }
    }
    int weight=0;
    for(int i=1; i<nVertices; i++)
    {
        weight=weight+matrix[parent[i]][i];
        printf("%d %d\n", parent[i]+1, i+1);
    }
    printf("%d\n", weight);
}

int Graph::shortestpath(int source)
{
    int *arr,v,weight=0,flag=0;
    arr=new int [nVertices];
    for(int i=0; i<nVertices; i++)
    {
        dist[i]=INFINITY;
        parent[i]=-1;
        arr[i]=0;
    }
    dist[source]=0;
    for(int i=0; i<nVertices; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            if(isEdge(i,j))
            {
                arr[i]=1;
            }
        }
    }
    for(int i=0; i<nVertices-1; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            for(int k=0; k<adjList[j].getLength(); k++)
            {
                v=adjList[j].getItem(k);
                if(dist[v]>dist[j]+matrix[j][v])
                {
                    dist[v]=dist[j]+matrix[j][v];
                    //  cout<<dist[v]<<endl;
                    parent[v]=j;
                    // cout<<parent[v]<<endl;
                }
            }
        }
    }
    for(int i=0; i<nVertices-1; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            for(int k=0; k<adjList[j].getLength(); k++)
            {
                v=adjList[j].getItem(k);
                if(dist[v]>dist[j]+matrix[j][v])
                {
                    //dist[v]=dist[j]+matrix[j][v];
                    //parent[v]=j;
                    flag=1;
                    break;
                }
            }
        }
    }
    for(int i=0; i<nVertices; i++)
    {
        if(parent[i]==-1)
        {
            cout<<i+1<<"    "<<dist[i]<<"   "<<parent[i]<<endl;
        }
        else
        {
            cout<<i+1<<"    "<<dist[i]<<"   "<<parent[i]+1<<endl;
        }
    }
    cout<<"Negative Cycle?"<<' ';
    if(flag==0)
    {
        cout<<"No"<<endl;
    }
    if(flag==1)
    {
        cout<<"Yes"<<endl;
    }

    return 0;
}

Graph::~Graph()
{
    if(adjList)  delete[ ] adjList;
    adjList=0;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************

int main()
{
    FILE *fptr;
    int n,e,u,v,w,source;
    Graph g(true);
    Graph graph;


    fptr = fopen("edge.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    else
    {
        fscanf(fptr,"%d",&n);
        g.setnVertices(n);
        graph.setnVertices(n);
        fscanf(fptr,"%d",&e);
        printf ("%d\n", n);
        printf ("%d\n", e);
        for(int i=0; i<e; i++)
        {
            fscanf(fptr,"%d %d %d",&u,&v,&w);
            cout<<u<<' '<<v<<' '<<w<<endl;
            g.addEdge(u-1,v-1,w);
            graph.addEdge(u-1,v-1,w);
        }
    }

    cout<<"The Source?"<<' ';
    scanf("%d",&source);
    // graph.mst(0);
    g.shortestpath(source);
    fclose(fptr);

    return 0;
}

/*int main(void)
{
    int n,e;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d",&e);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. 2. has common adjacent. 9.dfs\n");
        printf("3. remove edge. 4. is edge. 5. get degree.\n");
        printf("6. get distance. 7. Print Graph  8. mst\n");


        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g.addEdge(u, v, w);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.hasCommonAdjacent(u,v);
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u,v);
        }
        else if(ch==4)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.isEdge(u,v);
        }
        else if(ch==5)
        {
            int u;
            scanf("%d", &u);
            g.getDegree(u);
        }
        else if(ch==6)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.getDist(u,v);

        }
        else if(ch==7)
        {
            g.printGraph();
        }
        else if(ch==8)
        {
            g.mst(0);
        }
        else if (ch==9)
        {
            g.dfs();
        }
    }
}*/
