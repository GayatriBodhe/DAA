#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

// Adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX];
int visited[MAX], stack[MAX], top = -1;
int V;

// Create a new node
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Add edge to adjacency list
void addEdge(int u, int v) {
    Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

// DFS utility for Topological Sort
void topologicalSortUtil(int v) {
    visited[v] = 1;

    Node* temp = adjList[v];
    while (temp) {
        if (!visited[temp->vertex])
            topologicalSortUtil(temp->vertex);
        temp = temp->next;
    }

    stack[++top] = v; // Push to stack
}

// Perform Topological Sort
void topologicalSort() {
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            topologicalSortUtil(i);
    }

    printf("Topological Sorting Order: ");
    while (top >= 0)
        printf("%d ", stack[top--] + 1); // 1-based indexing
    printf("\n");
}

int main() {
    int edges, u, v;
    clock_t start, end;
    double cpu_time_used;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // Initialize adjacency list
    for (int i = 0; i < V; i++) {
        adjList[i] = NULL;
        visited[i] = 0;
    }

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u - 1, v - 1); // 0-based indexing
    }

    // Start timer
    start = clock();

    topologicalSort();

    // End timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Show time complexity and execution time
    printf("\nTime Complexity (Adjacency List): O(V + E)\n");
    printf("Execution Time: %.6f seconds\n", cpu_time_used);

    return 0;
}
