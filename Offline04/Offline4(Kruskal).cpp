#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define SUCCESS_VALUE 99998



using namespace std;





class Edge
{
    int sVertex;
    int eVertex;


public:

    int value;

    Edge()
    {
        sVertex=0;
        eVertex=0;
        value=0;
    }

    Edge(int s,int e,int v)
    {
        sVertex=s;
        eVertex=e;
        value=v;
    }

    void setEDGE(int s, int e , int v)
    {
        sVertex=s;
        eVertex=e;
        value=v;
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


class ListNode
{
public:
    int item;
    ListNode * next;
};

class LinkedListWithTail
{


    int length;

public:

    ListNode * list;
    ListNode * tail;


    LinkedListWithTail()
    {
        list = 0;  //initially set to NULL
        tail = 0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    //add required codes to set up tail pointer
    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ;
        if(length==0)
        {
            tail=newNode;
        }//point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;
        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
    int deleteItem(int item)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        if(temp==0)//if the list is empty initially
        {
            printf("You cannot delete from an empty list.\n");
            return NULL_VALUE;
        }
        while (temp != 0)
        {
            if (temp->item == item) break ;
            prev = temp;
            temp = temp->next ; //move to next node
        }
        if (temp == 0)return NULL_VALUE ;//item not found to delete
        if(length==0)//to free the tail pointer when the list gets empty by deleting one by one(Code by me)
        {
            if(tail!=0)
                delete tail;
            return NULL_VALUE;
        }
        if (temp == list) //delete the first node
        {
            list = list->next ;
            free(temp) ;
            length--;
        }
        else
        {//when the last node is deleted,previous node is assigned as the tail pointer(Code by me)
            if(temp->next==0)
            {
                tail=prev;
            }
            prev->next = temp->next ;
            delete temp;
            length--;
        }
        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
    ListNode * searchItem(int item)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) return temp ;
            temp = temp->next ; //move to next node
        }
        return 0 ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printList()
    {
        ListNode * temp, *temp1;
        temp = list;
        temp1=tail;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
       printf("The last item is %d\n\n",tail->item);
        printf("Length: %d\n",getLength());
    }

    //------------write code for the functions below-----------
    int insertLast(int item)
    {
        //write your codes here
        ListNode *newNode= new ListNode();
        newNode->item=item;
        newNode->next=0;
        ListNode *temp;
        temp=list;
        //if the list is empty
        if(temp==0)
        {
            list=newNode;
            free(temp);
            tail=newNode;
            length++;
            return SUCCESS_VALUE;
        }
        //otherwise
        tail->next=newNode;
        tail=newNode;
        length++;
        return SUCCESS_VALUE;
    }

    ListNode * getItemAt(int pos)
    {
         //write your codes here
          ListNode *temp;
         temp=list;
         if(pos>length)
            return 0;
         else
         {
             for(int i=1; i<pos;i++)
             {
                 temp=temp->next;

             }
             return temp;
         }

    }

    int deleteLast()
    {
        //write your codes here
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        if(temp==0)//if the list is empty initially
        {
            printf("You cannot delete from an empty list.\n");
            return NULL_VALUE;
        }
        while (temp->next != 0)
        {
            prev = temp;
            temp = temp->next ; //move to next node
        }
        prev->next = temp->next ;
            delete temp;
            tail=prev;
            length--;
            return SUCCESS_VALUE;
    }
};








/*class node
{
public:
    node()
    {

    }

    int pos;
    int value;
};*/

void Swap(Edge &a, Edge &b)
{
    Edge  temp = a;
    a = b;
    b = temp;
}




class Heap
{
    int size;
    int length;
    Edge *arr;


public:



    Heap(int l)//it will create an empty heap
    {
        size=0;
        length=l+100;
        arr= new Edge[length];
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
   /* node& getItemAt (int i)
    {
        return arr[i];
    }*/

    void Min_heapify( Edge *a, int i);

    void Build_Heap( Edge *a, int len);

    int Heap_Size();

    bool is_empty();

    int Find_Min();

    void Push(int i);

    Edge Pop();

    void Decrease_key(int i, int key);

    void Sift_Up(int l);

    void Sift_Down(int i);

   /* void print()
    {
        // cout<<arr[0]<<endl;
        for(int i=0; i<size; i++)
        {
            cout<<arr[i].pos<<"  "<<arr[i].value<<"->";
        }
        cout<<"\n\n";


    }*/
};




void Heap::Min_heapify( Edge *a, int i)
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










void Heap::Build_Heap(Edge *a, int len )
{
    //arr=new int[len];
    arr=a;
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











Edge Heap::Pop()
{
    if(size<=0)
        cout<<"There is no element in the heap to delete."<<endl;
    else
    {
        Edge x=arr[0];
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
    LinkedListWithTail *cluster;
    Edge *edgeList;
    //Stack s;

    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:

    bool directed ;
    Graph(bool dir );
    ~Graph();
    void setnVertices(int n);
    void setnEdges(int e);
    void addEdge(int u, int v);
    void Kruskal();
   // void Dijkstra(int **Weight , int nVertice , int source);
    void printGraph();

};


 Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    cluster=0;
    edgeList=0;
    directed = dir ;


     //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;

    if(cluster!=0) delete cluster;
    cluster=new LinkedListWithTail[nVertices];

}

void Graph::setnEdges(int e)
{
    this->nEdges =e ;
    if(edgeList!=0) delete[] edgeList ; //delete previous list
    edgeList = new Edge[nEdges] ;



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




void Graph::Kruskal()
{

    int nV,e,u,v,w,i=0;


    ifstream fInput("Kruskal.txt");
    fInput>>nV;
   // cout<<n<<endl;
    setnVertices(nV);

    fInput>>e;
    setnEdges(e);

    cout<<nV<<"  "<<e<<endl;



    Edge *ans=new Edge[nEdges] ;

    int disjoint[nVertices];

    for(int j=0;j<nVertices;j++)
    {
        disjoint[j]=j;
        cluster[j].insertLast(j);
    }






 //cout<<"b4 while "<<endl;
    while(fInput>>u>>v>>w)
    {
        edgeList[i++].setEDGE(u,v,w);

    }

   // cout<<edgeList[0].getsVertice()<<"  "<<edgeList[0].geteVertice();



   Heap H(nEdges);
   H.Build_Heap(edgeList,nEdges);

   //cout<<H.Pop().value<<endl;
   //cout<<H.Pop().value;
   int m,n,count=0,nEdgeCount=0,p,q,r,sum=0;

  while(nEdgeCount<nVertices)
   {
       Edge a=H.Pop();
       m=a.getsVertice();
       n=a.geteVertice();

       if(disjoint[m]!=disjoint[n])
       {
           ans[count++]=a;
           sum=sum+a.value;
           nEdgeCount++;
           if(cluster[disjoint[m]].getLength()>cluster[disjoint[n]].getLength())
           {
               p=disjoint[m];
               q=disjoint[n];
               r=cluster[q].getLength();

               for(int i=0;i<r;i++)
               {
                   cluster[p].insertLast(cluster[q].getItemAt(i)->item);
                   disjoint[cluster[q].getItemAt(i)->item]=p;
               }
               for(int i=0;i<r;i++)
               {
                   cluster[q].deleteLast();
               }





       }

       else
       {
               p=disjoint[m];
               q=disjoint[n];
               r=cluster[p].getLength();

               for(int i=0;i<r;i++)
               {
                   cluster[q].insertLast(cluster[p].getItemAt(i)->item);
                   disjoint[cluster[p].getItemAt(i)->item]=q;
               }
               for(int i=0;i<r;i++)
               {
                   cluster[p].deleteLast();
               }

       }
   }

   }
  // sum=0;

   for(int y=0;y<count;y++)
   {
       cout<<ans[y].getsVertice()<<"   "<<ans[y].geteVertice()<<endl;
      // sum+=ans[y].value;

   }
   cout<<sum;



























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

   // ifstream fInput("BellmanFord.txt");

  //  fInput>>n;
    //cout<<n<<endl;
    //G.setnVertices(n);

    //fInput>>e;
    //G.setnEdges(e);




   // fInput>>s;



    // cout<<"b4 while "<<endl;



//    G.BellmanFord(s);
    //cout<<"bel "<<endl;

 //   fInput.close();
 G.Kruskal();








    return 0;
}
