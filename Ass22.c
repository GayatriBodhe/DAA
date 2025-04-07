#include <stdio.h>
#include <string.h>

// Function to find and print LCS
void findLCS(char *X, char *Y, int m, int n) {
    int L[m + 1][n + 1];

    // Build LCS table in bottom-up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }

    
    // Length of LCS
    int index = L[m][n];
    char lcs[index + 1];
    lcs[index] = '\0'; // Null termination

    // Tracing back the LCS from table
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1]; // Store character in LCS
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    // Printing LCS and its length
    printf("Length of Longest Common Subsequence: %d\n", L[m][n]);
    printf("Longest Common Subsequence: %s\n", lcs);
    printf("LCS String Length: %ld\n", strlen(lcs));
}

// Main function
int main() {
    char X[100], Y[100];

    // Taking user input
    printf("Enter first sequence: ");
    scanf("%s", X);
    printf("Enter second sequence: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    // Finding LCS
    findLCS(X, Y, m, n);
    return 0;
}
