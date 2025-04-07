// Topological Sorting using DFS
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX], visited[MAX], stack[MAX], top = -1;
int V;

// Function for DFS-based Topological Sort
void topologicalSortUtil(int v) {
    visited[v] = 1;
    
    for (int i = 0; i < V; i++) {
        if (graph[v][i] == 1 && !visited[i]) {
            topologicalSortUtil(i);
        }
    }
    
    stack[++top] = v; // Push to stack
}

// Function to perform Topological Sorting
void topologicalSort() {
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            topologicalSortUtil(i);
    }

    // Print topological order
    printf("Topological Sorting Order: ");
    while (top >= 0) {
        printf("%d ", stack[top--]);
    }
    printf("\n");
}

int main() {
    int edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // Initialize adjacency matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1; // Directed edge u → v
    }

    topologicalSort();
    return 0;
}
