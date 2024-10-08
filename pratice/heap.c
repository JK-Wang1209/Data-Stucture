#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct Heap{
    int* array;
    int size; 
    int capacity;
}Heap;

Heap* createHeap(int capacity){
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->size =0;
    heap->capacity = capacity;
    heap->array = (int*)malloc(capacity *sizeof(int));
    return heap;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b ; 
    *b = temp;
}

void heaptify(Heap* heap , int i){
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    
}