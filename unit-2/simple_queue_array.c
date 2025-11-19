#include <stdio.h>
#include <stdlib.h>

struct queue{
    int front, rear , capacity;
    int *array;
};
typedef struct queue queue;

queue* createQueue(int capacity){
    queue* q = (queue*)malloc(sizeof(queue));
    q->capacity = capacity;
    q->front = q->rear = -1;//initialy dono front and rear -1
    q->array = (int*)malloc(q->capacity * sizeof(int));
    return q;
}


int isfull(queue* q)
{
    return q->rear == q->capacity - 1;//here rear starts from 0 so capacity - 1
}

int isempty(queue* q)
{
    return q->front == -1;//either front is -1 or front crossed rear
}
//inserting the element at rear end
void enqueue(queue* q, int data)
{
    if(isfull(q))
    {
        printf("Queue is full\n");
        return;
    }
    
    q->front++;//initially front and rear -1 so incrementing both
    q->rear++;
    q->array[q->rear] = data;
    printf("%d enqueued to queue\n", data);
}
//removing the element from front
int dequeue(queue* q)
{
    if(isempty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    int data = q->array[q->front];//getting the front element to return
    if(q->front == q->rear)//if only one element was present
        q->front = q->rear = -1;//resetting the queue
    else
    q->front++;
    return data;
}

int front(queue *q)
{
     if(isempty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    else
        return q->array[q->front];
}

int rear(queue * q)
{
     if(isempty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    else
        return q->array[q->rear];
}
//displaying the queue elements
void display(queue *q)
{
     if(isempty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    for(int i = q->front; i <= q->rear; i++)
    {
        printf("%d ", q->array[i]);
    }
    printf("\n");
}

int main()
{
    struct queue *q = createQueue(5);
    int choice, value;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Front\n");
        printf("5. Rear\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(q, value);
                break;
            case 2:
                value = dequeue(q);
                if (value != -1)
                    printf("Dequeued: %d\n", value);
                break;
            case 3:
                printf("Queue contents: ");
                display(q);
                break;
            case 4:
                value = front(q);
                if (value != -1)
                    printf("Front element: %d\n", value);
                break;
            case 5:
                value = rear(q);
                if (value != -1)
                    printf("Rear element: %d\n", value);
                break;
            case 6:
                free(q->array);
                free(q);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}