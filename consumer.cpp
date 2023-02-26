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

void dikstra(graph *g, int i)
{
    
}

int main()
{
    for (int i = 0; i < 10; i++)
    {
        if (fork() == 0)
        {
            while (1)
            {
                graph *g;
                dikstra(g, );
                sleep(30);
            }
        }
    }
}