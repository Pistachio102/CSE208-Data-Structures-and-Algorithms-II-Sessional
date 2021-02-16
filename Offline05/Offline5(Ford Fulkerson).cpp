#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <limits.h>
#include <string.h>
#include<fstream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define SUCCESS_VALUE 99999

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
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
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
    ArrayList  * adjList ;
    int **weight;
    int **edgeExists;
    int *parent;


    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    int **residual;
    bool directed ;
    Graph(bool dir );
    bool isEdge(int u, int v);
    ~Graph();
    void setnVertices(int n);
    void addEdgeWeight(int u, int v, int w);
    // void removeEdge(int u, int v);
    // bool isEdge(int u, int v);
    // int getDegree(int u);
    // bool hasCommonAdjacent(int u, int v);
    // int getDist(int u, int v);
    // void printGraph();
    bool bfs( int source,int sink);//will run bfs in the graph
    void dfs(int s, bool devisited[])
    {
        devisited[s] = true;
        for (int i = 0; i < nVertices; i++)
            if (residual[s][i] && !devisited[i])
                dfs(i, devisited);
    }
    int FordFulkerson(int source, int sink);

};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    parent=0;
    weight=0;
    residual=0;

    //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;

    parent=new int[nVertices];
   // edgeExists=new int [nVertices];
   edgeExists=new int*[nVertices];
    weight = new int*[n];
    residual=new int*[n];

    for(int i=0; i<n; i++)
    {
        weight[i] = new int[n];
        residual[i] = new int[n];
        edgeExists[i]=new int[n];
        //for(int j=0;j<n;j++)
        //  weight[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdgeWeight(int u, int v, int w)
{

    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    //this->nEdges++ ;
    adjList[u].insertItem(v) ;
    weight[u][v]=w;
    residual[u][v]=w;
    edgeExists[u][v]=1;
    // edgeList[count++].setVertices(u,v);
   /* if(!directed)
    {
        adjList[v].insertItem(u) ;
        weight[v][u]=w;
    }*/
}

bool Graph::bfs(int source, int sink)
{
    //complete this function
    //initialize BFS variables
    int u;
    bool visited[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        //color[i] = WHITE ;
        //parent[i] = -1 ;
        visited[i]=false;
        // dist[i] = INFINITY ;
    }
    Queue q ;

    q.enqueue(source) ;
    visited[source]=true;
    parent[source]=-1;

    while( !q.empty() )
    {

        u=q.dequeue();
        visited[u]=true;


        for(int v=0; v<nVertices; v++)
        {
            if(visited[v]==false && residual[u][v]>0)
            {

                q.enqueue(v);
                parent[v]=u;

            }
        }



    }


    return (visited[sink]==true);


}



bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        //printf("Invalid vertice.\n");
        return false;
    }
    int x=adjList[u].searchItem(v);
    //int y=adjList[v].searchItem(u);
    if(x==NULL_VALUE )
        return false;
    else
    {
        return true;
    }
}

int Graph::FordFulkerson(int source, int sink)
{
    int u,v,flow, maximumFlow=0;
    int s=source, t=sink;



    while(bfs(s,t))
    {
        flow=INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            flow = min(flow, residual[u][v]);

        }

        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            residual[u][v] =residual[u][v] - flow;
            residual[v][u] =residual[u][v] + flow;
        }


        maximumFlow=maximumFlow+flow;
    }

    cout<<maximumFlow<<endl;



    bool devisited[nVertices];
    /*for(int i=0;i<nVertices;i++)
    {
        devisited[i]=false;
    }*/
    memset(devisited, false, sizeof(devisited));
    dfs(s, devisited);

    // Print all edges that are from a reachable vertex to
    // non-reachable vertex in the original graph
    for (int i = 0; i < nVertices; i++)
    {
        for (int j = 0; j < nVertices; j++)
        {
            if (devisited[i] && !devisited[j] && weight[i][j])
            {
                cout << i << " - " << j << endl;
                //cout << i<<"  " <<j<<"  "<<weight[i][j] << endl;
                //cout << i << " - " << j << endl;
            }
        }
    }
    cout<<endl;
    cout<<endl;


    for(int i=0; i<=nVertices; i++)
    {
        for(int j=0; j<=nVertices; j++)
        {
            if(isEdge(i,j))
            {


                //printf("From %d to %d , flow is %d\n",i,j,graph[i][j]-rGraph[i][j]);
                cout<<"from "<<i<<" to "<<j<<","<<"flow is"<<weight[i][j]-residual[i][j]<<endl;
            }
        }
    }




    //return;
   /* for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            cout<<i<<j<<weight[i][j]<<"   ";
        }
        cout<<endl;
    }*/






}

Graph::~Graph()
{
    //write your destructor here
    if( parent && adjList)
    {

        delete[] parent;
        delete[] adjList;
    }

    parent=0;
    adjList=0;
}


int main()
{

    freopen("in.txt","r",stdin);
    freopen("Output.txt","w",stdout);

    //  ifstream fin("in.txt");



    Graph g(true);

    int n, m, source, sink, u, v, w;
    cin >> n >> m >> source >> sink;
    // cout << n << m << source<<sink<<endl;

    g.setnVertices(n);
    // g.setnEdges(m);

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        //cout << u << v << w << endl;
        g.addEdgeWeight(u,v,w);
    }


    g.FordFulkerson(source,sink);




    // cout<<maxFlow;



    return 0;
}
