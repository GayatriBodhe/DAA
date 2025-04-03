//4. Find LCS for input sequences “AGGTAB” and “GXTXAYB”
#include <stdio.h>
#include <string.h>

// Function to find the length of LCS
int LCS(char *X, char *Y, int m, int n) {
    int L[m + 1][n + 1];

    // Build LCS table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = 1 + L[i - 1][j - 1];
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }

    return L[m][n]; // Length of LCS
}

// Main function
int main() {
    char X[100], Y[100];

    printf("Enter first string: ");
    scanf("%s", X);
    printf("Enter second string: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    printf("Length of Longest Common Subsequence: %d\n", LCS(X, Y, m, n));
    return 0;
}
