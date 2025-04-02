#include <stdio.h>
#include <limits.h>

// Function to calculate sum of frequencies from i to j
int sum(int freq[], int i, int j) {
    int s = 0;
    for (int k = i; k <= j; k++)
        s += freq[k];
    return s;
}

// Function to construct an optimal BST
int optimalBST(int keys[], int freq[], int n) {
    int cost[n][n];

    // Initialize diagonal elements where i == j (single node trees)
    for (int i = 0; i < n; i++)
        cost[i][i] = freq[i];

    // Chain length L varies from 2 to n
    for (int L = 2; L <= n; L++) {
        for (int i = 0; i <= n - L; i++) {
            int j = i + L - 1;
            cost[i][j] = INT_MAX;

            // Try making each key in range [i, j] as root
            for (int r = i; r <= j; r++) {
                int leftCost = (r > i) ? cost[i][r - 1] : 0;
                int rightCost = (r < j) ? cost[r + 1][j] : 0;
                int totalCost = leftCost + rightCost + sum(freq, i, j);

                if (totalCost < cost[i][j])
                    cost[i][j] = totalCost;
            }
        }
    }

    return cost[0][n - 1]; // The minimum search cost of OBST
}

int main() {
    int n;
    printf("Enter number of keys: ");
    scanf("%d", &n);

    int keys[n], freq[n];

    printf("Enter keys: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &keys[i]);

    printf("Enter frequencies: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &freq[i]);

    int minCost = optimalBST(keys, freq, n);
    printf("Minimum cost of Optimal BST: %d\n", minCost);

    return 0;
}
