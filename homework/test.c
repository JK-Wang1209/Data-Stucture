#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char* stack[MAX];
int top = -1;

// Function to push an element onto the stack
void push(char* element) {
    if (top < MAX - 1) {
        stack[++top] = strdup(element);  // Duplicate the string to avoid overwriting
    } else {
        printf("Stack overflow\n");
    }
}

// Function to pop an element from the stack
char* pop() {
    if (top != -1) {
        return stack[top--];
    } else {
        return NULL;  // Stack underflow
    }
}

// Function to check if a character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to convert prefix to infix
char* prefixToInfix(char* prefix) {
    char* token = strtok(prefix, " ");
    while (token != NULL) {
        if (isOperator(token[0])) {
            // Pop two operands from the stack
            char* operand1 = pop();
            char* operand2 = pop();

            // Create a new expression
            char* expr = (char*)malloc(MAX * sizeof(char));
            snprintf(expr, MAX, "(%s %s %s)", operand1, token, operand2);

            // Push the new expression onto the stack
            push(expr);
        } else {
            // It's an operand, push it onto the stack
            push(token);
        }
        token = strtok(NULL, " ");
    }
    return pop();  // The final result will be at the top of the stack
}

int main() {
    char prefix[MAX];

    printf("Enter a prefix expression: ");
    fgets(prefix, MAX, stdin);
    
    // Remove the newline character from the input
    prefix[strcspn(prefix, "\n")] = '\0';

    char* infix = prefixToInfix(prefix);
    printf("Infix expression: %s\n", infix);

    // Clean up allocated memory
    free(infix);
    for (int i = 0; i <= top; i++) {
        free(stack[i]);
    }

    return 0;
}
