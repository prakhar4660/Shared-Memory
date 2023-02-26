#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <limits.h>
#include <sys/wait.h>

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
    const int SIZE = sizeof(Graph) + MAX_NODES * MAX_NODES * sizeof(int);
    const key_t KEY = 1234;
    int num_nodes = 4039;

    int shm_id = shmget(KEY, SIZE, IPC_CREAT | 0666);
    if (shm_id < 0)
    {
        cerr << "Error: cannot create shared memory\n";
        return -1;
    }

    void *shared_ptr = shmat(shm_id, NULL, 0);
    if (shared_ptr == (void *)-1)
    {
        cerr << "Error: cannot map shared memory\n";
        return -1;
    }

    Graph *g = new (shared_ptr) Graph(num_nodes);

    fstream infile;
    int x, y;
    infile.open("facebook_combined.txt");

    while (infile >> x >> y)
    {
        add_edge(*g, x, y);
    }

    int fd = fork();
    if (fd == 0)
    {
        execl("producer", "./producer", NULL);
    }
    wait(NULL);

    void *ptr = shmat(shm_id, NULL, 0);
    if (ptr == (void *)-1)
    {
        cerr << "Error: cannot map shared memory\n";
        return -1;
    }

    Graph *gp = static_cast<Graph *>(ptr);
    cout << gp->num_of_nodes << endl;

    shmdt(shared_ptr);
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}
