#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <limits.h>
#include <random>

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

void add_edge(Graph &g, int u, int v)
{
    if (u < 0 || u >= g.num_of_nodes || v < 0 || v >= g.num_of_nodes)
    {
        cerr << "Error: invalid node number\n";
        return;
    }
    g.adj_matrix[u][v] = 1;
    g.adj_matrix[v][u] = 1;
}

int main()
{
    int cnt = 3;
    while (cnt--)
    {
        const int SIZE = sizeof(Graph) + MAX_NODES * MAX_NODES * sizeof(int);
        const key_t KEY = 1234;

        int shm_id = shmget(KEY, SIZE, 0666);
        if (shm_id < 0)
        {
            cerr << "Error: cannot access shared memory\n";
            return -1;
        }
        void *ptr = shmat(shm_id, NULL, 0);
        if (ptr == (void *)-1)
        {
            cerr << "Error: cannot map shared memory\n";
            return -1;
        }

        Graph *g = static_cast<Graph *>(ptr);
        cout << g->num_of_nodes << endl;

        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<> dist_m(10, 30);
        int m = dist_m(gen);

        for (int i = 0; i < m; i++)
        {
            g->num_of_nodes++;
            uniform_int_distribution<> dist_k(1, 20);
            int k = dist_k(gen);
            for (int j = 0; j < k; j++)
            {
                uniform_int_distribution<> dist_k(0, g->num_of_nodes - 2);
                int coord = dist_k(gen);
                add_edge(*g, g->num_of_nodes - 1, coord);
            }
        }

        ofstream outfile;
        outfile.open("Adj_list.txt", ios::out | ios::trunc);

        for (int i = 0; i < g->num_of_nodes; i++)
        {
            outfile << i << " --> ";
            for (int j = 0; j < g->num_of_nodes; j++)
            {
                if (g->adj_matrix[i][j])
                    outfile << j << " ";
            }
            outfile << endl;
        }

        shmdt(ptr);
        // sleep(50);
    }

    return 0;
}
