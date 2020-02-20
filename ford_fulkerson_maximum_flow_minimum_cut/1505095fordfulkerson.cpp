#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<fstream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

using namespace std;

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
    int **residual;
    int **flowmatrix;
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
    void mst(int source);
    int floydwarshall();
    int fordfulkerson(int s, int t);
    int isConnected(int s, int t);
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
    //residual=0;
    //flowmatrix=0;
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
    residual= new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        residual[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            residual[i][j] = -1; //initialize the matrix cells to 0
    }
    flowmatrix= new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        flowmatrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            flowmatrix[i][j] = 0; //initialize the matrix cells to 0
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
        printf("is edge.\n");
        return true;
    }
    else
    {
        printf("not edge. \n");
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
            int v=adjList[u].getItem(j);
            if( color[v]==WHITE && residual[u][v]>0)
            {
                color[v]=GREY;
                dist[v]=dist[u]+1;
                parent[v]=u;
                q.enqueue(v);
            }
        }
        color[u]=BLACK;
    }

}

int Graph::isConnected(int s, int t)
{
    bfs(s);
    if(color[t]==WHITE)
    {
        return 0;
    }
    else
    {
        return 1;
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
        printf("%d:", i+1);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            int v=adjList[i].getItem(j);
            printf(" %d %d/%d , ",v+1,matrix[i][v]-residual[i][v],matrix[i][v]);
        }
        printf("\n");
    }
}

int Graph::fordfulkerson(int s, int t)
{
    int maxflow=0,i,j,mflow=0;
    for(i=0; i<nVertices; i++)
    {
        for(j=0; j<adjList[i].getLength(); j++)
        {
            int v=adjList[i].getItem(j);
            residual[i][v]=matrix[i][v];
        }
    }

    while(isConnected(s,t))
    {
        int flow=INFINITY;
        for(j=t; j!=s; j=parent[j])
        {
            i=parent[j];
            flow=min(flow,residual[i][j]);
        }
        for(j=t; j!=s; j=parent[j])
        {
            i=parent[j];
            flowmatrix[i][j]=flow;
        }
        for(j=t; j!=s; j=parent[j])
        {
            i=parent[j];
            residual[i][j] -= flow;
            residual[j][i] += flow;
        }
        cout<<endl;
        maxflow+=flow;
    }
    /*  for(int i=0; i<nVertices; i++)
      {
          for(int j=0; j<adjList[i].getLength(); j++)
          {
              int v=adjList[i].getItem(j);
              cout<<i+1<<' '<<v+1<<' '<<matrix[i][v]-residual[i][v]<<"/"<<matrix[i][v]<<endl;
          }
      }*/
    printGraph();
    // cout<<endl;
    // cout<<"maxflow: "<<maxflow<<endl;
    cout<<endl;
    cout<<"mincut: "<<endl;
    for(int i=0; i<nVertices; i++)
    {
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            int v=adjList[i].getItem(j);
            // if(flowmatrix[i][v]==matrix[i][v])
            if(color[i]==BLACK && color[v]==WHITE && matrix[i][v])
            {
                cout<<i+1<<' '<<v+1<<' '<<endl;
                mflow+=matrix[i][v];
            }
        }
    }
    cout<<endl;
    cout<<"max flow: "<<endl;
    int finalflow=max(maxflow,mflow);
    cout<<finalflow<<endl;
}

Graph::~Graph()
{
    if(adjList)  delete[ ] adjList;
    adjList=0;
}

int main ()
{
    FILE *fptr;
    char filename[15];
    char ch;
    int n,e,u,v,w,s,t;
    Graph g(true);

    fptr = fopen("edge1.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    //ch = fgetc(fptr);
    else
    {
        fscanf(fptr,"%d",&n);
        g.setnVertices(n);
        fscanf(fptr,"%d",&e);
        printf ("%d\n", n);
        printf ("%d\n", e);
        for(int i=0; i<e; i++)
        {
            fscanf(fptr,"%d %d %d",&u,&v,&w);
            cout<<u<<' '<<v<<' '<<w<<endl;
            g.addEdge(u-1,v-1,w);
        }
    }
    printf("the source? ");
    scanf("%d",&s);
    printf("the sink? ");
    scanf("%d",&t);
    g.fordfulkerson(s-1,t-1);
    fclose(fptr);

    return 0;
}


/*  int main(void)
{
  int n;
  Graph g;
  printf("Enter number of vertices: ");
  scanf("%d", &n);
  g.setnVertices(n);

  while(1)
  {
      printf("1. Add edge. 2. has common adjacent.\n");
      printf("3. remove edge. 4. is edge. 5. get degree.\n");
      printf("6. get distance. 7. Print Graph  8. mst.\n");

      int ch;
      scanf("%d",&ch);
      if(ch==1)
      {
          int u, v, w;
          scanf("%d%d%d", &u, &v, &w);
          g.addEdge(u-1, v-1, w);
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
  }
}   */


