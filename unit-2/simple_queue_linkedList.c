#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} NODE;

NODE *front = NULL;
NODE *rear = NULL;

void qinsert(int val);
int qdelete();
void qdisplay();

int main(){
    int ch, x;
    while (1) {
        printf("\n1: Insert\n2: Delete\n3: Display\n4: Exit\n\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &x);
                qinsert(x);
                break;
            case 2:
                qdelete();
                break;
            case 3:
                qdisplay();
                break;
            case 4:
                free(front);
                exit(0);
            default:
                break;
        }
    }
    return 0;
}

void qinsert(int val){
    NODE *newNode = (NODE *) malloc(sizeof(NODE));
    newNode->data = val;
    newNode->next = NULL;
    if(front==NULL && rear==NULL)
        front = rear = newNode;
    else {
        rear->next = newNode;
        rear = newNode;
    }
    printf("Enqueueueueue successful: %d\n", val);
}

int qdelete(){
    int val=-1;
    if(front==NULL && rear==NULL)
        printf("Empty Queueueueue\n");
    else {
        NODE *temp = front;
        front = front->next;
        val = temp->data;
        free(temp);
        printf("Dequeueueueue successful: %d\n", val);
    }
    return val;
}

void qdisplay(){
    NODE *temp = front;
    printf("The elements are: \n");
    while (temp!=NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}