#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two numbers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choosing last element as pivot
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to generate random numbers
void generateRandomNumbers(int arr[], int n) {
    srand(time(0)); // Seed for random numbers
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // Random numbers between 0-999
    }
}

// Function to read numbers from a file
int readFromFile(int arr[], int n) {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &arr[i]) != 1) {
            printf("Error reading data!\n");
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n, choice;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Choose input method:\n");
    printf("1. Generate Random Numbers\n");
    printf("2. Read from File (input.txt)\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        generateRandomNumbers(arr, n);
    } else if (choice == 2) {
        if (!readFromFile(arr, n)) {
            return 1;
        }
    } else {
        printf("Invalid choice! Exiting...\n");
        return 1;
    }

    printf("Original Array:\n");
    printArray(arr, n);

    // Measure sorting time
    clock_t start = clock();
    quickSort(arr, 0, n - 1);
    clock_t end = clock();

    printf("Sorted Array:\n");
    printArray(arr, n);

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for sorting: %f seconds\n", time_taken);

    return 0;
}
