#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

class graph
{
public:
    int nodes;
    vector<vector<int>> adj_list;

    // Constructor
    graph(int nodes)
    {
        this->nodes = nodes;
        this->adj_list.clear();
        this->adj_list.resize(nodes);
    }
    // Function to insert edges in graph
    void insert_edge(int x, int y)
    {
        adj_list[x].push_back(y);
        adj_list[y].push_back(x);
    }
};

int NO_PARENT = -1;

// Function to print shortest path
// from source to currentVertex
// using parents array
void printPath(int currentVertex, vector<int> parents)
{

    // Base case : Source node has
    // been processed
    if (currentVertex == NO_PARENT)
    {
        return;
    }
    printPath(parents[currentVertex], parents);
    cout << currentVertex << " ";
}

// A utility function to print
// the constructed distances
// array and shortest paths
void printSolution(int startVertex, vector<int> distances,
                   vector<int> parents)
{
    int nVertices = distances.size();
    cout << "Vertex\t Distance\tPath";

    for (int vertexIndex = 0; vertexIndex < nVertices;
         vertexIndex++)
    {
        if (vertexIndex != startVertex)
        {
            cout << "\n"
                 << startVertex << " -> ";
            cout << vertexIndex << " \t\t ";
            cout << distances[vertexIndex] << "\t\t";
            printPath(vertexIndex, parents);
        }
    }
}

void dijkstra(vector<vector<int>> adjacencyMatrix, int startVertex)
{
    int nVertices = adjacencyMatrix[0].size();

    // shortestDistances[i] will hold the
    // shortest distance from src to i
    vector<int> shortestDistances(nVertices);

    // added[i] will true if vertex i is
    // included / in shortest path tree
    // or shortest distance from src to
    // i is finalized
    vector<bool> added(nVertices);

    // Initialize all distances as
    // INFINITE and added[] as false
    for (int vertexIndex = 0; vertexIndex < nVertices;
         vertexIndex++)
    {
        shortestDistances[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;
    }

    // Distance of source vertex from
    // itself is always 0
    shortestDistances[startVertex] = 0;

    // Parent array to store shortest
    // path tree
    vector<int> parents(nVertices);

    // The starting vertex does not
    // have a parent
    parents[startVertex] = NO_PARENT;

    // Find shortest path for all
    // vertices
    for (int i = 1; i < nVertices; i++)
    {

        // Pick the minimum distance vertex
        // from the set of vertices not yet
        // processed. nearestVertex is
        // always equal to startNode in
        // first iteration.
        int nearestVertex = -1;
        int shortestDistance = INT_MAX;
        for (int vertexIndex = 0; vertexIndex < nVertices;
             vertexIndex++)
        {
            if (!added[vertexIndex] && shortestDistances[vertexIndex] < shortestDistance)
            {
                nearestVertex = vertexIndex;
                shortestDistance = shortestDistances[vertexIndex];
            }
        }

        // Mark the picked vertex as
        // processed
        added[nearestVertex] = true;

        // Update dist value of the
        // adjacent vertices of the
        // picked vertex.
        for (int vertexIndex = 0; vertexIndex < nVertices;
             vertexIndex++)
        {
            int edgeDistance = adjacencyMatrix[nearestVertex][vertexIndex];

            if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortestDistances[vertexIndex]))
            {
                parents[vertexIndex] = nearestVertex;
                shortestDistances[vertexIndex] = shortestDistance + edgeDistance;
            }
        }
    }

    printSolution(startVertex, shortestDistances, parents);
}

void findPath(int i, vector<int> &parent, string &s)
{
    if(i == -1)
    {
        return;
    }
    findPath(parent[i], parent, s);
    s += to_string(i);
    s += " ";
}

void storePathUtility(vector<int> &sources, vector<int> &parent)
{
    for (int i = 0; i < parent.size(); i++)
    {
        int flag = 0;
        for (auto x : src)
        {
            if (i == x)
            {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            continue;
        }
        string s;
        findPath(i, parent, s);
    }
}

vector<int> dikstra(graph *g, int src)
{
    vector<int> dist(g->nodes, INT_MAX);
    vector<bool> finalised(g->nodes, false);
    dist[0] = 0;
    vector<int> parentArray(g->nodes);
    parentArray[src] = -1;

    for (int cnt = 0; cnt < g->nodes - 1; cnt++)
    {
        int u = -1;
        for (int i = 0; i < g->nodes; i++)
        {
            if (!finalised[i] && (u == -1 || dist[i] < dist[u]))
            {
                u = i;
            }
        }
        finalised[u] = true;
    }

    for (auto v : g->adj_list[u])
    {
        if (!finalised[v] && (dist[u] + 1) < dist[v])
        {
            parentArray[v] = u;
            dist[v] = dist[u] + 1;
        }
    }

    storePathUtility(src, parentArray);
}

int main()
{
    for (int i = 0; i < 10; i++)
    {
        if (fork() == 0)
        {
            while (1)
            {
                vactor<int> v;
                graph *g;
                int x = g->nodes / 10;
                for (int j = 0; j < x; j++)
                {
                    v = dikstra(g, i * x + j);
                }
                if (i == 9)
                {
                    for (int j = (i + 1) * x; j < g->nodes; j++)
                    {
                        v = dikstra(g, j);
                    }
                }
                sleep(30);
            }
        }
    }
}