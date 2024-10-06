#include<stdio.h>
#include<stdlib.h>

#define MAX 100

struct Node{
    int data;
    struct Node *left , *right;
};
typedef struct Node* TreeNode;

struct Stack{
    int size;
    int top;
    struct Node** array;
};

struct Node* newNode(int data){
    TreeNode node = (TreeNode)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

struct Stack* createstack(int size){
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->size = size;
    stack->top = -1;
    stack->array = (TreeNode*)malloc(sizeof(TreeNode));
    return stack;
}

int isFull(struct Stack* stack){
    return stack->top -1 == stack->size;
}

int isEmpty(struct Stack* stack){
    return stack->top == -1;
}

void push(struct Stack* stack , TreeNode node){
    if(isFull(stack)){
        return ;
    }
    else{
        stack->array[++stack->top] = node;
    }
}

TreeNode pop(struct Stack* stack){
    if(isEmpty(stack)){
        return NULL;
    }
    else{
        return stack->array[stack->top--]; 
    }
}

TreeNode peek(struct Stack* stack){
    if(isEmpty(stack)){
        return NULL;
    }
    else{
        return stack->array[stack->top];
    }
}

void postOrderIterative(TreeNode root){
    if(root == NULL) return ;
    struct Stack* stack = createstack(MAX);
    do{
        while(root != NULL){
            if(root->right) push(stack , root->right);
            push(stack , root);

            root = root->left;
        }

        root = pop(stack);

        if(root->right && peek(stack) == root->right){
            pop(stack);
            push(stack , root);
            root = root->right;
        }
        else{
            printf("%d" , root->data);
            root =NULL;
        }
    }while(!isEmpty(stack));
}

int main(){
    TreeNode root = NULL;
    root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    printf("PostOrder traversal of binary tree is: \n");
    printf("[");
    postOrderIterative(root);
    printf("]");
    return 0;
}




