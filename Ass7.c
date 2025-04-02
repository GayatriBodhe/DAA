#include <stdio.h>
#include <limits.h>

#define MAX 100 // Maximum number of vertices

int minDistance(int dist[], int visited[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[MAX][MAX], int src, int V) {
    int dist[V];     // Stores the shortest distances from the source
    int visited[V];  // Keeps track of visited vertices

    // Initialize all distances to infinity and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance to source itself is 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = 1;

        // Update distance of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print shortest distances
    printf("Vertex\t Distance from Source %d\n", src);
    for (int i = 0; i < V; i++) {
        printf("%d\t %d\n", i, dist[i]);
    }
}

int main() {
    int V, E, src;
    int graph[MAX][MAX] = {0};

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    printf("Enter edges in format: src dest weight\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w; // Comment this for a directed graph
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, src, V);

    return 0;
}
