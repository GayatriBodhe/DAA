#include <stdio.h>
#include <stdlib.h>

// Function to add two matrices
void addMatrix(int n, int A[n][n], int B[n][n], int result[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices
void subtractMatrix(int n, int A[n][n], int B[n][n], int result[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];
}

// Strassen's multiplication algorithm
void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0]; // Base case
        return;
    }

    int newSize = n / 2;
    int A11[newSize][newSize], A12[newSize][newSize], A21[newSize][newSize], A22[newSize][newSize];
    int B11[newSize][newSize], B12[newSize][newSize], B21[newSize][newSize], B22[newSize][newSize];
    int C11[newSize][newSize], C12[newSize][newSize], C21[newSize][newSize], C22[newSize][newSize];
    int M1[newSize][newSize], M2[newSize][newSize], M3[newSize][newSize], M4[newSize][newSize], M5[newSize][newSize], M6[newSize][newSize], M7[newSize][newSize];
    int temp1[newSize][newSize], temp2[newSize][newSize];

    // Dividing matrices into 4 sub-matrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculating M1 to M7 using Strassen's formulas
    addMatrix(newSize, A11, A22, temp1);
    addMatrix(newSize, B11, B22, temp2);
    strassen(newSize, temp1, temp2, M1); // M1 = (A11 + A22) * (B11 + B22)

    addMatrix(newSize, A21, A22, temp1);
    strassen(newSize, temp1, B11, M2); // M2 = (A21 + A22) * B11

    subtractMatrix(newSize, B12, B22, temp1);
    strassen(newSize, A11, temp1, M3); // M3 = A11 * (B12 - B22)

    subtractMatrix(newSize, B21, B11, temp1);
    strassen(newSize, A22, temp1, M4); // M4 = A22 * (B21 - B11)

    addMatrix(newSize, A11, A12, temp1);
    strassen(newSize, temp1, B22, M5); // M5 = (A11 + A12) * B22

    subtractMatrix(newSize, A21, A11, temp1);
    addMatrix(newSize, B11, B12, temp2);
    strassen(newSize, temp1, temp2, M6); // M6 = (A21 - A11) * (B11 + B12)

    subtractMatrix(newSize, A12, A22, temp1);
    addMatrix(newSize, B21, B22, temp2);
    strassen(newSize, temp1, temp2, M7); // M7 = (A12 - A22) * (B21 + B22)

    // Computing C matrices
    addMatrix(newSize, M1, M4, temp1);
    subtractMatrix(newSize, temp1, M5, temp2);
    addMatrix(newSize, temp2, M7, C11); // C11 = M1 + M4 - M5 + M7

    addMatrix(newSize, M3, M5, C12); // C12 = M3 + M5

    addMatrix(newSize, M2, M4, C21); // C21 = M2 + M4

    addMatrix(newSize, M1, M3, temp1);
    subtractMatrix(newSize, temp1, M2, temp2);
    addMatrix(newSize, temp2, M6, C22); // C22 = M1 + M3 - M2 + M6

    // Merging C11, C12, C21, and C22 into result matrix C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

// Function to print a matrix
void printMatrix(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

// Main function
int main() {
    int n;

    printf("Enter the size of the matrix (must be power of 2): ");
    scanf("%d", &n);

    int A[n][n], B[n][n], C[n][n];

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    // Applying Strassen's multiplication
    strassen(n, A, B, C);

    printf("Resultant Matrix C after Strassen's Multiplication:\n");
    printMatrix(n, C);

    return 0;
}
