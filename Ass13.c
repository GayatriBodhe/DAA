#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int graph[MAX][MAX], visited[MAX], queue[MAX], front = -1, rear = -1;

// Function for DFS
void DFS(int vertex, int n) {
    printf("%d ", vertex);
    visited[vertex] = 1;
    
    for (int i = 0; i < n; i++) {
        if (graph[vertex][i] == 1 && visited[i] == 0)
            DFS(i, n);
    }
}

// Function for BFS
void BFS(int start, int n) {
    front = rear = 0;
    queue[rear] = start;
    visited[start] = 1;

    while (front <= rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && visited[i] == 0) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int n, edges, u, v, start;
    
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    // Read edges
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; // Assuming undirected graph
    }

    printf("Enter starting vertex for DFS & BFS: ");
    scanf("%d", &start);

    // DFS
    printf("\nDFS Traversal: ");
    for (int i = 0; i < n; i++) visited[i] = 0;
    DFS(start, n);

    // BFS
    printf("\nBFS Traversal: ");
    for (int i = 0; i < n; i++) visited[i] = 0;
    BFS(start, n);

    return 0;
}
