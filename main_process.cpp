#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

// Class for Graphs
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

int main()
{
    int x, y;

    const char *shared_mem = "/my_shm";
    int shmFD = shm_open(shared_mem, O_CREAT | O_RDWR, 0666);
    int num_nodes = 4039;
    graph *GRAPH = new graph(num_nodes);

    // For reading and writing to files
    fstream infile;
    ofstream outfile;
    infile.open("facebook_combined.txt");
    outfile.open("Adj_list.txt", ios::out | ios::trunc);

    while (infile >> x >> y)
    {
        GRAPH->insert_edge(x, y);
    }

    // Writing the graph to the shared memory created above by the name "shared_mem"
    ftruncate(shmFD, sizeof(graph));
    void *ptr_to_shm = mmap(0, sizeof(graph), PROT_WRITE, MAP_SHARED, shmFD, 0);

    graph *shared_graph = new (ptr_to_shm) graph(num_nodes);

    // copying the graph
    for (int i = 0; i < num_nodes; i++)
    {
        shared_graph->adj_list[i].resize(GRAPH->adj_list[i].size());
        shared_graph->adj_list[i] = GRAPH->adj_list[i];
    }
    delete GRAPH;

    ptr_to_shm = mmap(0, sizeof(graph), PROT_READ, MAP_SHARED, shmFD, 0);
    graph *GRAPH2 = (graph *)ptr_to_shm;

    // Printing The graph
    for (int i = 0; i < num_nodes; i++)
    {
        outfile << i << " --> ";
        for (int j = 0; j < GRAPH2->adj_list[i].size(); j++)
        {
            outfile << GRAPH2->adj_list[i][j] << " ";
        }
        outfile << endl;
    }

    munmap(ptr_to_shm, sizeof(graph));
    shm_unlink(shared_mem);
    return 0;
}
