#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to merge two sorted halves of an array
void merge(int arr[], int left, int mid, int right) {
    // Calculate sizes of two subarrays
    int n1 = mid - left + 1;  // Size of left subarray
    int n2 = right - mid;      // Size of right subarray

    // Create temporary arrays to store left and right subarrays
    int L[n1], R[n2];

    // Copy elements into left subarray
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];  

    // Copy elements into right subarray
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the two sorted subarrays back into the main array
    int i = 0, j = 0, k = left;  // Initialize indices for L[], R[], and arr[]
    
    while (i < n1 && j < n2) { // Compare elements of L[] and R[]
        if (L[i] <= R[j]) {  // If L[i] is smaller, put it in arr[]
            arr[k] = L[i];
            i++;  // Move to next element in L[]
        } else {  // If R[j] is smaller, put it in arr[]
            arr[k] = R[j];
            j++;  // Move to next element in R[]
        }
        k++;  // Move to the next position in arr[]
    }

    // Copy any remaining elements of L[] (if any)
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy any remaining elements of R[] (if any)
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Function to generate random numbers
void generateRandomNumbers(int arr[], int n) {
    srand(time(0)); 
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
    mergeSort(arr, 0, n - 1);
    clock_t end = clock();

    printf("Sorted Array:\n");
    printArray(arr, n);

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for sorting: %f seconds\n", time_taken);

    return 0;
}
