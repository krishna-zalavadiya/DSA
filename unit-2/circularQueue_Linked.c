#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} NODE;

typedef struct cqueue {
    NODE *front;
    NODE *rear;
} CQ;

void cenqueue(CQ *q, int val);
int cdequeue(CQ *q);
void display(CQ *q);

int main() {
    CQ *q = (CQ *)malloc(sizeof(CQ));
    q->front = NULL;
    q->rear = NULL;

    int ch, x;
    while (1) {
        printf("\n1: Insert\n2: Delete\n3: Display\n4: Exit\n\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &x);
                cenqueue(q, x);
                break;
            case 2:
                cdequeue(q);
                break;
            case 3:
                display(q);
                break;
            case 4:
                free(q); 
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void cenqueue(CQ *q, int val) {
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->data = val;
    newNode->next = NULL;
    if (q->front == NULL) {
        q->front = q->rear = newNode;
        newNode->next = q->front;
    } 
    else {
        q->rear->next = newNode;
        q->rear = newNode;
        newNode->next = q->front;
    }
}

int cdequeue(CQ *q) {
    if (q->front == NULL) {
        printf("Empty Queue\n");
        return -1;
    }
    int val;
    NODE *temp = q->front;
    if (q->front == q->rear) {
        val = q->front->data;
        free(q->front);
        q->front = q->rear = NULL;
    } 
    else {
        val = q->front->data;
        q->front = q->front->next;
        q->rear->next = q->front;
        free(temp);
    }
    printf("Dequeue successful: %d\n", val);
    return val;
}

void display(CQ *q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    NODE *temp = q->front;
    printf("The elements are: \n");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != q->front);
    printf("\n");
}