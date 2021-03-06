#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#define NULL_VALUE -999999
#define INFINITY 999999



using namespace std;


class Edge
{
    int sVertex;
    int eVertex;

public:
    Edge()
    {
        sVertex=0;
        eVertex=0;
    }

    Edge(int s,int e)
    {
        sVertex=s;
        eVertex=e;
    }

    void setVertices(int s, int e)
    {
        sVertex=s;
        eVertex=e;
    }

    int getsVertice()
    {
        return sVertex;
    }
    int geteVertice()
    {
        return eVertex;
    }




};

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
    int nVertices, nEdges, **weight ;

    ArrayList  * adjList ;
    Edge *edgeList;
    int count;



    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    bool directed ;
    Graph(bool dir );
    ~Graph();
    void setnVertices(int n);
    void setnEdges(int e);
    void addEdgeWeight(int u, int v, int w);
    void BellmanFord(int source);
    void printGraph();
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    edgeList=0;
    directed = dir ;
    count=0;
    //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;


    //cout<<"HI"<<endl;
    weight = new int*[n];
    for(int i=0; i<n; i++)
    {
        weight[i] = new int[n];
        //for(int j=0;j<n;j++)
        //  weight[i][j] = 0; //initialize the matrix cells to 0
    }
    //cout<<"HI2"<<endl;
}

void Graph:: setnEdges(int e)
{
    this->nEdges=e;
    if(edgeList!=0) delete[] edgeList;
    edgeList=new Edge[nEdges];

}

void Graph::addEdgeWeight(int u, int v, int w)
{

    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    //this->nEdges++ ;
    adjList[u].insertItem(v) ;
    weight[u][v]=w;
    edgeList[count++].setVertices(u,v);
    if(!directed)
    {
        adjList[v].insertItem(u) ;
        weight[v][u]=w;
    }
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

Graph::~Graph()
{
    //write your destructor here
    if(adjList)
    {
        delete[] adjList;
    }

    adjList=0;
}




void Graph:: BellmanFord(int source)
{

    int dist[nVertices], prev[nVertices], u, v ;


    for(int i=0 ; i<nVertices ; i++)
    {
        dist[i] = INFINITY;
        prev[i] = NULL_VALUE;
    }


    dist[source] = 0;


    for(int i=0; i<nVertices-1; i++)
    {
        for(int j=0;j<nEdges;j++)
        {
            u=edgeList[j].getsVertice();
            v=edgeList[j].geteVertice();

            if(dist[v]>(dist[u]+weight[u][v]))
                {
                    dist[v]=dist[u]+weight[u][v];
                    //cout<<dist[v]<<endl;
                    prev[v]=u;
                }
        }






    }




    int flag=0;


    for(int j=0;j<nEdges;j++)
        {
            u=edgeList[j].getsVertice();
            v=edgeList[j].geteVertice();

            if(dist[v]>(dist[u]+weight[u][v]))
                {
                    flag=1;
                    break;
                }
        }




     ofstream fOutput("output.txt");

    if(flag==1)
    {
        fOutput<<"Negative cycle detected. \n"<<endl;
        fOutput<<"Distance      Parent"<<endl;

    for(int i=0; i<nVertices; i++)
    {
        fOutput<<dist[i]<<"             "<<prev[i]<<endl;
    }

    }



    else
    {

        fOutput<<"No negative cycle detected. \n"<<endl;
        fOutput<<"Distance      Parent"<<endl;

    for(int i=0; i<nVertices; i++)
    {
        fOutput<<dist[i]<<"             "<<prev[i]<<endl;
    }
    }









}





















int main()
{


    int u,v,n,s, a, w, e ;
    Graph G(false);


    cout<<"Press 1 if the graph is directed else press 2."<<endl;
    cin>>a;

    if(a==1)
        G.directed=true;

    else G.directed=false;

    ifstream fInput("BellmanFord.txt");

    fInput>>n;
    //cout<<n<<endl;
    G.setnVertices(n);

    fInput>>e;
    G.setnEdges(e);




    fInput>>s;



    // cout<<"b4 while "<<endl;
    while(fInput>>u>>v>>w)
    {
        G.addEdgeWeight(u,v,w);

    }


    G.BellmanFord(s);
    //cout<<"bel "<<endl;

    fInput.close();









    return 0;
}
