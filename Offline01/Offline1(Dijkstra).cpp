#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999

#define SUCCESS_VALUE 99999

using namespace std;


class node
{
public:
    node()
    {

    }

    int pos;
    int value;
};

void Swap(node &a, node &b)
{
    node temp = a;
    a = b;
    b = temp;
}




class Heap
{
    int size;
    int length;
    node *arr;


public:



    Heap(int l)//it will create an empty heap
    {
        size=0;
        length=l+100;
        arr= new node[length];
    }

    int parent(int i)
    {
        return (i-1)/2;
    }
    int left(int i)
    {
        return (2*i+1) ;
    }
    int right(int i)
    {
        return (2*i+2) ;
    }
    node& getItemAt (int i)
    {
        return arr[i];
    }

    void Min_heapify( node *a, int i);

    void Build_Heap( int *a, int len);

    int Heap_Size();

    bool is_empty();

    int Find_Min();

    void Push(int i);

    int Pop();

    void Decrease_key(int i, int key);

    void Sift_Up(int l);

    void Sift_Down(int i);

    void print()
    {
        // cout<<arr[0]<<endl;
        for(int i=0; i<size; i++)
        {
            cout<<arr[i].pos<<"  "<<arr[i].value<<"->";
        }
        cout<<"\n\n";


    }
};




void Heap::Min_heapify( node *a, int i)
{
    // cout<<"in max"<<endl;

    int l,r,smallest;

    l=left(i);
    r=right(i);


    if(l< size && a[l].value<=a[i].value)
        smallest = l;
    else smallest = i;

    if(r< size && a[r].value<=a[smallest].value)
        smallest= r;

    if(smallest!= i )
    {
        Swap(a[i],a[smallest]);
        Min_heapify(a,smallest);
        //return;
    }
    // cout<<"out max"<<endl;
    return ;

}










void Heap::Build_Heap(int *a, int len )
{
    //arr=new int[len];
    for(int x=0; x<len; x++)
    {
        arr[x].value=a[x];
        arr[x].pos=x;
        //cout<<arr[x]<<"  "<<a[x]<<endl;
    }
    size=len;
    for(int i=(len-2)/2 ; i>=0 ; i--)
    {
        // cout<<i;
        Min_heapify(arr,i);

    }
    return;

}


int Heap::Heap_Size()
{
    return size;
}


bool Heap::is_empty()
{
    if(size==0)
        return true;
    else return false;
}




int Heap::Find_Min()//root node is the minimum of a min heap
{

    return arr[0].value;
}











int Heap::Pop()
{
    if(size<=0)
        cout<<"There is no element in the heap to delete."<<endl;
    else
    {
        int x=arr[0].pos;
        Swap(arr[0],arr[size-1]);
        size--;
        Sift_Down(0);
        return x;
    }
}








void Heap::Decrease_key(int i, int key)
{
    if(key>arr[i].value)
        cout<<"New key is greater than current key"<<endl;

    else
    {
        arr[i].value=key;
        Sift_Up(i);

    }

}





void Heap::Sift_Up(int l)
{
    int i=l;

    /* for(int i=(l-2)/2 ; i>=0 ; i--)
      {
          //cout<<i;
          Max_heapify(arr,i);

      }*/


    while(i!=0 && (arr[parent(i)].value>arr[i].value) )
    {
        Swap(arr[parent(i)],arr[i]);
        i=parent(i);
    }







}






void Heap::Sift_Down(int i )
{
    Min_heapify(arr,i);
}





class ArrayList
{

    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    int * list;
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
    //Stack s;

    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:

    bool directed ;
    Graph(bool dir );
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void Dijkstra(int **Weight , int nVertice , int source);
    void printGraph();

};


 Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ;


     //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;

}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    if(!directed) adjList[v].insertItem(u) ;
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




void Graph:: Dijkstra(int **Weight , int nVertice , int source)
{
    int dist[nVertice] , prev[nVertice] , u ,v , position ;
    Heap pq(nVertice);


    for(int i=0 ; i<nVertice ; i++)
    {
        dist[i] = INFINITY;
        prev[i] = NULL_VALUE;
    }


    dist[source] = 0;
    pq.Build_Heap(dist,nVertice);
    //pq.print();



   while(!pq.is_empty())
    {
        u=pq.Pop();
        //cout<<u<<endl;
        int x= adjList[u].getLength();
       // cout<<x<<endl;

        for(int y=0 ; y<x ;y++)
        {
            v=adjList[u].getItem(y);
            //cout<<v<<endl;

            if(dist[v]>(dist[u]+Weight[u][v]))
            {
                dist[v]=dist[u]+Weight[u][v];
                //cout<<dist[v]<<endl;
                prev[v]=u;


                for(int k=0;k<pq.Heap_Size();k++)
                {
                    if(pq.getItemAt(k).pos==v)
                      {
                            position=k;
                      //  cout<<"position "<<position<<endl;
                        break;
                      }
                }
                pq.Decrease_key(position,dist[v]);
            }
        }
      // output[count++]=pq.Pop();

    }

    ofstream fOutput("output.txt");
    fOutput<<"Distance      Parent"<<endl;

    for(int i=0;i<nVertice;i++)
    {
        fOutput<<dist[i]<<"             "<<prev[i]<<endl;
    }



}

















int main()
{
    int u ,v ,n=6 ,s ,**weight ,w ,a ,e;
    Graph G(false);


    cout<<"Press 1 if the graph is directed else press 2."<<endl;
    cin>>a;

    if(a==1)
         G.directed=true;

    else G.directed=false;

    ifstream fInput("input.txt");

    fInput>>n;
    G.setnVertices(n);


    fInput>>s;


    weight = new int*[n];
    for(int i=0;i<n;i++)
    {
        weight[i] = new int[n];
        //for(int j=0;j<n;j++)
          //  weight[i][j] = 0; //initialize the matrix cells to 0
    }



    //cout<<"Enter the edges and the weights: "<<endl;
    while(fInput>>u>>v>>w)
    {
        G.addEdge(u,v);
        weight[u][v]=w;

        if(!G.directed)
            weight[v][u]=w;
    }






  G.Dijkstra(weight,n,s);

   fInput.close();







    return 0;
}
