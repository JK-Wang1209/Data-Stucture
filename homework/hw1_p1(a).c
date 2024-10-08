#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10000
int size = 0;

//the struct of the stack 
struct Stack{
    char array[MAX];
    int top;
};

//create the stack data structure
struct Stack* createStack(){
    struct Stack* newStack = (struct Stack*)malloc(sizeof(struct Stack));
    newStack->top = -1;
    return newStack;
}

//check the stack is full or not
int isFull(struct Stack*  stack){
    if(stack->top == MAX-1) return 1;
    else return 0;
}

//checj the stasck is empty or not
int isEmpty(struct Stack* stack){
    if(stack->top == -1) return 1;
    else return 0;
}

//push data in the stack
void push(struct Stack* stack , char ch){
    if(isFull(stack)){
        printf("Stack overflow");
    }
    else{
        stack->array[++stack->top] = ch;
    }
}

//pop the data out of the stack
char pop(struct Stack* stack){
    if(isEmpty(stack)) {
        printf("stack is empty");
    }
    else{
        return stack->array[stack->top--];
    }
}


//e.g. 
//input:
//  -*AB/CD
//output:
//  A*B-C/D
int isOperator(char temp){
    if(temp == '+' || temp == '-' || temp == '*' || temp == '/'){
        return 1;
    }
    else{
        return 0;
    }
}
int main(){
    struct Stack* stack = createStack();
    char string[10000];
    int finalindex =0;
    int index =0 , count =0;
    scanf("%s" , &string);

    for(int i=0 ; i<strlen(string) ; i++){
        char temp = string[i];
        //printf("%c" , temp);
        if(isOperator(temp) == 1){
            push(stack , temp);
        }
        else{
            printf("%c" , temp);
            if(!isEmpty(stack)){
                printf("%c" , pop(stack));
            }
            
        }
    }    

}