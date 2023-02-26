#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

const int MAX_NODES = 10000;

struct Graph
{
    int num_of_nodes;
    int adj_matrix[MAX_NODES][MAX_NODES];

    Graph(int n)
    {
        num_of_nodes = n;
        memset(adj_matrix, 0, sizeof(adj_matrix));
    }
};

void dikstra(Graph *g, int i)
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
                Graph *g;
                dikstra(g, 6);
                sleep(30);
            }
        }
    }
}