#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

struct MinHeap {
    int size;
    int array[MAX_SIZE];
};

// Function to create a Min Heap
struct MinHeap* createMinHeap() {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    return minHeap;
}

// Function to swap two elements in the heap
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to maintain the heap property from child to parent (Bubble Up)
void heapifyUp(struct MinHeap* minHeap, int idx) {
    if (idx && minHeap->array[idx] < minHeap->array[(idx - 1) / 2]) {
        swap(&minHeap->array[idx], &minHeap->array[(idx - 1) / 2]);
        heapifyUp(minHeap, (idx - 1) / 2);
    }
}

// Function to insert a new element into the heap
void insertMinHeap(struct MinHeap* minHeap, int value) {
    if (minHeap->size == MAX_SIZE) {
        printf("Heap overflow\n");
        return;
    }
    minHeap->size++;
    int idx = minHeap->size - 1;
    minHeap->array[idx] = value;

    // Heapify up from the inserted position
    heapifyUp(minHeap, idx);
}

// Function to heapify down from a node to its children
void heapifyDown(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left] < minHeap->array[smallest])
        smallest = left;

    if (right < minHeap->size && minHeap->array[right] < minHeap->array[smallest])
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->array[idx], &minHeap->array[smallest]);
        heapifyDown(minHeap, smallest);
    }
}

// Function to delete a specific value from the heap
void deleteNode(struct MinHeap* minHeap, int value) {
    int idx;
    // Find the index of the value to delete
    for (idx = 0; idx < minHeap->size; idx++) {
        if (minHeap->array[idx] == value)
            break;
    }

    if (idx == minHeap->size) {
        printf("Element not found in the heap\n");
        return;
    }

    // Replace the node to be deleted with the last element in the heap
    minHeap->array[idx] = minHeap->array[minHeap->size - 1];
    minHeap->size--;

    // Heapify down from the replaced node
    heapifyDown(minHeap, idx);
}

// Function to print the heap in level-order
void printHeap(struct MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->array[i]);
    }
    printf("\n");
}

// Main function to execute the series of commands
int main() {
    struct MinHeap* minHeap = createMinHeap();

    char command[10];
    int value;

    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "insert") == 0) {
            scanf("%d", &value);
            insertMinHeap(minHeap, value);
        } else if (strcmp(command, "delete") == 0) {
            scanf("%d", &value);
            deleteNode(minHeap, value);
        }
    }

    // Print the final state of the heap in level-order
    printHeap(minHeap);

    return 0;
}
