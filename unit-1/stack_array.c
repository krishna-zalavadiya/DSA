#include <stdio.h>
#include <stdlib.h>

struct stack {
    int *s;  // Dynamic array for stack elements
    int top; // Index of top element
};
typedef struct node{
    char data;
    struct node *left;
    struct node *right;
} tnode;

typedef struct stack stack;

// Function prototypes
int *create(int size);
int stfull(stack st, int size);
int stempty(stack st);
void push(stack *st, int item, int size);
int pop(stack *st);
int peek(stack st);
void display(stack st);
tnode* constructree(char exp[100]);
int isoperator(char c);


int isoperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// construct expression tree from postfix expression (operands are single chars, optional spaces ignored)
tnode* constructree(char exp[100]) {
    tnode *root = NULL;
    if (!exp) return NULL;

    size_t cap = 16;
    tnode **pst = malloc(cap * sizeof(tnode*));
    if (!pst) return NULL;
    size_t top = 0;

    int i = 0;
    char token;
    while ((token = exp[i]) != '\0') {
        i++;
        if (token == ' ' || token == '\t' || token == '\r' || token == '\n') continue;

        tnode *newnode = malloc(sizeof(tnode));
        if (!newnode) { free(pst); return NULL; }
        newnode->data = token; newnode->left = newnode->right = NULL;

        if (!isoperator(token)) {
            // operand -> push
            if (top >= cap) {
                cap *= 2;
                tnode **tmp = realloc(pst, cap * sizeof(tnode*));
                if (!tmp) { free(newnode); free(pst); return NULL; }
                pst = tmp;
            }
            pst[top++] = newnode;
        } else {
            // operator -> pop two, create node with left/right
            if (top < 2) { // invalid postfix
                free(newnode);
                for (size_t j = 0; j < top; ++j) free(pst[j]);
                free(pst);
                return NULL;
            }
            tnode *right = pst[--top];
            tnode *left = pst[--top];
            newnode->right = right;
            newnode->left = left;
            pst[top++] = newnode;
        }
    }

    if (top == 1) root = pst[0];
    // free stack array (not the nodes)
    free(pst);
    return root;
}

int *create(int size) {
    return malloc(sizeof(int) * size); // Dynamically allocate memory
}

int stfull(stack st, int size) {
    return (st.top >= size - 1);
}

int stempty(stack st) {
    return (st.top == -1);
}

void push(stack *st, int item, int size) {
    if (stfull(*st, size)) {
        printf("Stack Overflow! Cannot push %d\n", item);
    } else {
        st->top++;
        st->s[st->top] = item;
        printf("%d pushed into stack\n", item);
    }
}

int pop(stack *st) {
    if (stempty(*st)) {
        printf("Stack Underflow! Cannot pop\n");
        return -1;
    } else {
        int item = st->s[st->top];
        st->top--;
        return item;
    }
}

int peek(stack st) {
    if (stempty(st)) {
        printf("Stack is empty\n");
        return -1;
    } else {
        return st.s[st.top];//st->s[st->top] if the stack *st in function parameter
    }
}

void display(stack st) {
    if (stempty(st)) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements (top to bottom): ");
        for (int i = st.top; i >= 0; i--) {
            printf("%d ", st.s[i]);
        }
        printf("\n");
    }
}

int main() {
    stack st;
    int size;

    printf("Enter the size of stack: ");
    scanf("%d", &size);

    st.s = create(size);
    if (st.s == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    st.top = -1; // Initialize stack

    int choice, item;

    while (1) {
        printf("\n1.Push\n2.Pop\n3.Peek\n4.Display\n5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter the element to be pushed: ");
            scanf("%d", &item);
            push(&st, item, size);
            break;
        case 2:
            item = pop(&st);
            if (item != -1)
                printf("%d popped from stack\n", item);
            break;
        case 3:
            item = peek(st);
            if (item != -1)
                printf("Top element is %d\n", item);
            break;
        case 4:
            display(st);
            break;
        case 5:
            free(st.s); // Free allocated memory before exit
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
//write a c function to comstruct a expression tree fram a prefix expression