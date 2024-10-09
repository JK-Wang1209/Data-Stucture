#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Structure to represent a node in the binary tree
struct MinHeapNode {
    int key;
    struct MinHeapNode* left;
    struct MinHeapNode* right;
};

// A structure to represent the Min Heap itself
struct MinHeap {
    struct MinHeapNode* root; // Pointer to the root of the binary tree
    int size;                 // Current number of nodes
};

// Function to create a new node
struct MinHeapNode* createNode(int key) {
    struct MinHeapNode* newNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create an empty Min Heap
struct MinHeap* createMinHeap() {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->root = NULL;
    minHeap->size = 0;
    return minHeap;
}

// Function to swap the data of two nodes
void swap(struct MinHeapNode* a, struct MinHeapNode* b) {
    int temp = a->key;
    a->key = b->key;
    b->key = temp;
}

// Function to maintain the min-heap property (heapify) from a given node
void minHeapify(struct MinHeapNode* node) {
    if (!node) return;
    
    struct MinHeapNode* smallest = node;

    if (node->left && node->left->key < smallest->key)
        smallest = node->left;

    if (node->right && node->right->key < smallest->key)
        smallest = node->right;

    if (smallest != node) {
        swap(node, smallest);
        minHeapify(smallest);
    }
}

// Function to insert a node in the heap
void insertNode(struct MinHeap* minHeap, int key) {
    // Create a new node
    struct MinHeapNode* newNode = createNode(key);

    // If the tree is empty, make the new node the root
    if (!minHeap->root) {
        minHeap->root = newNode;
        minHeap->size = 1;
        return;
    }

    // Perform level-order insertion (BFS) to insert the new node at the correct position
    struct MinHeapNode* queue[minHeap->size + 1];  // Simple queue for BFS
    int front = 0, rear = 0;
    queue[rear++] = minHeap->root;

    while (front < rear) {
        struct MinHeapNode* temp = queue[front++];

        if (!temp->left) {
            temp->left = newNode;
            break;
        } else {
            queue[rear++] = temp->left;
        }

        if (!temp->right) {
            temp->right = newNode;
            break;
        } else {
            queue[rear++] = temp->right;
        }
    }

    // Maintain the heap property
    minHeap->size++;
    minHeapify(minHeap->root);
}

// Function to delete the key from the heap
void deleteNode(struct MinHeap* minHeap, int key) {
    if (!minHeap->root) {
        printf("Heap is empty\n");
        return;
    }

    struct MinHeapNode* queue[minHeap->size];  // Simple queue for BFS
    struct MinHeapNode* lastNode = NULL;
    struct MinHeapNode* nodeToDelete = NULL;
    struct MinHeapNode* parent = NULL;
    int front = 0, rear = 0;

    // Level-order traversal (BFS) to find the node to be deleted and the last node
    queue[rear++] = minHeap->root;

    while (front < rear) {
        struct MinHeapNode* temp = queue[front++];

        // Find the node to delete
        if (temp->key == key) {
            nodeToDelete = temp;
        }

        // Keep track of the last node
        lastNode = temp;

        if (temp->left) {
            parent = temp;
            queue[rear++] = temp->left;
        }

        if (temp->right) {
            parent = temp;
            queue[rear++] = temp->right;
        }
    }

    // If node to delete was not found
    if (!nodeToDelete) {
        printf("Node with key %d not found in the heap\n", key);
        return;
    }

    // If the node to delete is the last node
    if (nodeToDelete == lastNode) {
        if (parent && parent->right == lastNode) {
            parent->right = NULL;
        } else if (parent && parent->left == lastNode) {
            parent->left = NULL;
        } else {
            minHeap->root = NULL;  // If there is only one node in the heap
        }
        free(lastNode);
        minHeap->size--;
        return;
    }

    // Replace the node to delete with the last node's key
    nodeToDelete->key = lastNode->key;

    // Remove the last node
    if (parent && parent->right == lastNode) {
        parent->right = NULL;
    } else if (parent && parent->left == lastNode) {
        parent->left = NULL;
    }

    free(lastNode);
    minHeap->size--;

    // Heapify the modified heap to maintain the min-heap property
    minHeapify(minHeap->root);
}

// Function to print the binary heap in level-order
void printHeap(struct MinHeapNode* node) {
    if (!node) return;

    // Simple queue for BFS
    struct MinHeapNode* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = node;

    while (front < rear) {
        struct MinHeapNode* temp = queue[front++];

        printf("%d ", temp->key);

        if (temp->left)
            queue[rear++] = temp->left;

        if (temp->right)
            queue[rear++] = temp->right;
    }

    printf("\n");
}

//留下數字
int processString(const char *str) {
    // 创建副本以避免修改原始字符串
    char temp[100];
    strcpy(temp, str);
    char *numberStr = strtok(NULL, " ");  // 获取数字部分
    
    if (numberStr != NULL) {
        int number = atoi(numberStr);  // 将字符串转换为整数
        return number;
    } 
}

// Driver program to test the above functions
int main() {
    struct MinHeap* minHeap = createMinHeap();
    char determine[30];
    scanf("%s" , determine);
    while(determine[0] != '0'){
        if(determine[0] == 'd'){
            int delnum = processString(determine);
            deleteNode(minHeap, delnum);
            printf("insert");
        }
        else if(determine[0] == 'i'){
            int insernum = processString(determine);
            insertNode(minHeap, insernum);
            printf("delete");
        }
        else{
            printHeap(minHeap);
            break;
        }
    }
    // insertNode(minHeap, 3);
    // insertNode(minHeap, 2);
    // insertNode(minHeap, 1);
    // insertNode(minHeap, 15);
    // insertNode(minHeap, 5);
    // insertNode(minHeap, 4);
    // insertNode(minHeap, 45);

    // printf("Min Heap: ");
    // printHeap(minHeap->root);

    // printf("Extracted Min: %d\n", extractMin(minHeap));
    // printf("Min Heap after extraction: ");
    // printHeap(minHeap->root);

    return 0;
}
