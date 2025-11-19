#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
// ------------------------------
// STACK FOR TREE NODES
// ------------------------------

struct stack {
    struct node **arr;   // array of node pointers
    int top;
    int size;
};
typedef struct stack stack;


// ------------------------------
// EXPRESSION TREE NODE
// ------------------------------
struct node {
    char data;           // operator or operand
    struct node *left;
    struct node *right;
};
typedef struct node node;


// ------------------------------
// STACK FUNCTIONS
// ------------------------------

// Create stack of given size
stack* createStack(int size) {
    stack *s = (stack*)malloc(sizeof(stack));
    s->arr = (node**)malloc(sizeof(node*) * size);
    s->top = -1;
    s->size = size;
    return s;
}

// Check if stack full
int stfull(stack *s) {
    return s->top >= s->size - 1;
}

// Check if stack empty
int stempty(stack *s) {
    return s->top == -1;
}

// Push node to stack
void push(stack *s, node *n) {
    if (stfull(s)) {
        printf("Stack overflow!\n");
        return;
    }
    s->arr[++s->top] = n;
}

// Pop node from stack
node* pop(stack *s) {
    if (stempty(s)) {
        printf("Stack underflow!\n");
        return NULL;
    }
    return s->arr[s->top--];
}

// Free stack memory
void freeStack(stack *s) {
    if (s) {
        free(s->arr);
        free(s);
    }
}


// ------------------------------
// EXPRESSION TREE FUNCTIONS
// ------------------------------

// Check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Create a tree node
node* createNode(char ch) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = ch;
    temp->left = temp->right = NULL;
    return temp;
}


// ---------------------------------------------------
// BUILD EXPRESSION TREE FROM POSTFIX EXPRESSION
// ---------------------------------------------------
node* createExpressionTree(char *expr) {
    stack *s = createStack(100);

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        // Ignore spaces
        if (ch == ' ') continue;

        node *temp = createNode(ch);

        if (isOperator(ch)) {
            // Operator → pop two nodes
            node *right = pop(s);
            node *left  = pop(s);

            // Build subtree
            temp->left = left;
            temp->right = right;
        }

        // Push operand or subtree root
        push(s, temp);
    }

    // Final element is root
    node *root = pop(s);
    freeStack(s);
    return root;
}

// ------------------------------
// TREE TRAVERSALS
// ------------------------------
void preorder(node *t) {
    if (t) {
        printf("%c ", t->data);
        preorder(t->left);
        preorder(t->right);
    }
}

// Inorder WITH brackets for proper expression
void inorder(node *t) {
    if (t) {
        if (isOperator(t->data)) printf("(");
        inorder(t->left);
        printf("%c", t->data);
        inorder(t->right);
        if (isOperator(t->data)) printf(")");
    }
}

void postorder(node *t) {
    if (t) {
        postorder(t->left);
        postorder(t->right);
        printf("%c ", t->data);
    }
}


// ------------------------------
// EVALUATE THE EXPRESSION TREE
// ------------------------------
int eval(node *t) {
    // Leaf → operand
    if (!t->left && !t->right)
        return t->data - '0';  // convert char to int

    int l = eval(t->left);
    int r = eval(t->right);

    switch (t->data) {
        case '+': return l + r;
        case '-': return l - r;
        case '*': return l * r;
        case '/': return l / r;
        case '^': return (int)pow(l, r);
    }
    return 0;
}


// ------------------------------
// FREE TREE MEMORY
// ------------------------------
void freeTree(node *t) {
    if (t) {
        freeTree(t->left);
        freeTree(t->right);
        free(t);
    }
}


// ------------------------------
// MAIN
// ------------------------------
int main() {
    char expr[100];

    printf("Enter a postfix expression: ");
    scanf("%s", expr);

    node *root = createExpressionTree(expr);

    printf("\nPreorder  (Prefix) : ");
    preorder(root);

    printf("\nInorder   (Infix)  : ");
    inorder(root);

    printf("\nPostorder (Postfix): ");
    postorder(root);

    int result = eval(root);
    printf("\n\nEvaluation Result: %d\n", result);

    freeTree(root);
    return 0;
}
