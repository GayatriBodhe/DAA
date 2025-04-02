#include <stdio.h>

#define MAX 10

int n, target, subset[MAX];

// Recursive function to find subsets
void sumOfSubsets(int arr[], int index, int curr_sum) {
    if (curr_sum == target) {
        printf("Subset found: ");
        for (int i = 0; i < index; i++)
            printf("%d ", subset[i]);
        printf("\n");
        return;
    }

    if (index >= n || curr_sum > target)
        return;

    subset[index] = arr[index];
    sumOfSubsets(arr, index + 1, curr_sum + arr[index]);
    sumOfSubsets(arr, index + 1, curr_sum);
}

int main() {
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[MAX];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter target sum: ");
    scanf("%d", &target);

    sumOfSubsets(arr, 0, 0);
    return 0;
}
