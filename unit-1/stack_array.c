#include <stdio.h>
#include <stdlib.h>

struct stack {
    int *s;
    int top;
};
typedef struct stack stack;

int* create(int size) {
    return malloc(sizeof(int) * size);
}

int stfull(stack st, int size) {
    return (st.top >= size - 1);
}

void push(stack *p_st, int item) {
    p_st->top++;
    p_st->s[p_st->top] = item;
}

int stempty(stack st) {
    return (st.top == -1);
}

int pop(stack *p_st) {
    int item = p_st->s[p_st->top];
    p_st->top--;
    return item;
}

void display(stack st) {
    if (stempty(st))
        printf("\nStack is Empty!");
    else {
        printf("\nStack elements (top to bottom): ");
        for (int i = st.top; i >= 0; i--)
            printf("%d ", st.s[i]);
    }
}

int main() {
    int item, choice, size = 0;
    char ans;
    stack st;
    st.top = -1;
    st.s = NULL;

    printf("\n\tImplementation Of Stack");

    do {
        printf("\n\nMain Menu");
        printf("\n1. Create");
        printf("\n2. Push");
        printf("\n3. Pop");
        printf("\n4. Display");
        printf("\n5. Exit");
        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter the size of the stack to be created: ");
            scanf("%d", &size);
            if (st.s != NULL) {
                free(st.s);  // free old stack if already created
            }
            st.s = create(size);
            if (st.s == NULL) {
                printf("Stack cannot be created");
                exit(1);
            }
            st.top = -1;
            break;

        case 2:
            if (st.s == NULL) {
                printf("\nStack not created yet!");
                break;
            }
            printf("\nEnter the item to be pushed: ");
            scanf("%d", &item);
            if (stfull(st, size))
                printf("\nStack is Full!");
            else
                push(&st, item);
            break;

        case 3:
            if (st.s == NULL || stempty(st))
                printf("\nEmpty stack! Underflow!!");
            else {
                item = pop(&st);
                printf("\nThe popped element is %d", item);
            }
            break;

        case 4:
            if (st.s == NULL)
                printf("\nStack not created yet!");
            else
                display(st);
            break;

        case 5:
            if (st.s != NULL) free(st.s);
            exit(0);

        default:
            printf("\nInvalid Choice!");
        }

        printf("\nDo you want to continue? (Y/N): ");
        scanf(" %c", &ans);

    } while (ans == 'Y' || ans == 'y');

    if (st.s != NULL) free(st.s);
    return 0;
}