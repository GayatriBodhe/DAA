#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Swap function for sorting
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Selection Sort (O(n^2))
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(&arr[minIdx], &arr[i]);
    }
}

// Insertion Sort (O(n^2))
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Heapify function for Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i;            // Assume the root is the largest element
    int left = 2 * i + 1;       // Left child index
    int right = 2 * i + 2;      // Right child index

    // If left child exists and is greater than root, update largest
    if (left < n && arr[left] > arr[largest]) 
        largest = left;

    // If right child exists and is greater than the current largest, update largest
    if (right < n && arr[right] > arr[largest]) 
        largest = right;

    // If the largest is not the root, swap and heapify the affected subtree
    if (largest != i) {
        swap(&arr[i], &arr[largest]); // Swap root with the largest
        heapify(arr, n, largest);     // Recursively heapify the affected subtree
    }
}


// Heap Sort (O(n log n))
void heapSort(int arr[], int n) {
    // Step 1: Build a Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    // Step 2: Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);  // Swap root (max element) with last element
        heapify(arr, i, 0);      // Restore heap property in the reduced heap
    }
}


// Function to get the maximum value in an array
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}

// Counting sort used for Radix Sort
void countingSort(int arr[], int n, int exp) {
    int output[n], count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Radix Sort (O(nk))
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}

// Function to copy an array
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = source[i];
}

// Function to display an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Function to calculate and display sorting time
void measureSortingTime(void (*sortFunction)(int[], int), int arr[], int n, const char *sortName) {
    int tempArr[n];
    copyArray(arr, tempArr, n);

    clock_t start = clock();
    sortFunction(tempArr, n);
    clock_t end = clock();

    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%s took %.6f seconds.\n", sortName, timeTaken);
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nSorting times:\n");
    measureSortingTime(selectionSort, arr, n, "Selection Sort (O(n^2))");
    measureSortingTime(insertionSort, arr, n, "Insertion Sort (O(n^2))");
    measureSortingTime(heapSort, arr, n, "Heap Sort (O(n log n))");
    measureSortingTime(radixSort, arr, n, "Radix Sort (O(nk))");

    // Sorting using Heap Sort to get sorted array for display
    int sortedArr[n];
    copyArray(arr, sortedArr, n);
    heapSort(sortedArr, n);

    // Print the sorted array only once
    printf("\nFinal Sorted Array: ");
    printArray(sortedArr, n);

    return 0;
}
