#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

// struct Graph
// {
//     int num_of_nodes;
//     int adj_matrix[MAX_NODES][MAX_NODES];

//     Graph(int n)
//     {
//         num_of_nodes = n;
//         memset(adj_matrix, 0, sizeof(adj_matrix));
//     }
// };

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

void findPath(int i, vector<int> &parent, string &s)
{
    if (i == -1)
    {
        return;
    }
    findPath(parent[i], parent, s);
    s += to_string(i);
    s += " ";
}

void storePathUtility(vector<int> &sources, vector<int> &parent, int consumerNum)
{
    ofstream file;
    string outputFilename = "output_" + to_string(consumerId) + ".txt";
    file.open(outputFilename, ios::app);
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
        file >> s >> endl;
    }
}

vector<int> dikstra(graph *g, int src, int consumerNum)
{
    vector<int> dist(g->nodes, INT_MAX);
    vector<bool> finalised(g->nodes, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<int, int>> pq;
    dist[src] = 0;
    pq.push(make_pair(0, src));
    vector<int> parentArray(g->nodes);
    parentArray[src] = -1;

    for (int cnt = 0; cnt < g->nodes - 1; cnt++)
    {
        int u = pq.top().second;
        pq.pop();
        finalised[u] = true;

        for (auto v : g->adj_list[u])
        {
            if (!finalised[v] && (dist[u] + 1) < dist[v])
            {
                parentArray[v] = u;
                dist[v] = dist[u] + 1;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    storePathUtility(src, parentArray, consumerNum);
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
                    v = dikstra(g, i * x + j, i + 1);
                }
                if (i == 9)
                {
                    for (int j = (i + 1) * x; j < g->nodes; j++)
                    {
                        v = dikstra(g, j, i + 1);
                    }
                }
                sleep(30);
            }
        }
    }
}