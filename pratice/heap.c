#include<stdio.h>
#include<stdlib.h>

struct Heap{
    int size;
    int capacity;
    int* arr;
};

typedef struct Heap Heap;

Heap* createHeap(int capacity){
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->arr = (int*)malloc(capacity*sizeof(int));
    return heap;
}

void swap(int* a , int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int isEmpty(struct Heap* heap){
    return heap->size == 0;
}

void insert(struct Heap* heap , int value){

}

void delete(struct Heap* heap , int value){

}

void levelOrder(){

}
