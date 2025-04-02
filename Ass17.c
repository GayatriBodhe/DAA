#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int graph[MAX][MAX], V, colors[MAX];

// Check if color assignment is safe
bool isSafe(int v, int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && colors[i] == c)
            return false;
    return true;
}

// Utility function for Graph Coloring
bool graphColoringUtil(int m, int v) {
    if (v == V)
        return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            colors[v] = c;
            if (graphColoringUtil(m, v + 1))
                return true;
            colors[v] = 0; // Backtrack
        }
    }
    return false;
}

// Function to solve Graph Coloring
bool graphColoring(int m) {
    for (int i = 0; i < V; i++)
        colors[i] = 0;

    if (!graphColoringUtil(m, 0)) {
        printf("Solution does not exist.\n");
        return false;
    }

    printf("Vertex Coloring:\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d → Color %d\n", i, colors[i]);
    
    return true;
}

int main() {
    int edges, u, v, m;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    printf("Enter number of colors: ");
    scanf("%d", &m);

    graphColoring(m);
    return 0;
}
