#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct stack {
    char data[MAX];
    int top;
} stack;

void init(stack *s) {
    s->top = -1;
}

int empty(stack *s) {
    return (s->top == -1);
}

int full(stack *s) {
    return (s->top == MAX - 1);
}

void push(stack *s, char x) {
    if (full(s)) {
        printf("Stack overflow!\n");
        return;
    }
    s->data[++(s->top)] = x;
}

char pop(stack *s) {
    if (empty(s)) {
        printf("Stack underflow!\n");
        return '\0';
    }
    return s->data[(s->top)--];
}

char top(stack *s) {
    if (empty(s)) return '\0';
    return s->data[s->top];
}

int match_parentheses(char expr[]) {
    stack s;
    init(&s);

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        } 
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (empty(&s)) return 0;   // closing without opening

            char in = pop(&s);
            if ((ch == ')' && in != '(') ||
                (ch == '}' && in != '{') ||
                (ch == ']' && in != '[')) {
                return 0;   // mismatch
            }
        }
    }

    return empty(&s);  // should be empty if balanced
}

int main() {
    char expr[MAX];

    printf("Enter an expression: ");
    scanf("%s", expr);   // no spaces

    if (match_parentheses(expr))
        printf("\nParentheses matching succeeded\n");
    else
        printf("\nParentheses matching failed\n");

    return 0;
}