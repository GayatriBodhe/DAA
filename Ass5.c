#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Function to create a graph
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Comparator function for sorting edges based on weight
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Find function (using path compression)
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return parent[i] = find(parent, parent[i]);
}

// Union function (using union by rank)
void unionSet(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Function to implement Kruskal's algorithm
void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V]; // Stores the MST
    int parent[V];
    int rank[V];
    int e = 0; // Count of edges in MST
    int i = 0; // Index for sorted edges

    // Initialize parent and rank arrays
    for (int v = 0; v < V; v++) {
        parent[v] = -1;
        rank[v] = 0;
    }

    // Sort edges in increasing order of weight
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    // Process edges and construct MST
    while (e < V - 1 && i < graph->E) {
        struct Edge nextEdge = graph->edges[i++];
        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        // If including this edge doesn't create a cycle, add it to MST
        if (x != y) {
            result[e++] = nextEdge;
            unionSet(parent, rank, x, y);
        }
    }

    // Print the MST
    printf("Edges in Minimum Cost Spanning Tree:\n");
    int minCost = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minCost += result[i].weight;
    }
    printf("Minimum Cost: %d\n", minCost);
}

// Driver function
int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    struct Graph* graph = createGraph(V, E);

    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }

    kruskalMST(graph);

    free(graph->edges);
    free(graph);
    return 0;
}
