#include<bits/stdc++.h>

using namespace std;



class Graph
{
    int V;
    int E;
    int *degree;    // No. of vertices
    list<int> *adj;  // Pointer to an array containing adjacency lists
public:
    Graph(int V,int E);  // Constructor
    void addEdge(int v, int w); // function to add an edge to graph
    void printVertexCover();  // prints vertex cover
};

Graph::Graph(int V,int E)
{
    this->V = V;
    this->E= E;
    degree=new int[V];
    for(int i=0;i<V;i++)
    {
        degree[i]=0;
    }
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v);
    degree[v]++;
    degree[w]++; // Since the graph is undirected
}

// The function to print vertex cover
void Graph::printVertexCover()
{
    // Initialize all vertices as not visited.
    int u;
    bool visited[V];
    bool alreadyChosen[V];
    for (int i=0; i<V; i++)
        {
            visited[i] = false;
            alreadyChosen[i] = false;
        }

    list<int>::iterator i;


    // Consider all edges one by one
    for (int j=0; j<V; j++)
    {
        for(int k=0;k<V;k++)
        {
            u=rand()%V;
            if(alreadyChosen[u]==false)
            {
                alreadyChosen[u]==true;
                break;
            }

        }


        // An edge is only picked when both visited[u] and visited[v]
        // are false
        if (visited[u] == false)
        {
            // Go through all adjacents of u and pick the first not
            // yet visited vertex (We are basically picking an edge
            // (u, v) from remaining edges.
            for (i= adj[u].begin(); i != adj[u].end(); ++i)
            {
                int v = *i;
                if (visited[v] == false)
                {
                     // Add the vertices (u, v) to the result set.
                     // We make the vertex u and v visited so that
                     // all edges from/to them would be ignored
                     visited[v] = true;
                     visited[u]  = true;
                     break;
                }
            }
        }
    }

    // Print the vertex cover
    for (int i=0; i<V; i++)
        if (visited[i])
          cout << i << " ";
}

// Driver program to test methods of graph class
int main()
{
    // Create a graph given in the above diagram
    Graph g(7,6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);

    g.printVertexCover();

    return 0;
}
