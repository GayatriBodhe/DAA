#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int graph[MAX][MAX], path[MAX], V;

// Check if vertex `v` can be added to cycle
bool isSafe(int v, int pos) {
    if (graph[path[pos - 1]][v] == 0)
        return false;

    for (int i = 0; i < pos; i++) {
        if (path[i] == v)
            return false;
    }
    return true;
}

// Recursive function to solve Hamiltonian Cycle
bool hamiltonianCycleUtil(int pos) {
    if (pos == V) {
        return graph[path[pos - 1]][path[0]] == 1;
    }

    for (int v = 1; v < V; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamiltonianCycleUtil(pos + 1))
                return true;
            path[pos] = -1;
        }
    }
    return false;
}

// Function to check for Hamiltonian Cycle
bool hamiltonianCycle() {
    for (int i = 0; i < V; i++)
        path[i] = -1;

    path[0] = 0;
    return hamiltonianCycleUtil(1);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &graph[i][j]);

    if (hamiltonianCycle())
        printf("Graph contains a Hamiltonian Cycle\n");
    else
        printf("Graph does not contain a Hamiltonian Cycle\n");

    return 0;
}
