// Traveling Salesman Problem using Nearest Neighbor Heuristic
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 10

int tsp(int graph[MAX][MAX], int n) {
    bool visited[MAX] = {false};
    int min_cost = 0, count = 1, current_city = 0;

    visited[current_city] = true;
    printf("Tour: %d -> ", current_city);

    while (count < n) {
        int nearest = -1, min_distance = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[current_city][j] < min_distance) {
                min_distance = graph[current_city][j];
                nearest = j;
            }
        }

        if (nearest == -1)
            break;

        visited[nearest] = true;
        min_cost += min_distance;
        printf("%d -> ", nearest);
        current_city = nearest;
        count++;
    }

    // Returning to the starting city
    min_cost += graph[current_city][0];
    printf("0\n");

    return min_cost;
}

int main() {
    int n, graph[MAX][MAX];

    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    int cost = tsp(graph, n);
    printf("Minimum Cost: %d\n", cost);

    return 0;
}
