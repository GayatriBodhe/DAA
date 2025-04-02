#include <stdio.h>

// Structure to store item details
struct Item {
    int weight;
    int profit;
    float ratio;
};

// Function to swap two items
void swap(struct Item *a, struct Item *b) {
    struct Item temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort items by decreasing profit/weight ratio
void sortItems(struct Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (items[j].ratio < items[j + 1].ratio) {
                swap(&items[j], &items[j + 1]);
            }
        }
    }
}

// Function to solve the fractional knapsack problem
float knapsack(int capacity, struct Item items[], int n) {
    float totalProfit = 0.0;
    int currentWeight = 0;

    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            // Take full item
            totalProfit += items[i].profit;
            currentWeight += items[i].weight;
        } else {
            // Take fractional part of item
            int remaining = capacity - currentWeight;
            totalProfit += items[i].ratio * remaining;
            break;
        }
    }

    return totalProfit;
}

int main() {
    int n, capacity;
    printf("Enter number of items: ");
    scanf("%d", &n);
    
    struct Item items[n];

    printf("Enter weight and profit of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d %d", &items[i].weight, &items[i].profit);
        items[i].ratio = (float)items[i].profit / items[i].weight;
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    // Sort items by profit/weight ratio
    sortItems(items, n);

    float maxProfit = knapsack(capacity, items, n);
    printf("Maximum profit: %.2f\n", maxProfit);

    return 0;
}
