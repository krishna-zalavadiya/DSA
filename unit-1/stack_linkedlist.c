#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;            // Data of the node
    struct node *next;   // Pointer to next node
} node;

typedef struct stack {
    node *top;           // Pointer to top of stack
} stack;

// Function prototypes
void init(stack *st);
int isempty(stack *st);
void push(stack *st, int item);
int pop(stack *st);
int peek(stack *st);
void display(stack *st);

// Initialize stack
void init(stack *st) {
    st->top = NULL;
}

// Check if stack is empty
int isempty(stack *st) {
    return st->top == NULL;
}

// Push element to stack
void push(stack *st, int item) {
    node *newnode = (node *)malloc(sizeof(node));
    if (!newnode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newnode->data = item;
    newnode->next = st->top;
    st->top = newnode;
    printf("%d pushed into stack\n", item);
}

// Pop element from stack
int pop(stack *st) {
    if (isempty(st)) {
        printf("Stack is empty! Cannot pop.\n");
        return -1;
    }
    node *temp = st->top;
    int item = temp->data;//st->top->data;
    st->top = st->top->next;
    free(temp);
    return item;
}

// Peek top element
int peek(stack *st) {
    if (isempty(st)) {
        printf("Stack is empty! Nothing to peek.\n");
        return -1;
    }
    return st->top->data;
}

// Display stack elements
void display(stack *st) {
    if (isempty(st)) {
        printf("Stack is Empty!\n");
        return;
    }

    printf("Stack elements (top to bottom):\n");
    node *temp = st->top;
    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

int main() {
    stack st;
    init(&st);

    push(&st, 10);
    push(&st, 20);
    push(&st, 30);

    display(&st);

    printf("Peek top: %d\n", peek(&st));
    printf("Popped: %d\n", pop(&st));
    printf("Popped: %d\n", pop(&st));

    display(&st);

    if (isempty(&st)) {
        printf("Stack is empty now.\n");
    }

    return 0;
}
